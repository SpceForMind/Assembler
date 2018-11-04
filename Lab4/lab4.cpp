
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

int main()
{
	ofstream out("output.txt");
	char *strin = new char[80];
	cout << "|--------------------|----------------------------------------------|\n"
		"| Вид преобразования | Из входной строки удаляются все символы      |\n"
		"|                    | кроме латинских и русских.                   |\n"
		"|--------------------|----------------------------------------------|\n"
		"| Автор              | Давыдов А.А., группа 7304                    |\n"
		"|--------------------|----------------------------------------------|\n\n";
	cout << "Введите строку\n";
	if(!cin.getline(strin, 80))
	{
		cout << "Введено больше 80 символов" << endl;
		return 0;
	}
	char *strout = new char[strlen(strin) + 1];
__asm
	{
		mov esi, strin
		mov edi, strout
		
		start:
			lodsb	// загрузка из esi в al
			test al, al	// сравнение al c '\0'
			je exit
			cmp al, 'A'	//сравнение с латинской A
			jle start	//считывание нового символа
			cmp al, 'Z'
			jg check_low_latin
				stosb	//сохранение строковых данных из al в es:edi
				jmp start
			check_low_latin:
				cmp al, 'a'
				jl start
				cmp al, 'z'
				jg check_rus_up
				stosb
				jmp start
			check_rus_up:
				cmp al, 'А'
				jl start
				cmp al, 'Я'
				jg check_rus_low
				stosb
				jmp start
			check_rus_low:
				cmp al, 'а'
				jl start
				cmp al, 'я'
				jg start
				stosb
				jmp start
		exit:
			stosb	//сохранение строковых данных в edi 
	}
	return 0;
}
