#include "stdafx.h"
#include <iostream>
#include <ctime>
extern "C"
{

	int __stdcall power(int a, int b)
	{
		return pow(a, b);
	}
	int __stdcall random()
	{
		srand(time(NULL));
		int k = rand();
		return k;
	}
	int __stdcall outnum(int value)
	{
		std::cout << value;
		return 0;
	}
	int __stdcall outsym(char value)
	{
		std::cout << value;
		return 0;
	}
	int __stdcall outstr(char* ptr)
	{
		if (ptr == nullptr)
		{
			std::cout << std::endl;
		}
		for (int i = 0; ptr[i] != '\0'; i++)
			std::cout << ptr[i];
		return 0;
	}
}