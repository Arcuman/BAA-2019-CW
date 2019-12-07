#pragma once
#include "pch.h"

#define LEX_SEPARATORS	 'S'	// �����������
#define	LEX_ID_TYPE    	 't'	// ���� ������		
#define	LEX_ID			 'i'	// ��������������		
#define	LEX_LITERAL		 'l'	// ��������		
#define	LEX_FUNCTION     'f'	// function		
#define	LEX_MAIN		 'm'	// main		
#define	LEX_SEPARATOR	 ';'	// ����������� ����������
#define	LEX_COMMA		 ','	// ����������� ���������� 		
#define	LEX_LEFTBRACE	 '{'	// ������ �����		
#define	LEX_BRACELET	 '}'	// ����� �����		
#define	LEX_SQ_BRACELET	 '['	// ����� �����		
#define	LEX_SQ_BRACELET	 ']'	// ����� �����		
#define	LEX_LEFTHESIS	 '('	// ������ ������ ����������		
#define	LEX_RIGHTTHESIS	 ')'	// ����� ������ ����������		
#define	LEX_PLUS		 '+'	// ��������	
#define	LEX_MINUS		 '-'	// ���������
#define	LEX_STAR		 '*'	// ���������
#define LEX_DIRSLASH	 '\\'	// �������
#define	LEX_EQUAL		 '='	// ������������				
#define LEX_IS			 '?'	// if:
#define LEX_WHILE		 'c'	// while:
#define LEX_ISTRUE		 'r'	// ������ ����
#define LEX_ISFALSE		 'w'	// �������� ����
#define LEX_DO			 'd'	// do
#define LEX_WRITE		 'o'	// �����
#define LEX_NEWLINE		 '^'	// ������� ������
#define LEX_RETURN		 'e'	// ����� �� �������
#define LEX_TYPE		 'n'	// ���������� ����������
#define LEX_MORE		 '>'	// �������� �� ������
#define LEX_LESS		 '<'	// �������� �� ������
#define LEX_EQUALS		 '&'	// �������� �� ���������
#define LEX_NOTEQUALS	 '!'	// �������� �� �����������
#define	LEXEMA_FIXSIZE   1	        //������ �������
#define	LT_MAXSIZE		 4096	    //������������ ���������� ����� � ��
#define	NULLDX_TI	 0xffffffff	//��� �������� ��
namespace LT		// ������� ������
{
	struct Entry	// ������ ������� ������
	{
		unsigned char lexema;	// �������
		int sn;							// ����� ������ � �������� ������
		int idxTI;						// ������ � ������� ��������������� ��� LT_TI_NULLIDX

		Entry();
		Entry(unsigned char lexema, int snn, int idxti = NULLDX_TI);

	};

	struct LexTable						// ��������� ������� ������
	{
		int maxsize;					// ������� ������� ������ < LT_MAXSIZE
		int size;						// ������� ������ ������� ������ < maxsize
		Entry* table;					// ������ ����� ������� ������
	};

	LexTable Create(		// ������� ������� ������
		int size			// ������� ������� ������ < LT_MAXSIZE
	);

	void Add(				// �������� ������ � ������� ������
		LexTable& lextable,	// ��������� ������� ������
		Entry entry			// ������ ������� ������
	);

	Entry GetEntry(			// �������� ������ ������� ������
		LexTable& lextable,	// ��������� ������� ������
		int n				// ����� ���������� ������
	);

	void Delete(LexTable& lextable);	// ������� ������� ������ (���������� ������)

	Entry writeEntry(					// ��������� ������ ������� ������
		Entry &entry,
		unsigned char lexema,
		int indx,
		int line
	);
	void showTable(LexTable lextable, Log::LOG &log);						// ����� ������� ������
	void writeLexTable(std::ostream *stream, LT::LexTable &lextable);		//������� ������� ������
	void writeLexemsOnLines(std::ostream *stream, LT::LexTable &lextable);	//������� ������� �� �������
};