#pragma once
#pragma once
#include "pch.h"
#define GRB_ERROR_SERIES 600
#define NS(n)	GRB::Rule::Chain::N(n)
#define TS(n)	GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)

namespace GRB
{
	Greibach greibach(NS('S'), TS('$'), 16,

		Rule(NS('S'), GRB_ERROR_SERIES, 2,						// Неверная структура программы	
			Rule::Chain(6, TS('t'), TS('f'), TS('i'), NS('P'), NS('T'), NS('S')),
			Rule::Chain(4, TS('m'), TS('{'), NS('K'), TS('}'))
		),

		Rule(NS('T'), GRB_ERROR_SERIES + 2, 2,								// Ошибка в теле функции
			Rule::Chain(5, TS('{'), TS('e'), NS('V'), TS(';'), TS('}')),
			Rule::Chain(6, TS('{'), NS('K'), TS('e'), NS('V'), TS(';'), TS('}'))
		),
		Rule(NS('P'), GRB_ERROR_SERIES + 1, 2,								// Не найден список параметров функции	
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(2, TS('('), TS(')'))
		),

		Rule(NS('E'), GRB_ERROR_SERIES + 3, 2,								// Ошибка в списке параметров функции						
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('E')),
			Rule::Chain(2, TS('t'), TS('i'))
		),

		Rule(NS('F'), GRB_ERROR_SERIES + 4, 2,								// Ошибка в вызове функции						
			Rule::Chain(3, TS('('), NS('N'), TS(')')),
			Rule::Chain(2, TS('('), TS(')'))
		),

