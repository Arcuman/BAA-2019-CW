#pragma once
#include "pch.h"

#define LEX_SEPARATORS	 'S'	// разделители
#define	LEX_ID_TYPE    	 't'	// типы данных		
#define	LEX_STDFUNC    	 'p'	// типы данных		
#define	LEX_ID			 'i'	// идентификаторы		
#define	LEX_LITERAL		 'l'	// литералы		
#define	LEX_FUNCTION     'f'	// function		
#define	LEX_MAIN		 'm'	// main		
#define	LEX_SEPARATOR	 ';'	// разделитель инструкций
#define	LEX_COMMA		 ','	// разделитель параметров 		
#define	LEX_LEFTBRACE	 '{'	// начало блока		
#define	LEX_BRACELET	 '}'	// конец блока		
#define	LEX_SQ_LBRACELET '['	// начало блока		
#define	LEX_SQ_RBRACELET ']'	// конец блока		
#define	LEX_LEFTHESIS	 '('	// начало списка параметров		
#define	LEX_RIGHTTHESIS	 ')'	// конец списка параметров		
#define	LEX_PLUS		 '+'	// сложение	
#define	LEX_MINUS		 '-'	// вычитание
#define	LEX_STAR		 '*'	// умножение
#define LEX_DIRSLASH	 '/'	// деление
#define LEX_PROCENT		 '%'	// остаток от деления
#define	LEX_EQUAL		 '='	// присваивание				
#define LEX_IS			 '?'	// if:
#define LEX_TILDA		 '~'	// if:
#define LEX_WHILE		 'c'	// while:
#define LEX_ISTRUE		 'r'	// ложный блок
#define LEX_ISFALSE		 'w'	// истинный блок
#define LEX_DO			 'd'	// do
#define LEX_WRITE		 'o'	// вывод
#define LEX_NEWLINE		 '^'	// перевод строки
#define LEX_RETURN		 'e'	// выход из функции
#define LEX_TYPE		 'n'	// объявления переменных
#define LEX_MORE		 '>'	// проверка на больше
#define LEX_LESS		 '<'	// проверка на меньше
#define LEX_EQUALS		 '&'	// проверка на равенство
#define LEX_NOTEQUALS	 '!'	// проверка на неравенство
#define	LEXEMA_FIXSIZE   1	        //размер лексемы
#define	LT_MAXSIZE		 4096	    //максимальное количество строк в ТЛ
#define LEX_SUBST		'@'
#define	NULLDX_TI	 0xffffffff	//нет элемента ТИ
namespace LT		// таблица лексем
{
	struct Entry	// строка таблицы лексем
	{
		unsigned char lexema;	// лексема
		int sn;							// номер строки в исходном тексте
		int idxTI;						// индекс в таблице идентификаторов или LT_TI_NULLIDX

		Entry();
		Entry(unsigned char lexema, int snn, int idxti = NULLDX_TI);

	};

	struct LexTable						// экземпляр таблицы лексем
	{
		int maxsize;					// емкость таблицы лексем < LT_MAXSIZE
		int size;						// текущий размер таблицы лексем < maxsize
		Entry* table;					// массив строк таблицы лексем
	};

	LexTable Create(		// создать таблицу лексем
		int size			// емкость таблицы лексем < LT_MAXSIZE
	);

	void Add(				// добавить строку в таблицу лексем
		LexTable& lextable,	// экземпляр таблицы лексем
		Entry entry			// строка таблицы лексем
	);

	Entry GetEntry(			// получить строку таблицы лексем
		LexTable& lextable,	// экземпляр таблицы лексем
		int n				// номер получаемой строки
	);

	void Delete(LexTable& lextable);	// удалить таблицу лексем (освободить память)

	Entry writeEntry(					// заполнить строку таблицы лексем
		Entry &entry,
		unsigned char lexema,
		int indx,
		int line
	);
	void showTable(LexTable lextable, Log::LOG &log);						// вывод таблицы лексем
	void writeLexTable(std::ostream *stream, LT::LexTable &lextable);		//вывести таблицу лексем
	void writeLexemsOnLines(std::ostream *stream, LT::LexTable &lextable);	//вывести лексемы по строкам
};