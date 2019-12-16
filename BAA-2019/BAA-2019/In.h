#pragma once
#define IN_MAX_LEN_TEXT 1024*1024 //макс размер исходного кода 1MB
#define MAX_LEN_BUFFER  2048
#define IN_CODE_ENDL  '\n'
#define IN_CODE_SPACE  ' '
#define IN_CODE_NULL  '\0'
#define IN_CODE_QUOTE '\"'
#define IN_CODE_TILDA '~'
#define IN_CODE_TABLE {\
	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::P, IN::N, IN::F,  IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
	IN::P, IN::S, IN::Q, IN::T,  IN::T, IN::S, IN::S, IN::F,   IN::S, IN::S, IN::S, IN::S,  IN::S, IN::S, IN::T, IN::S,\
	IN::T, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,   IN::T, IN::T, IN::T, IN::S,  IN::S, IN::S, IN::S, IN::T,\
	IN::T, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,   IN::T, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,\
	IN::T, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,   IN::T, IN::T, IN::T, IN::S,  IN::K, IN::S, IN::T, IN::T,\
	IN::F, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,   IN::T, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,\
	IN::T, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,   IN::T, IN::T, IN::T, IN::S,  IN::T, IN::S, IN::QQ, IN::T,\
	\
	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F \
}
namespace In
{
	struct InWord
	{
		char word[MAX_LEN_BUFFER];	// слово
		int line;					// строка в исходном тексте
		int size ;			// количество слов
	};
	struct IN //исходные данные
	{
		/*
		S - ( ) { } [ ] < > ! & * + - = / , ;
		P - пробел, табуляция
		N (NEW)- новая строка
		F (FALSE)- запрещённый
		T (TRUE)- разрешённый
		I (IGNORED)- игнорируемый
		Q - "
		QQ - ~
		*/
		enum { T = 1024, F = 2048, I = 4096, S, Q, P, N ,QQ,K}; 
		int size = 0; //размер исходного кода 
		int lines = 1; //количество строк
		int ignor = 0;// количество проигнорированных строк
		unsigned char* text; //исходный текст
		int code[256] = IN_CODE_TABLE; 
		InWord* words;
	};
	IN getin(wchar_t infile[], std::ostream *stream);//Ввести и проверить входной поток 
	void addWord(InWord* words, char* word, int line);
	InWord* getWordsTable(std::ostream* stream, unsigned char* text, int* code, int textSize);

	void printTable(InWord* table);
}