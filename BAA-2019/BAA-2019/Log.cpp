#include "pch.h"
namespace Log
{

	LOG getlog(wchar_t logfile[])
	{
		LOG temp;
		temp.stream = new std::ofstream(logfile);					//динамическое выделение ofstream и инициализация указателя на этот объект и открытие
		if (!temp.stream->is_open())
			throw ERROR_THROW(112);
		wcscpy_s(temp.logfile, logfile);							//копирование logfile в temp.logfile
		return temp;
	}

	void WriteLine(LOG log, const char * c, ...)
	{
		const char **ptr = &c;										//берем адрес-адреса
		while (strlen(*ptr))										//пока не встретим L""
		{
			*log.stream << *ptr;									// запись в файл параметра
			++ptr;													//перемещаемся на следующий параметр
		}
		*log.stream << std::endl;
	}
	void WriteLineConsole(char * c, ...)
	{
		char** ptr = &c;			// указатель для доступа к параметрам
		char* result;				// строка результата
		result = new char[15];
		int size = 0;
		while (strcmp(*ptr, "") != 0)
		{
			size_t slen = strlen(*ptr);
			result = (char*)realloc(result, size + slen);
			result[size] = '\0';
			size += slen; // size - ПОЛНЫЙ размер буфера
			strcat_s(result, size + 1, *ptr);
			ptr++;
		}
		std::cout << result << std::endl;	
	}

	void WriteLine(LOG log, const wchar_t * c, ...)
	{
		const wchar_t **ptr = &c;
		while (wcslen(*ptr))
		{
			char out[PARM_MAX_SIZE];
			size_t charsConverted = 0;								//функция преобразовавающая wchar_t* в char
			wcstombs_s(&charsConverted, out, *ptr, PARM_MAX_SIZE);	// 1-ый аргумент: Размер в байтах преобразованной строки, включая нулевой терминатор 2-
			*log.stream << out;										// запись в файл параметра	
			++ptr;
		}
		*log.stream << std::endl;
	}

	void WriteLog(LOG log)
	{
		time_t  t = time(nullptr);									// time_t = количество секунд time()- Текущее календарное время типа c 1 января 1970 
		tm  now ;														// структура содержащая сек мин час ...
		localtime_s(&now, &t);										//Преобразует time_t в календарное время, выраженное в местном времени в хранилище struct tm
		char date[PARM_MAX_SIZE];									//массив для вывода времени
		strftime(date, PARM_MAX_SIZE, "%d.%m.%Y %H:%M:%S", &now);	//фукнция преобразующая структуру tm в массив c макс кол-вом символов для копирования PARM_MAX_SIZE в формате day month year...
		*log.stream << "---- Протокол ------- Дата: " << date << std::endl;
	}

	void WriteParm(LOG log, Parm::PARM parm)
	{
		*log.stream << "---- Параметры -------" << std::endl;
		char out[PARM_MAX_SIZE];
		size_t charsConverted(0);
		wcstombs_s(&charsConverted, out, parm.log, PARM_MAX_SIZE);
		*log.stream << "-log: " << out << std::endl;
		wcstombs_s(&charsConverted, out, parm.out, PARM_MAX_SIZE);
		*log.stream << "-out: " << out << std::endl;
		wcstombs_s(&charsConverted, out, parm.in, PARM_MAX_SIZE);
		*log.stream << "-in: " << out << std::endl;
	}

	void WriteIn(LOG log, In::IN in)
	{
		*log.stream << "---- Исходные данные -----" << std::endl;
		*log.stream << "Количество символов: " << in.size << std::endl;
		*log.stream << "Проигнорировано:     " << in.ignor << std::endl;
		*log.stream << "Количество строк:    " << in.lines << std::endl;
	}
	void WriteError(std::ostream *stream, Error::ERROR e)
	{
		if (stream == NULL)
		{
			if (e.position.col == -1 || e.position.line == -1)
				std::cout << std::endl << "Ошибка N" << e.id << ": " << e.message << std::endl;
			else if (e.position.col == NULL)
				std::cout << std::endl << "Ошибка N" << e.id << ": " << e.message
				<< " Строка: " << e.position.line << std::endl;
			else
				std::cout << std::endl << "Ошибка N" << e.id << ": " << e.message
				<< " Строка: " << e.position.line
				<< " Позиция в строке: " << e.position.col	 << std::endl;
			system("pause");
		}
		else
		{
			if (e.position.col == -1 || e.position.line == -1)
				*stream << std::endl << "Ошибка N" << e.id << ": " << e.message;
			else if (e.position.col == NULL)
				*stream << std::endl << "Ошибка N" << e.id << ": " << e.message
				<< " Строка: " << e.position.line;
			else
				*stream << std::endl << "Ошибка N" << e.id << ": " << e.message
				<< " Строка: " << e.position.line
				<< " Позиция в строке: " << e.position.col;
			*stream << std::endl;
		}
	}

	void Close(LOG log)
	{
		if (log.stream != nullptr)									//если поток открыт
		{
			log.stream->close();
			delete log.stream;
		}
	}

}