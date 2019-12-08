#include "pch.h"
#include <string>

using namespace std;

namespace Gener
{
	
	void CodeGeneration(Lex::LEX& lex, Parm::PARM& parm, Log::LOG& log)
	{
		ofstream ofile(parm.out);
		ofile << BEGIN;
		ofile << EXTERN;
		ofile << ".const\n";
		int conditionnum = 0,cyclenum=0;
		for (int i = 0; i < lex.idtable.size; i++)
		{
			if (lex.idtable.table[i].idtype == IT::L)
			{
				ofile << "\t" << lex.idtable.table[i].id;
				if (lex.idtable.table[i].iddatatype == IT::SYM)
				{
					ofile << " BYTE \'" << lex.idtable.table[i].value.symbol << "\', 0\n";
				}
				if (lex.idtable.table[i].iddatatype == IT::STR)
				{
					ofile << " BYTE \'" << lex.idtable.table[i].value.vstr.str << "\', 0\n";
				}
				if (lex.idtable.table[i].iddatatype == IT::INT)
				{
					ofile << " SDWORD " << lex.idtable.table[i].value.vint << endl;
				}
			}
		}
		ofile << ".data\n";
		for (int i = 0; i < lex.idtable.size; i++)
		{
			if (lex.idtable.table[i].idtype == IT::IDTYPE::V)
			{
				ofile << "\t" << lex.idtable.table[i].id;
				if (lex.idtable.table[i].iddatatype == IT::SYM)
				{
					ofile << " DWORD ?\n";
				}
				if (lex.idtable.table[i].iddatatype == IT::STR)
				{
					ofile << " DWORD ?\n";
				}
				if (lex.idtable.table[i].iddatatype == IT::INT)
				{
					ofile << " SDWORD 0\n";
				}
			}
		}

		stack<string> stk;
		string cyclecode = "", func_name = "";					// имя локальной функции
		bool flag_cycle = false,					// внутри локальной функции?
			flag_is = false,					// is
			flag_true = false,					
			flag_false = false;					

		ofile << "\n.code\n\n";
		for (int i = 0; i < lex.lextable.size; i++)
		{
			switch (lex.lextable.table[i].lexema)
			{
			case LEX_FUNCTION:
			{
				i++;
				ofile << (func_name = ITENTRY(i).id) << " PROC ";
				int j = i + 3;
				while (LEXEMA(j) != LEX_RIGHTTHESIS) // пока параметры не кончатся
				{
					if (lex.lextable.table[j].lexema == LEX_ID) // параметр
					{
						ofile << lex.idtable.table[lex.lextable.table[j].idxTI].id << " : ";
						if (ITENTRY(j).iddatatype == IT::IDDATATYPE::INT)
						{
							ofile << " SDWORD ";
						}
						else if (ITENTRY(j).iddatatype == IT::IDDATATYPE::SYM)
						{
							ofile << " DWORD ";
						}
						else
						{
							ofile << " DWORD ";
						}
					}
					if (LEXEMA(j) == LEX_COMMA)
					{
						ofile << ", ";
					}
					j++;
				}
				ofile << endl;
				break;
			}
			case LEX_MAIN:
			{
				ofile << "main PROC\n";
				break;
			}
			case LEX_RETURN:
			{
				ofile << "\tmov eax, " << ITENTRY(i + 1).id << "\n";
				ofile << "\tret\n";
				ofile << func_name + " ENDP\n";
				break;
			}
			case LEX_EQUAL:
			{
				int result_position = i - 1;
				while (lex.lextable.table[i].lexema != LEX_SEPARATOR)
				{
					
					switch (LEXEMA(i))
					{
					case LEX_ID:
					case LEX_LITERAL:
					{
						if (ITENTRY(i).iddatatype == IT::IDDATATYPE::INT)
						{
							ofile << "\tpush " << ITENTRY(i).id << endl;
							stk.push(lex.idtable.table[lex.lextable.table[i].idxTI].id);
							break;
						}
						else
						{
							ofile << "\tpush offset " << ITENTRY(i).id << endl;
							stk.push("offset" + (string)lex.idtable.table[lex.lextable.table[i].idxTI].id);
							break;
						}
					}
					case LEX_SUBST:
					{
						for (int j = 1; j <= (LEXEMA(i + 1) - '0') + 1; j++)
						{
							ofile << "\tpop edx\n";

						}
						for (int j = 1; j <= lex.lextable.table[i + 1].lexema - '0'; j++)
						{
							ofile << "\tpush " << stk.top() << endl;
							stk.pop();
						}
						ofile << "\t\tcall " << ITENTRY(i - (lex.lextable.table[i + 1].lexema - '0') - 1).id << "\n\tpush eax\n";
						break;
					}
					case LEX_STAR:
					{
						ofile << "\tpop eax\n\tpop ebx\n";
						ofile << "\tmul ebx\n\tpush eax\n";
						break;
					}
					case LEX_PLUS:
					{
						ofile << "\tpop eax\n\tpop ebx\n";
						ofile << "\tadd eax, ebx\n\tpush eax\n";
						break;
					}
					case LEX_MINUS:
					{
						if (LEXEMA(i - 2) == LEX_EQUAL)
						{
							ofile << "\tmov eax, 0\n\tpop ebx\n";
							ofile << "\tsub eax, ebx\n\tpush eax\n";
							break;
						}
						ofile << "\tpop ebx\n\tpop eax\n";
						ofile << "\tsub eax, ebx\n\tpush eax\n";
						break;
					}
					case LEX_DIRSLASH:
					{
						ofile << "\tpop ebx\n\tpop eax\n";
						ofile << "\tcdq\n";
						ofile << "\tidiv ebx\n\tpush eax\n";
						break;
					}
					case LEX_PROCENT:
					{
						ofile << "\tpop ebx\n\tpop eax\n";
						ofile << "\tcdq\n";
						ofile << "\tidiv ebx\n\tpush edx\n";
						break;
					}
					}
					i++;
				}
				ofile << "\tpop " << ITENTRY(result_position).id << "\n";
				ofile << endl;
				break;
			}
			case LEX_NEWLINE: // перевод строки 
			{
				switch (ITENTRY(i + 1).iddatatype)
				{
				case IT::IDDATATYPE::INT:
					ofile << "\npush " << ITENTRY(i + 1).id << "\ncall outnumline\n";
					break;
				case IT::IDDATATYPE::SYM:
				case IT::IDDATATYPE::STR:
					if (ITENTRY(i + 1).idtype == IT::IDTYPE::L)
						ofile << "\npush offset " << ITENTRY(i + 1).id << "\ncall outstrline\n";
					else ofile << "\npush " << ITENTRY(i + 1).id << "\ncall outstrline\n";
					break;
				}
				break;
			}
			case LEX_WRITE: // вывод
			{
				switch (ITENTRY(i + 1).iddatatype)
				{
				case IT::IDDATATYPE::INT:
					ofile << "\npush " << ITENTRY(i+1).id << "\ncall outnum\n";
					break;
				case IT::IDDATATYPE::SYM:
				case IT::IDDATATYPE::STR:
					if (ITENTRY(i + 1).idtype == IT::IDTYPE::L) 
						ofile << "\npush offset " << ITENTRY(i + 1).id << "\ncall outstr\n";
					else ofile << "\npush " << ITENTRY(i + 1).id << "\ncall outstr\n";
					break;
				}
				break;
			}
			case LEX_IS: // условие
			{
				conditionnum++;
				flag_is = true;
				ofile << "\tmov edx, " << ITENTRY(i + 1).id << "\n\tcmp edx, " << ITENTRY(i + 3).id <<"\n";
				int j = i;
				char* right, *wrong;
				while (LEXEMA(j) != LEX_SQ_RBRACELET)
				{
					if (LEXEMA(j)==LEX_ISTRUE)
					{
						flag_true = true;
					}
					else if (LEXEMA(j) == LEX_ISFALSE)
					{
						flag_false = true;
					}
					j++;
				}
				if (LEXEMA(j + 1) == LEX_ISTRUE || LEXEMA(j + 1) == LEX_ISFALSE)
				{
					flag_true = true;
					flag_false = true;
				}
				switch (LEXEMA(i + 2))
				{
					//Инструкция JG выполняет короткий переход, если первый операнд БОЛЬШЕ второго операнда при выполнении операции сравнения с помощью команды CMP
					//jl если первый операнд меньше второго
					//Инструкция JZ выполняет короткий переход, если первый операнд РАВЕН второму операнду при выполнении операции сравнения с помощью команды CMP
					//jnz если не равны
				case LEX_MORE:
					right = "jg";  wrong = "jl"; 
					break;
				case LEX_LESS: 
					right = "jl";  wrong = "jg";  
					break;
				case LEX_EQUALS:   
					right = "jz";  wrong = "jnz";  
					break;
				case LEX_NOTEQUALS: 
					right = "jnz";  wrong = "jz"; 
					break;
				}
				if (flag_true) 
					ofile  << "\t"<< right << " right" <<conditionnum << "\n";
				if (flag_false) 
					ofile << "\t" << wrong << " wrong" <<conditionnum << "\n";
				ofile << "\t" << "jmp next" << conditionnum << "\n";
				i += 2;
				break;
			}
			case LEX_ISTRUE:
			{
				ofile << "right" << conditionnum << ":";
				break;
			}
			case LEX_ISFALSE:
			{
				ofile << "wrong" << conditionnum << ":";
				break;
			}
			case LEX_SQ_RBRACELET:
			{
				if (flag_is)
				{
					if (LEXEMA(i+1) != LEX_ISTRUE && LEXEMA(i+1) != LEX_ISFALSE)
					{
						ofile << "\nnext" << conditionnum << ":";
						flag_is = false;
						flag_true = false;
						flag_false = false;
					}
					else 
					{
						ofile << "\tjmp next" << conditionnum << "\n\n";
					}
				}
				if (flag_cycle)
				{
					flag_cycle = false;
					ofile << cyclecode;
					ofile << "continue" << cyclenum << ":";
				}
				break;
			}
			case LEX_WHILE:
			{
				flag_cycle = true;
				cyclecode.clear();
				cyclenum++;
				cyclecode = "\tmov edx, " + (string)ITENTRY(i + 1).id + "\n\tcmp edx, " + (string)ITENTRY(i + 3).id + "\n";
				char* right;
				switch (LEXEMA(i + 2))
				{
				case LEX_MORE:
					right = "jg"; 
					break;
				case LEX_LESS:
					right = "jl"; 
					break;
				case LEX_EQUALS:
					right = "jz";
					break;
				case LEX_NOTEQUALS:
					right = "jnz";
					break;
				}
				cyclecode +="\t" + (string)right + " cycle" + std::to_string(cyclenum) + "\n";
				ofile << cyclecode;
				ofile << "\t" << "jmp continue" << cyclenum << "\n";
				i += 2;
				break;
			}
			case LEX_DO:
			{
				ofile  << " cycle" << cyclenum << ":";
			}

			}
		}
		ofile << END;
		ofile.close();
	};
}