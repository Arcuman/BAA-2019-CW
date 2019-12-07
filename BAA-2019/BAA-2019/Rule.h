#pragma once
#pragma once
#include "pch.h"
#define GRB_ERROR_SERIES 600
#define NS(n)	GRB::Rule::Chain::N(n)
#define TS(n)	GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)

namespace GRB
{
	Greibach greibach(NS('S'), TS('$'), 15,

		Rule(NS('S'), GRB_ERROR_SERIES, 2,						// �������� ��������� ���������	
			Rule::Chain(6, TS('t'), TS('f'), TS('i'), NS('P'), NS('T'), NS('S')),
			Rule::Chain(4, TS('m'), TS('{'), NS('K'), TS('}'))
		),

		Rule(NS('T'), GRB_ERROR_SERIES + 2, 4,								// ������ � ���� �������
			Rule::Chain(5, TS('{'), TS('e'), TS('l'), TS(';'), TS('}')),
			Rule::Chain(5, TS('{'), TS('e'), TS('i'), TS(';'), TS('}')),
			Rule::Chain(6, TS('{'), NS('K'), TS('e'), TS('i'), TS(';'), TS('}')),
			Rule::Chain(6, TS('{'), NS('K'), TS('e'), TS('l'), TS(';'), TS('}'))
		),
		Rule(NS('P'), GRB_ERROR_SERIES + 1, 2,								// �� ������ ������ ���������� �������	
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(2, TS('('), TS(')'))
		),

		Rule(NS('E'), GRB_ERROR_SERIES + 3, 2,								// ������ � ������ ���������� �������						
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('E')),
			Rule::Chain(2, TS('t'), TS('i'))
		),

		Rule(NS('F'), GRB_ERROR_SERIES + 4, 2,								// ������ � ������ �������						
			Rule::Chain(3, TS('('), NS('N'), TS(')')),
			Rule::Chain(2, TS('('), TS(')'))
		),

