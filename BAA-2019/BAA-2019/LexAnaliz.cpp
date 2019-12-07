#pragma once
#include "pch.h"
namespace Lex
{
	Graph graphs[N_GRAPHS] =
	{
		{ LEX_SEPARATORS, FST::FST(GRAPH_SEPARATORS) },
		{ LEX_ID_TYPE, FST::FST(GRAPH_INTEGER) },
		{ LEX_LITERAL, FST::FST(GRAPH_INT_LITERAL) },
		{ LEX_LITERAL, FST::FST(GRAPH_STRING_LITERAL) },
		{ LEX_LITERAL, FST::FST(GRAPH_SYMBOL_LITERAL) },
		{ LEX_LITERAL, FST::FST(GRAPH_INT_NEGATIVE) },
		{ LEX_TYPE, FST::FST(GRAPH_TYPE) },
		{ LEX_MAIN, FST::FST(GRAPH_MAIN) },
		{ LEX_ID_TYPE, FST::FST(GRAPH_STRING) },
		{ LEX_FUNCTION, FST::FST(GRAPH_FUNCTION) },
		{ LEX_ID_TYPE, FST::FST(GRAPH_SYMBOL) },
		{ LEX_RETURN, FST::FST(GRAPH_RETURN) },
		{ LEX_WRITE, FST::FST(GRAPH_WRITE) },
		{ LEX_NEWLINE, FST::FST(GRAPH_NEWLINE) },
		{ LEX_IS, FST::FST(GRAPH_IS) },
		{ LEX_WHILE, FST::FST(GRAPH_WHILE) },
		{ LEX_DO, FST::FST(GRAPH_DO) },
		{ LEX_ISFALSE, FST::FST(GRAPH_ISFALSE) },
		{ LEX_ISTRUE, FST::FST(GRAPH_ISTRUE) },
		{ LEX_ID, FST::FST(GRAPH_ID) }
	};
	char* getScopeName(IT::IdTable idtable, char* prevword) // имя текущей области видимости (если находимся внутри блока)
	{
		char *a = new char[5];
		a = (char*)"main\0";
		if (strcmp(prevword, MAIN) == 0)
			return a;
		for (int i = idtable.size - 1; i >= 0; i--)
			if (idtable.table[i].idtype == IT::IDTYPE::F|| idtable.table[i].idtype == IT::IDTYPE::S)
				return idtable.table[i].id;
		return nullptr; // не найдено имя функции
	}

