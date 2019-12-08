// BAA-2019.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"

int _tmain(int argc, _TCHAR ** argv)
{
	char LEXERROR[] = "Лексический анализ завершен с ошибками";
	char SYNTERROR[] = "Синтаксический анализ завершен с ошибками";
	char SEMERROR[] = "Обнаружены семантические ошибки";
	char POLISHERROR[] = "Ошибка при попытке преобразования выражения";
	char LEXGOOD[] = "Лексический анализ завершен без ошибок";
	char SYNTGOOD[] = "Синтаксический анализ завершен без ошибок";
	char SEMGOOD[] = "Семантический анализ завершен без ошибок";
	char POLISHGOOD[] = "Преобразование выражений завершено без ошибок";
	char MESSAGE[] = "--------------------КОНЕЧНЫЕ ТАБЛИЦЫ ЛЕКСЕМ И ИДЕНТИФИКАТОРОВ-------------------";
	char STOP[] = "Выполнение программы остановлено";
	char ALLGOOD[] = "Программа успешно завершена!";
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLog(log);													//написать заголовок журнала
		Log::WriteParm(log, parm);											//записать в журнал параметры
		In::IN in = In::getin(parm.in,log.stream);
		Log::WriteIn(log, in);
		in.words = In::getWordsTable(log.stream, in.text, in.code, in.size);	//разобрать на токены
		In::printTable(in.words);
		Lex::LEX tables;
		bool lex_ok = Lex::analyze(tables, in, log, parm);					//выполнить лексический анализ
		
		LT::writeLexTable(log.stream, tables.lextable);							//записать в журнал таблицы лексем и идентификаторов 
		IT::writeIdTable(log.stream, tables.idtable);							//а также соответствие токенов и лексем
		LT::writeLexemsOnLines(log.stream, tables.lextable);
		if (!lex_ok)
		{
			Log::WriteLine(log, LEXERROR, "");
			Log::WriteLineConsole(LEXERROR, STOP, "");
			return 0;
		}
		else
		{
			Log::WriteLineConsole(LEXGOOD, "");
		}

		MFST_TRACE_START(log.stream);
		MFST::Mfst mfst(tables, GRB::getGreibach());							//выполнить синтаксический анализ
		bool synt_ok = mfst.start(log);
		mfst.savededucation();
		mfst.printrules(log);													//вывести дерево разбора
		if (!synt_ok)
		{
			Log::WriteLine(log, SYNTERROR, "");
			Log::WriteLineConsole(SYNTERROR, STOP, "");
			return 0;
		}
		else Log::WriteLineConsole(SYNTGOOD, "");

		bool sem_ok = Semantic::semanticsCheck(tables, log);					//выполнить семантический анализ
		if (!sem_ok)
		{
			Log::WriteLine(log, SEMERROR, "");
			Log::WriteLineConsole(SEMERROR, STOP, "");
			return 0;
		}

		tables.lextable.size = Polish::searchExpression(tables);		//выполнить преобразование выражений в ПОЛИЗ
		if (tables.lextable.size == 0)
		{
			Log::WriteLine(log, POLISHERROR, "");
			Log::WriteLineConsole(POLISHERROR, STOP, "");
			return 0;
		}
		else Log::WriteLineConsole(POLISHGOOD,""); 

		Log::WriteLine(log, MESSAGE, "");
		LT::writeLexTable(log.stream, tables.lextable);							//записать в журнал новые таблицы лексем и идентификаторов
		IT::writeIdTable(log.stream, tables.idtable);
		LT::writeLexemsOnLines(log.stream, tables.lextable);					//а также соответствие токенов и лексем
		Log::WriteLineConsole(MESSAGE, "");
		IT::writeIdTable(&std::cout, tables.idtable);							//записать в командную строку новые таблицы лексем и идентификаторов 
		LT::writeLexTable(&std::cout, tables.lextable);							//а также соответствие токенов и лексем
		LT::writeLexemsOnLines(&std::cout, tables.lextable);

		bool gen_ok = Gener::CodeGeneration(tables, parm, log);								//выполнить генерацию кода
		if (!gen_ok)
		{
			Log::WriteLine(log, SEMERROR, "");
			Log::WriteLineConsole(SEMERROR, STOP, "");
			return 0;
		}
		else Log::WriteLineConsole(SEMGOOD, "");
		Log::WriteLine(log, ALLGOOD, "");									//итог работы программы
		Log::WriteLineConsole(ALLGOOD, "");
		Log::Close(log);
		system("pause");
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log.stream, e);
	}
	catch (...)
	{
		std::cout << "Ошибка: Системный сбой" << std::endl;
	}
	return 0;
}