		Rule(NS('N'), GRB_ERROR_SERIES + 5, 4,								// ������ � ������ ���������� �������		
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('N')),
			Rule::Chain(3, TS('l'), TS(','), NS('N'))
		),

		Rule(NS('R'), GRB_ERROR_SERIES + 6, 4,								// ������ ��� �������������� �����/��������� ���������	
			Rule::Chain(2, TS('r'), NS('Y')),
			Rule::Chain(2, TS('w'), NS('Y')),
			Rule::Chain(4, TS('r'), NS('Y'), TS('w'), NS('Y')),
			Rule::Chain(4, TS('w'), NS('Y'), TS('r'), NS('Y'))
		),

		Rule(NS('Y'), GRB_ERROR_SERIES + 7, 1,								// ������ � ���� �����/��������� ���������			
			Rule::Chain(3, TS('['), NS('X'), TS(']'))
		),
		Rule(NS('Z'), GRB_ERROR_SERIES + 8, 4,								// ������ � ������� �����/��������� ���������	
			Rule::Chain(3, TS('i'), NS('L'), TS('i')),
			Rule::Chain(3, TS('i'), NS('L'), TS('l')),
			Rule::Chain(3, TS('l'), NS('L'), TS('l')),
			Rule::Chain(3, TS('l'), NS('L'), TS('i'))
		),

		Rule(NS('L'), GRB_ERROR_SERIES + 9, 4,								// �������� �������� ��������		
			Rule::Chain(1, TS('<')),
			Rule::Chain(1, TS('>')),
			Rule::Chain(1, TS('&')),
			Rule::Chain(1, TS('!'))
		),

		Rule(NS('A'), GRB_ERROR_SERIES + 10, 5,								// �������� �������������� ��������
			Rule::Chain(1, TS('+')),
			Rule::Chain(1, TS('-')),
			Rule::Chain(1, TS('*')),
			Rule::Chain(1, TS('%')),
			Rule::Chain(1, TS('/'))
		),
		Rule(NS('W'), GRB_ERROR_SERIES + 11, 9,								// ������ � ������������� ���������
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('W'), TS(')')),
			Rule::Chain(5, TS('('), NS('W'), TS(')'), NS('A'), NS('W')),
			Rule::Chain(2, TS('i'), NS('F')),
			Rule::Chain(2, TS('i'), NS('F')),
			Rule::Chain(3, TS('i'), NS('A'), NS('W')),
			Rule::Chain(3, TS('l'), NS('A'), NS('W')),
			Rule::Chain(4, TS('i'), NS('F'), NS('A'), NS('W'))
		),

		Rule(NS('K'), GRB_ERROR_SERIES + 12, 26,							// ������������ �������������� �����������
			Rule::Chain(7, TS('n'), TS('t'), TS('i'), TS('='), TS('i'), TS(';'), NS('K')),	// ���������� + ������������
			Rule::Chain(7, TS('n'), TS('t'), TS('i'), TS('='), TS('l'), TS(';'), NS('K')),	// ���������� + ������������
			Rule::Chain(7, TS('n'), TS('t'), TS('i'), TS('='), NS('W'), TS(';'), NS('K')),	// ���������� + ������������
			Rule::Chain(8, TS('n'), TS('t'), TS('i'), TS('='), TS('-'), TS('i'), TS(';'), NS('K')),	// ���������� + ������������ �����
			Rule::Chain(5, TS('n'), TS('t'), TS('i'), TS(';'), NS('K')),	// ����������
			Rule::Chain(5, TS('i'), TS('='), NS('W'), TS(';'), NS('K')),	// ������������

			Rule::Chain(4, TS('o'), TS('i'), TS(';'), NS('K')),				// �����
			Rule::Chain(4, TS('o'), TS('l'), TS(';'), NS('K')),				// �����
			Rule::Chain(4, TS('^'), TS('i'), TS(';'), NS('K')),						// ������� ������
			Rule::Chain(4, TS('^'), TS('l'), TS(';'), NS('K')),						// ������� ������
			Rule::Chain(4, TS('?'), NS('Z'), NS('R'), NS('K')),				// if
			Rule::Chain(5, TS('c'), NS('Z'), TS('d'), NS('Y'), NS('K')),				// while
			Rule::Chain(6, TS('i'), TS('='), TS('i'), NS('F'), TS(';'), NS('K')),	// ������������ c ������� ������ ������� 

			Rule::Chain(6, TS('n'), TS('t'), TS('i'), TS('='), TS('l'), TS(';')),	// ���������� + ������������
			Rule::Chain(6, TS('n'), TS('t'), TS('i'), TS('='), TS('i'), TS(';')),	// ���������� + ������������
			Rule::Chain(6, TS('n'), TS('t'), TS('i'), TS('='), NS('W'), TS(';')),	// ���������� + ������������
			Rule::Chain(7, TS('n'), TS('t'), TS('i'), TS('='), TS('-'), TS('i'), TS(';')),	// ���������� + ������������ ����
			Rule::Chain(4, TS('i'), TS('='), NS('W'), TS(';')),				// ������������
			Rule::Chain(4, TS('n'), TS('t'), TS('i'), TS(';')),				// ����������
			Rule::Chain(3, TS('o'), TS('i'), TS(';')),						// �����
			Rule::Chain(3, TS('o'), TS('l'), TS(';')),						// �����
			Rule::Chain(3, TS('^'), TS('l'), TS(';')),								// ������� ������
			Rule::Chain(3, TS('^'), TS('i'), TS(';')),								// ������� ������
			Rule::Chain(3, TS('?'), NS('Z'), NS('R')),						// if
			Rule::Chain(4, TS('c'), NS('Z'), TS('d'), NS('Y')),				// while
			Rule::Chain(5, TS('i'), TS('='), TS('i'), NS('F'), TS(';'))		// ������������ c ������� ������ ������� 
		),

		Rule(NS('X'), GRB_ERROR_SERIES + 13, 10,								// ������������ �������������� ����������� � ���� �����/��������� ���������	
			Rule::Chain(5, TS('i'), TS('='), NS('W'), TS(';'), NS('X')),	// ������������
			Rule::Chain(4, TS('o'), TS('i'), TS(';'), NS('X')),				// �����
			Rule::Chain(4, TS('o'), TS('l'), TS(';'), NS('X')),				// �����
			Rule::Chain(3, TS('^'), TS(';'), NS('X')),						// ������� ������
			Rule::Chain(6, TS('i'), TS('='), TS('i'), NS('F'), TS(';'), NS('K')),	// ������������ c ������� ������ ������� 

			Rule::Chain(4, TS('i'), TS('='), NS('W'), TS(';')),				// ������������
			Rule::Chain(3, TS('o'), TS('i'), TS(';')),						// �����
			Rule::Chain(3, TS('o'), TS('l'), TS(';')),						// �����
			Rule::Chain(2, TS('^'), TS(';')),								// ������� ������
			Rule::Chain(5, TS('i'), TS('='), TS('i'), NS('F'), TS(';'))		// ������������ c ������� ������ ������� 
		)
	);
}