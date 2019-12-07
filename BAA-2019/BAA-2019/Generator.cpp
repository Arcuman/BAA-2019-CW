#include "pch.h"


using namespace std;

namespace Gener
{

	void CodeGeneration(Lex::LEX& lex, Parm::PARM& parm, Log::LOG& log)
	{
		ofstream ofile(parm.out);
		ofile << BEGIN;
		ofile << EXTERN;
		ofile << ".const\n";

		for (int i = 0; i < lex.idtable.size; i++)
		{
			if (lex.idtable.table[i].idtype == IT::L)
			{
				ofile << "\t" << lex.idtable.table[i].id;
				if (lex.idtable.table[i].iddatatype == IT::SYM)
				{
					ofile << " BYTE " << lex.idtable.table[i].value.symbol << ", 0\n";
				}
				if (lex.idtable.table[i].iddatatype == IT::STR)
				{
					ofile << " DWORD " << lex.idtable.table[i].value.vstr.str << ", 0\n";
				}
				if (lex.idtable.table[i].iddatatype == IT::INT)
				{
					ofile << " DWORD " << lex.idtable.table[i].value.vint << endl;
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
					ofile << " BYTE ?\n";
				}
				if (lex.idtable.table[i].iddatatype == IT::STR)
				{
					ofile << " WORD ?\n";
				}
				if (lex.idtable.table[i].iddatatype == IT::INT)
				{
					ofile << " DWORD 0\n";
				}
			}
		}

		stack<string> stk;
		int num_of_points = 0,
			num_of_ret = 0,
			num_of_ends = 0;
		string strret = "", func_name = "";					// имя локальной функции
		bool flag_func = false,					// внутри локальной функции?
			flag_ret = false,					// был ret?
			flag_body = false,					// внутри главной функции?
			flag_if = false,					// внутри if?
			flag_then = false,					// внутри then?
			flag_else = false;					// внутри then/else?

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
							ofile << " DWORD ";
						}
						else if (ITENTRY(j).iddatatype == IT::IDDATATYPE::SYM)
						{
							ofile << " BYTE ";
						}
						else
						{
							ofile << " WORD ";
						}
					}
					if (LEXEMA(i) == LEX_COMMA)
					{
						ofile << ", ";
					}
					j++;
				}
				flag_func = true;
				ofile << endl;
				break;
			}
			case LEX_MAIN:
			{
				flag_body = true;
				ofile << "main PROC\n";
				break;
			}
			case LEX_RETURN:
			{
				ofile << "mov eax, " << ITENTRY(i + 1).id << "\n";
				ofile << "ret\n";
				ofile << func_name + " ENDP\n" ;
				break;
			}
			case LEX_EQUAL:
			{
				int result_position = i - 1;
				while (lex.lextable.table[i].lexema != LEX_SEPARATOR)
				{

				}
				
			}
			}
		}

		ofile.close();
	};
}