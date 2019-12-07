// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

#ifndef PCH_H
#define PCH_H
#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <locale>
#include <cwchar>
#include <mbstring.h>
#include <stack>
#include <queue>
#include <vector>

#include "Log.h"
#include "Error.h"
#include "Parm.h"
#include "LT.h"
#include "IT.h"
#include "In.h"
#include "FST.h"
#include "Graphs.h"
#include "LexAnaliz.h"
#include "Greibach.h"
#include "MFST.h"
#include "Semantic.h"
#include "PolishNotation.h"
#include "Generator.h"
#endif PCH_H
