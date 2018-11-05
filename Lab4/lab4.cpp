#include "pch.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <Windows.h>
using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ofstream out("output.txt");
	char *strin = new char[80];
	cout << "|--------------------|----------------------------------------------|\n"
		"| Вид преобразования | Из входной строки удаляются все символы      |\n"
		"|                    | кроме латинских и русских.                   |\n"
		"|--------------------|----------------------------------------------|\n"
		"| Автор              | Давыдов А.А., группа 7304                    |\n"
		"|--------------------|----------------------------------------------|\n\n";
	cout << "Введите строку\n";
	if (!cin.getline(strin, 80))
	{
		cout << "Введено больше 80 символов" << endl;
		return 0;
	}
	char *strout = new char[strlen(strin) + 1];
	__asm
	{
		mov esi, strin
		mov edi, strout

		start :
		lodsb	// загрузка из esi в al
			test al, al	// сравнение al c '\0'
			je exit1
			cmp al, ' '
				je wrt
			cmp al, 'А'
			jl start
			cmp al, 'Я'
			jg check_rus_low
			jmp wrt
			check_rus_low:
				cmp al, 'а'
				jl start
				cmp al, 'я'
				jg check_latin_up
				jmp wrt
			check_latin_up:
				cmp al, 'A'	//сравнение с латинской A
				jl start	//считывание нового символа
				cmp al, 'Z'
				jg check_low_latin
				jmp wrt
			check_low_latin :
				cmp al, 'a'
				jl start
				cmp al, 'z'
				jg start
				//next instruction is wrt
		wrt:
			stosb //сохранение строковых данных из al в es:edi
			jmp start
		exit1:
			stosb	//сохранение строковых данных в edi 
	}
	cout << strout;
	out << strout;
	out.close();
	return 0;
}