	bool isLiteral(char* id)
	{
		if (isdigit(*id) || *id == IN_CODE_QUOTE || *id == LEX_MINUS || *id == IN_CODE_TILDA || *id == NULL)
			return true;
		return false;
	}
	IT::STDFNC getStandFunction(char* id)
	{
		if (!strcmp(RAND, id))
			return IT::STDFNC::F_RAND;
		if (!strcmp(POW, id))
			return IT::STDFNC::F_POW;
		return IT::STDFNC::F_NOT_STD;
	}
	int getLiteralIndex(IT::IdTable ittable, char* value, IT::IDDATATYPE type) // получаем индекс повторного литерала(по значению)
	{
		for (int i = 0; i < ittable.size; i++)
		{
			if (ittable.table[i].idtype == IT::IDTYPE::L && ittable.table[i].iddatatype == type)
			{
				switch (type)
				{
				case IT::IDDATATYPE::INT:
					if (ittable.table[i].value.vint == atoi(value))
						return i;
					break;
				case IT::IDDATATYPE::STR:
					char buf[STR_MAXSIZE];
					for (unsigned j = 1; j < strlen(value) - 1; j++) // без кавычек
						buf[j - 1] = value[j];
					buf[strlen(value) - 2] = IN_CODE_NULL;
					if (strcmp((char*)ittable.table[i].value.vstr.str, buf) == 0)
						return i;
					break;
				case IT::IDDATATYPE::SYM:
					if (ittable.table[i].value.symbol == value[1])
						return i;
					break;
				}
			}
		}
		return TI_NULLIDX;
	}
	IT::IDDATATYPE getType(char* curword, char* idtype)
	{
		if (!strcmp(TYPE_SYMBOL, idtype))
			return IT::IDDATATYPE::SYM; // символьный ид
		if (!strcmp(TYPE_STRING, idtype))
			return IT::IDDATATYPE::STR;  // строковый ид
		if (!strcmp(TYPE_INTEGER, idtype))
			return IT::IDDATATYPE::INT;	 // числовой  ид
		if (isdigit(*curword) || *curword == LEX_MINUS)
			return IT::IDDATATYPE::INT;				// числовой литерал
		else if (*curword == IN_CODE_QUOTE)
			return IT::IDDATATYPE::STR;	// строковый литерал
		else if (*curword == IN_CODE_TILDA)
			return IT::IDDATATYPE::SYM;	// строковый литерал

		return IT::IDDATATYPE::UNDEF;		// неопределенный тип, индикатор ошибки
	}
	char* getNextLiteralName()						// сгенерировать следующее имя литерала
	{
		static int literalNumber = 1;
		char* buf = new char[SCOPED_ID_MAXSIZE];
		char num[3];
		strcpy_s(buf, ID_MAXSIZE, "L");
		_itoa_s(literalNumber++, num, 10);
		strcat(buf, num);
		return buf;
	}
	int getIndexInLT(LT::LexTable &lextable, int itTableIndex)					// индекс первой встречи в таблице лексем
	{
		if (itTableIndex == TI_NULLIDX)		// если идентификатор встречается впервые
			return lextable.size;
		for (int i = 0; i < lextable.size; i++)
			if (itTableIndex == lextable.table[i].idxTI)
				return i;
		return TI_NULLIDX;
	}
	IT::Entry* getEntry(		// формирует и возвращает строку ТИ
		Lex::LEX& tables,						// ТЛ + ТИ
		char lex,								// лексема
		char* id,								// идентификатор
		char* idtype,							// предыдущая (тип)
		bool isParam,							// признак параметра функции
		bool isFunc,							// признак функции
		Log::LOG log,							// протокол
		int line,								// строка в исходном тексте
		bool& lex_ok)							// флаг ошибки(по ссылке)
	{
		// тип данных
		IT::IDDATATYPE type = getType(id, idtype);
		int index = IT::isId(tables.idtable, id);	// индекс существующего идентификатора или -1
		if (lex == LEX_LITERAL)
			index = getLiteralIndex(tables.idtable, id, type);
		if (index != TI_NULLIDX)
			return nullptr;							// уже существует
		IT::Entry *itentry = new IT::Entry;
		itentry->iddatatype = type; // сохраняем тип данных


		itentry->idxfirstLE = getIndexInLT(tables.lextable, index); // индекс первой строки в таблице лексем 

		if (lex == LEX_LITERAL) // литерал
		{
			bool int_ok = IT::SetValue(itentry, id);
			if (!int_ok)
			{
				// превышен максимальный размер числового литерала
				Log::WriteError(log.stream, Error::geterrorin(313, line, 0));
				lex_ok = false;
			}
			if (itentry->iddatatype == IT::IDDATATYPE::STR && itentry->value.vstr.len == 0)
			{
				Log::WriteError(log.stream, Error::geterrorin(310, line, 0));
				lex_ok = false;
			}
			strcpy_s(itentry->id, getNextLiteralName());
			itentry->idtype = IT::IDTYPE::L;
		}
		else // идентификатор
		{
			switch (type)
			{
			case IT::IDDATATYPE::STR:
				strcpy_s(itentry->value.vstr.str, "");
				itentry->value.vstr.len = TI_STR_DEFAULT;
				break;
			case IT::IDDATATYPE::INT:
				itentry->value.vint = TI_INT_DEFAULT;
				break;
			case IT::IDDATATYPE::SYM:
				itentry->value.symbol = TI_SYM_DEFAULT;
				break;
			}

			if (isFunc)
			{
				switch (getStandFunction(id))
				{
				case IT::STDFNC::F_RAND:
				{
					itentry->idtype = IT::IDTYPE::S;
					itentry->iddatatype = RAND_TYPE;
					itentry->value.params.count = RAND_PARAMS_CNT;
					itentry->value.params.types = new IT::IDDATATYPE[RAND_PARAMS_CNT];
					break;
				}
				case IT::STDFNC::F_POW:
				{
					itentry->idtype = IT::IDTYPE::S;
					itentry->iddatatype = POW_TYPE;
					itentry->value.params.count = POW_PARAMS_CNT;
					itentry->value.params.types = new IT::IDDATATYPE[POW_PARAMS_CNT];
					for (int k = 0; k < POW_PARAMS_CNT; k++)
						itentry->value.params.types[k] = IT::POW_PARAMS[k];
					break;
				}
				case IT::STDFNC::F_NOT_STD:
					itentry->idtype = IT::IDTYPE::F;
					break;
				}
			}
			else if (isParam)
				itentry->idtype = IT::IDTYPE::P;
			else
				itentry->idtype = IT::IDTYPE::V;

			strncpy_s(itentry->id, id, SCOPED_ID_MAXSIZE);
		}

		// -------------------------------------------------------
		int i = tables.lextable.size; // индекс в ТЛ текущего ИД

		if (i > 1 && itentry->idtype == IT::IDTYPE::V && tables.lextable.table[i - 2].lexema != LEX_TYPE)
		{
			// в объявлении отсутствует ключевое слово new
			Log::WriteError(log.stream, Error::geterrorin(304, line, 0));
			lex_ok = false;
		}
		if (i > 1 && itentry->idtype == IT::IDTYPE::F && tables.lextable.table[i - 1].lexema != LEX_FUNCTION)
		{
			// в объявлении не указан тип функции
			Log::WriteError(log.stream, Error::geterrorin(303, line, 0));
			lex_ok = false;
		}
		if (itentry->iddatatype == IT::IDDATATYPE::UNDEF)
		{
			// невозможно определелить тип
			Log::WriteError(log.stream, Error::geterrorin(300, line, 0));
			lex_ok = false;
		}
		// --------------------------------------------------------
		return itentry;
	}
	bool analyze(LEX& tables, In::IN &in, Log::LOG &log, Parm::PARM &parm)
	{
		static bool lex_ok = true;
		tables.lextable = LT::Create(LT_MAXSIZE);
		tables.idtable = IT::Create(MAXSIZE_TI);
		bool isParam = false, isFunc = false;
		int enterPoint = NULL;
		char curword[STR_MAXSIZE], nextword[STR_MAXSIZE];
		int curline;
		std::stack <char*> scopes;			// стек для хранения имени текущей области видимости
		for (int i = 0; i < in.words->size; i++)
		{
			strcpy_s(curword, in.words[i].word);
			if (i < in.words->size - 1)
				strcpy_s(nextword, in.words[i + 1].word);
			curline = in.words[i].line;
			isFunc = false;
			int idxTI = TI_NULLIDX;
			for (int j = 0; j < N_GRAPHS; j++)
			{
				FST::FST fst((unsigned char*)curword, graphs[j].graph);
				if (FST::execute(fst))
				{
					char lexema = graphs[j].lexema;
					switch (lexema)
					{
					case LEX_MAIN:
						enterPoint++;
						break;
					case LEX_SEPARATORS:
					{
						switch (*curword)
						{
						case LEX_LEFTHESIS:		// открывающая скобка - параметры  функции
						{
							isParam = true;
							if (*nextword == LEX_RIGHTTHESIS || ISTYPE(nextword))
							{
								char* functionname = new char[ID_MAXSIZE];								//функция для области видимости
								char* scopename = getScopeName(tables.idtable, in.words[i - 1].word);
								if (scopename == nullptr)
									break;
								strcpy_s(functionname, ID_MAXSIZE, scopename);
								scopes.push(functionname);
							}
							break;
						}
						case LEX_RIGHTTHESIS:	// закрывающая скобка
						{
							isParam = false;
							// конец области видимости
							if (*in.words[i - 1].word == LEX_LEFTHESIS || (i > 2 && (tables.lextable.table[tables.lextable.size - 2].lexema == LEX_ID_TYPE)))
								scopes.pop();
							break;
						}
						case LEX_LEFTBRACE:		// начало области видимости
						{
							char* functionname = new char[ID_MAXSIZE];
							char* scopename = getScopeName(tables.idtable, in.words[i - 1].word);
							if (scopename == nullptr)  break;
							strcpy_s(functionname, ID_MAXSIZE, scopename);
							scopes.push(functionname);
							break;
						}
						case LEX_BRACELET:		// конец области видимости
						{
							// только в этом случае закрываем область видимости
							if (*in.words[i + 1].word == LEX_ID_TYPE || *in.words[i + 1].word == LEX_MAIN)
							{
								if (!scopes.empty())
									scopes.pop();
							}
							break;
						}
						}
						lexema = *curword;
						break;
					}
					case LEX_ID:
					case LEX_LITERAL:
					{
						char id[STR_MAXSIZE] = "";
						idxTI = NULLDX_TI;										// индекс идентификатора в ТИ
						if (*nextword == LEX_LEFTHESIS)
							isFunc = true;										// идентификатор функции
						char* idtype = (isFunc && i > 1) ?						// тип идентификатора
							in.words[i - 2].word : in.words[i - 1].word;		// пропускаем ключевое слово function
						if (!isFunc && !scopes.empty())
							strncpy_s(id, scopes.top(), ID_MAXSIZE);
						strncat(id, curword, ID_MAXSIZE);
						if (isLiteral(curword))
							strcpy_s(id, curword); // литерал заменяется своим значением
						IT::Entry *itentry = getEntry(tables, lexema, id, idtype, isParam, isFunc, log, curline, lex_ok);
						if (itentry != nullptr) // первая встреча - объявление
						{
							if (isFunc) // если функция - сохранить список параметров
							{
								if (getStandFunction(id) == IT::STDFNC::F_NOT_STD) // стандартная функция или нет
								{
									itentry->value.params.count = NULL;
									itentry->value.params.types = new IT::IDDATATYPE[MAX_PARAMS_COUNT];
									for (int k = i; in.words[k].word[0] != LEX_RIGHTTHESIS; k++)
									{
										if (k == in.words->size || in.words[k].word[0] == LEX_SEPARATOR)
											break;
										if (ISTYPE(in.words[k].word))
										{
											if (itentry->value.params.count >= MAX_PARAMS_COUNT)
											{
												Log::WriteError(log.stream, Error::geterrorin(306, curline, 0));
												lex_ok = false;
												break;
											}
											itentry->value.params.types[itentry->value.params.count++] = getType(NULL, in.words[k].word);
										}
									}
								}
							}
							IT::Add(tables.idtable, *itentry);
							idxTI = tables.idtable.size - 1;
						}
						else // повторный идентификатор (уже есть)
						{
							int i = tables.lextable.size - 1; // попытка переопределить идентификатор
							if (i > 0 && tables.lextable.table[i - 1].lexema == LEX_TYPE || tables.lextable.table[i].lexema == LEX_TYPE
								|| tables.lextable.table[i - 1].lexema == LEX_FUNCTION || tables.lextable.table[i].lexema == LEX_FUNCTION
								|| tables.lextable.table[i - 1].lexema == LEX_ID_TYPE || tables.lextable.table[i].lexema == LEX_ID_TYPE)
							{
								Log::WriteError(log.stream, Error::geterrorin(305, curline, 0));
								lex_ok = false;
							}
							idxTI = IT::isId(tables.idtable, id);	// индекс существующего идентификатора
							if (lexema == LEX_LITERAL)
								idxTI = getLiteralIndex(tables.idtable, curword, getType(id, in.words[i - 1].word)); // или литерала
						}
					}
					break;
					}
					LT::Entry *ltentry = new LT::Entry(lexema, curline, idxTI);
					LT::Add(tables.lextable, *ltentry);
					break;
				}
				else if (j == N_GRAPHS - 1) // цепочка не распознана
				{
					Log::WriteError(log.stream, Error::geterrorin(201, curline, 0));
					lex_ok = false;
				}

			}
		}
		if (enterPoint == NULL) // не найдена точка входа
		{
			Log::WriteError(log.stream, Error::geterror(301));
			lex_ok = false;
		}
		if (enterPoint > 1) //больше 1 точки входа
		{
			Log::WriteError(log.stream, Error::geterror(302));
			lex_ok = false;
		}
		return lex_ok;
	}

}