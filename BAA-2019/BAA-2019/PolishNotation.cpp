#include "pch.h"
using namespace std;

namespace Polish
{
	int getPriority(unsigned char e)
	{
		switch (e)
		{
		case LEX_LEFTHESIS: case LEX_RIGHTTHESIS: return 0;
		case LEX_COMMA: return 1;
		case LEX_PLUS: case LEX_MINUS: return 2;
		case LEX_STAR: case LEX_DIRSLASH: return 3;
		default: return -1;
		}
	}
	int searchExpression(Lex::LEX lex) {
		bool fl = false;
		Lex::LEX result;
		result.lextable = LT::Create(lex.lextable.size);
		result.idtable = IT::Create(lex.idtable.size);
		for (int i = 0,k =0; i < lex.lextable.size; i++) 
		{
			if (lex.lextable.table[i].lexema == LEX_EQUAL) {
				lex.lextable.size = PolishNotation(++i, lex);
			}
		}
		return lex.lextable.size;
	}
	int PolishNotation(int lextable_pos, Lex::LEX& lex)
	{
		stack<LT::Entry> stack;														// ���� ��� ��������
		queue<LT::Entry> queue;														// ������� ��� ���������
		LT::Entry temp;		temp.idxTI = -1;	temp.lexema = '#';	temp.sn = -1;	// ����������� �������, ��� ������ �������� ����� ���������� �� ���
		LT::Entry func;		func.idxTI = -1;	func.lexema = '@';	func.sn = -1;	// ������� ��� ������ �������
		int countLex = 0;															// ���������� ��������������� ������
		int countParm = 0;															// ���������� ���������� �������
		int posLex = lextable_pos;																// ���������� ����� ������� ����� ���������������
		bool findFunc = false;														// ���� ��� �������
		bool findComma = false;														// ���� ��� ������� (���-�� ���������� +2 �����)
		int skob = 0;
		int comma = 0;
		char* buf = new char[2];													// ����� ��� countParm � ��������� �������������
		for (int i = lextable_pos; lex.lextable.table[i].lexema != LEX_SEPARATOR; i++, countLex++)
		{
			switch (lex.lextable.table[i].lexema)
			{
			case LEX_ID:															// ���� �������������
			{
				if (lex.idtable.table[lex.lextable.table[i].idxTI].idtype == IT::F|| lex.idtable.table[lex.lextable.table[i].idxTI].idtype == IT::S)
					findFunc = true;
				queue.push(lex.lextable.table[i]);
				continue;
			}
			case LEX_LITERAL:															// ���� �������
			{
				queue.push(lex.lextable.table[i]);										// �������� � �������
				continue;
			}
			case LEX_LEFTHESIS:														// ���� (
			{
				skob++;
				stack.push(lex.lextable.table[i]);										// �������� �� � ����
				continue;
			}
			case LEX_RIGHTTHESIS:														// ���� )
			{
				skob++;
				if (findFunc)															// ���� ��� ����� �������, �� ������� () ���������� �� @ � ���-�� ����������
				{
					if (findComma)
					{
						countParm++;
					}
					func.sn = lex.lextable.table[i].sn;
					lex.lextable.table[i] = func;
					queue.push(lex.lextable.table[i]);									// ��������� � ������� ������� ������ �������
					_itoa_s(countParm, buf, 2, 10);										// �������������� ����� countParm � ������
					stack.top().lexema = buf[0];
					stack.top().idxTI = -1; stack.top().sn = lex.lextable.table[i].sn;						// ��������� �������, ����������� ���������� ���������� �������
					queue.push(stack.top());											// ��������� � ������� ��� �������
					findFunc = false;
				}
				else {
					while (stack.top().lexema != LEX_LEFTHESIS)						// ���� �� �������� (
					{
						queue.push(stack.top());										// ����������� �� ����� � �������
						stack.pop();

						if (stack.empty())
							return 0;
					}
				}
				stack.pop();															// ���������� ( ��� �������, ����������� ���������� ���������� �������
				continue;
			}
			case LEX_PLUS:															// ���� ���� ���������
			case LEX_MINUS:															// ���� ���� ���������
			case LEX_STAR:															// ���� ���� ���������
			case LEX_DIRSLASH:															// ���� ���� ���������
			{
				while (!stack.empty() && getPriority(lex.lextable.table[i].lexema) <= getPriority(stack.top().lexema))	// ���� ��������� �������� ��������� 
																							//������ ��� ����� ���������� ��������� � ������� �����
				{
					queue.push(stack.top());											// ����������� �� ����� � �������� ������
					stack.pop();
				}
				stack.push(lex.lextable.table[i]);
				continue;
			}
			case LEX_COMMA:																// ���� �������
			{
				findComma = true;
				comma++;
				countParm++;
				continue;
			}
			}
		}
		while (!stack.empty())															// ���� ���� �� ������
		{
			if (stack.top().lexema == LEX_LEFTHESIS || stack.top().lexema == LEX_RIGHTTHESIS)
				return 0;
			queue.push(stack.top());													// ����������� ��� � �������
			stack.pop();
		}
		while (countLex != 0)															// ������ �������� ��������� � ������� ������ �� �������� ������
		{
			if (!queue.empty()) {
				lex.lextable.table[posLex++] = queue.front();
				/*cout << lex.idtable.table[queue.front().idxTI].id << " ";			*/	// ����� � �������
				queue.pop();
			}
			else
			{
				lex.lextable.table[posLex++] = temp;
			}
			countLex--;
		}
		for (int i = 0; i < posLex; i++)												// �������������� �������� ������� ��������� � ������� ������ � ���������� �� ������� ���������������
		{
			if (lex.lextable.table[i].lexema == LEX_LITERAL)
				lex.idtable.table[lex.lextable.table[i].idxTI].idxfirstLE = i;
		}
		return lex.lextable.size;
	}


}