		Rule(NS('N'), GRB_ERROR_SERIES + 5, 4,								// Ошибка в списке параметров функции		
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('N')),
			Rule::Chain(3, TS('l'), TS(','), NS('N'))
		),

		Rule(NS('R'), GRB_ERROR_SERIES + 6, 4,								// Ошибка при констуировании цикла/условного выражения	
			Rule::Chain(2, TS('r'), NS('Y')),
			Rule::Chain(2, TS('w'), NS('Y')),
			Rule::Chain(4, TS('r'), NS('Y'), TS('w'), NS('Y')),
			Rule::Chain(4, TS('w'), NS('Y'), TS('r'), NS('Y'))
		),

		Rule(NS('Y'), GRB_ERROR_SERIES + 7, 1,								// Ошибка в теле цикла/условного выражения			
			Rule::Chain(3, TS('['), NS('X'), TS(']'))
		),
		Rule(NS('Z'), GRB_ERROR_SERIES + 8, 4,								// Ошибка в условии цикла/условного выражения	
			Rule::Chain(3, TS('i'), NS('L'), TS('i')),
			Rule::Chain(3, TS('i'), NS('L'), TS('l')),
			Rule::Chain(3, TS('l'), NS('L'), TS('l')),
			Rule::Chain(3, TS('l'), NS('L'), TS('i'))
		),

		Rule(NS('L'), GRB_ERROR_SERIES + 9, 4,								// Неверный условный оператор		
			Rule::Chain(1, TS('<')),
			Rule::Chain(1, TS('>')),
			Rule::Chain(1, TS('&')),
			Rule::Chain(1, TS('!'))
		),

		Rule(NS('A'), GRB_ERROR_SERIES + 10, 4,								// Неверный арифметический оператор
			Rule::Chain(1, TS('+')),
			Rule::Chain(1, TS('-')),
			Rule::Chain(1, TS('*')),
			Rule::Chain(1, TS('/'))
		),

		Rule(NS('V'), GRB_ERROR_SERIES + 11, 2,								// Неверное выражение. Ожидаются только идентификаторы и литералы
			Rule::Chain(1, TS('l')),
			Rule::Chain(1, TS('i'))
		),

		Rule(NS('W'), GRB_ERROR_SERIES + 12, 8,								// Ошибка в арифметичском выражении
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('W'), TS(')')),
			Rule::Chain(5, TS('('), NS('W'), TS(')'), NS('A'), NS('W')),
			Rule::Chain(2, TS('i'), NS('F')),
			Rule::Chain(3, TS('i'), NS('A'), NS('W')),
			Rule::Chain(3, TS('l'), NS('A'), NS('W')),
			Rule::Chain(4, TS('i'), NS('F'), NS('A'), NS('W'))
		),

		Rule(NS('K'), GRB_ERROR_SERIES + 13, 19,							// Недопустимая синтаксическая конструкция
			Rule::Chain(7, TS('n'), TS('t'), TS('i'), TS('='), NS('V'), TS(';'), NS('K')),	// декларация + присваивание
			Rule::Chain(7, TS('n'), TS('t'), TS('i'), TS('='), NS('W'), TS(';'), NS('K')),	// декларация + присваивание
			Rule::Chain(8, TS('n'), TS('t'), TS('i'), TS('='), TS('-'), TS('i'), TS(';'), NS('K')),	// декларация + присваивание отриц
			Rule::Chain(5, TS('n'), TS('t'), TS('i'), TS(';'), NS('K')),	// декларация
			Rule::Chain(5, TS('i'), TS('='), NS('W'), TS(';'), NS('K')),	// присваивание

			Rule::Chain(4, TS('o'), NS('V'), TS(';'), NS('K')),				// вывод
			Rule::Chain(3, TS('^'), TS(';'), NS('K')),						// перевод строки
			Rule::Chain(4, TS('?'), NS('Z'), NS('R'), NS('K')),				// if
			Rule::Chain(5, TS('c'), NS('Z'), TS('d'), NS('Y'), NS('K')),				// while
			Rule::Chain(6, TS('i'), TS('='), TS('i'), NS('F'), TS(';'), NS('K')),	// присваивание c помощью вызова функции 

			Rule::Chain(6, TS('n'), TS('t'), TS('i'), TS('='), NS('V'), TS(';')),	// декларация + присваивание
			Rule::Chain(6, TS('n'), TS('t'), TS('i'), TS('='), NS('W'), TS(';')),	// декларация + присваивание
			Rule::Chain(4, TS('i'), TS('='), NS('W'), TS(';')),				// присваивание
			Rule::Chain(4, TS('n'), TS('t'), TS('i'), TS(';')),				// декларация
			Rule::Chain(3, TS('o'), NS('V'), TS(';')),						// вывод
			Rule::Chain(2, TS('^'), TS(';')),								// перевод строки
			Rule::Chain(3, TS('?'), NS('Z'), NS('R')),						// if
			Rule::Chain(4, TS('c'), NS('Z'), TS('d'), NS('Y')),				// while
			Rule::Chain(5, TS('i'), TS('='), TS('i'), NS('F'), TS(';'))		// присваивание c помощью вызова функции 
		),

		Rule(NS('X'), GRB_ERROR_SERIES + 14, 8,								// Недопустимая синтаксическая конструкция в теле цикла/условного выражения	
			Rule::Chain(5, TS('i'), TS('='), NS('W'), TS(';'), NS('X')),	// присваивание
			Rule::Chain(4, TS('o'), NS('V'), TS(';'), NS('X')),				// вывод
			Rule::Chain(3, TS('^'), TS(';'), NS('X')),						// перевод строки
			Rule::Chain(6, TS('i'), TS('='), TS('i'), NS('F'), TS(';'), NS('K')),	// присваивание c помощью вызова функции 

			Rule::Chain(4, TS('i'), TS('='), NS('W'), TS(';')),				// присваивание
			Rule::Chain(3, TS('o'), NS('V'), TS(';')),						// вывод
			Rule::Chain(2, TS('^'), TS(';')),								// перевод строки
			Rule::Chain(5, TS('i'), TS('='), TS('i'), NS('F'), TS(';'))		// присваивание c помощью вызова функции 
		)
	);
}