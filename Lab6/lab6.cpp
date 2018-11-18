#include "pch.h" 
#include <cstdlib> 
#include <iostream> 
#include "windows.h" 
#include "fstream" 
#include <ctime> 
#include <iomanip> 

using namespace std;

void generation(int *, int, int, int);
int compare(const void *, const void *);

extern"C"
{
	void poisk(int NumRanDat, int *arr, int *RG, int *kol, int NInt);

}
void out1(ofstream&out)
{
	cout << "Результат работы программы:" << endl;;
	out << "Результат работы программ:" << endl;
	cout << setw(15) << "Номер интервала ";
	cout << setw(20) << "Границы ";
	cout << setw(35) << "Количество чисел в интервале" << endl;
	out << setw(15) << "Номер интервала ";
	out << setw(20) << "Границы ";
	out << setw(35) << "Количество чисел в интервал" << endl;
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ofstream fout("output.txt");
	int NumRanDat, Xmin, Xmax, NInt, i, j;
	int *kol; //массив для подсчета количества повторений на интервале 
	int *arr; //массив псевдослучайных чисел 
	int *RG; //массив правых границ 
	int *LG; //массив левых границ 

	cout << "Введите длину массива псевдослучайных чисел (<16000)" << endl;
	cin >> NumRanDat;
	while ((NumRanDat >= 16000) || (NumRanDat <= 0)) { //проверка корректности введенного числа
			cout << "Неверная длина массива. Повторите ввод" << endl;
		cin >> NumRanDat; //считывание количества чисел 
	}
	arr = new int[NumRanDat]; //выделение памяти под массив псевдослучайных чисел 
	cout << "Введите начало диапазона изменений Xmin" << endl;
	cin >> Xmin; //считывание минимального значения диапазона 
	cout << "Введите конец диапазона изменений Xmax" << endl;
	cin >> Xmax; //считывание максимального значения диапазона 
	while (Xmin > Xmax) { //проверка соотношения между максимумом и минимумом 
		cout << "Неверное соотношение между максимумом и минимумом диапазона" << endl;
		cin >> Xmin;
		cin >> Xmax;
	}
	generation(arr, NumRanDat, Xmin, Xmax); //вызов функции для генерации массива псевдослучайных чисел
		cout << "Массив пссевдослучайных чисел:" << endl;
	fout << "Массив пссевдослучайных чисел:" << endl;
	for (i = 0; i < NumRanDat; i++) {
		cout << arr[i] << " ";
		fout << arr[i] << " ";
	}
	cout << endl;
	cout << "Введите количество интервалов (<24)" << endl;
	cin >> NInt; //считывание количества интервалов 
	while ((NInt < 0) || (NInt > 24) || (NInt >= (Xmax - Xmin))) //проверка корректности введенного числа
	{
	cout << "Неверное значение. Повторите ввод" << endl;
	cin >> NInt;
	}
	kol = new int[NInt]; //выделение памяти под массив повторений 
	RG = new int[NInt]; //выделение памяти под массив правых границ 
	LG = new int[NInt]; //выделение памяти под массив левых границ 
	cout << "Введите левые границы интервалов" << endl;
	if (NInt != 0)
	{
		LG[0] = Xmin; //крайняя левая граница-минимальное значение псевдослучайных чисел 
		i = 0, j = 1;
		for (; i < NInt - 1; i++, j++)
		{
			cin >> LG[j]; //считывание левых границ 
			while ((LG[j] < Xmin) || (LG[j] > Xmax)) //проверка корректности введенных левых границ
			{
			cout << "Неверное значение. Введите другое значение " << endl;
			cin >> LG[j];
			}
			RG[i] = LG[j] - 1; //заполняем массив правых границ 

		}
		RG[NInt - 1] = Xmax; //крайняя правая граница-максимальное значение псевдослучайных чисел
			qsort(LG, NInt, sizeof(int), compare); //сортировка массива левых границ по возрастанию
			qsort(RG, NInt, sizeof(int), compare); //сортировка массива правых границ по возрастанию

			for (int i = 0; i < NInt; i++)
			{
				kol[i] = 0; //обнуление массива частот 
			}
		poisk(NumRanDat, arr, RG, kol, NInt);//вызов функции для заполнения массива 
		out1(fout); //вызов функции для вывод сообщений на экран и записи их в файл 
		for (int i = 0; i < NInt; i++)
		{
			cout << setw(10) << i + 1 << setw(18) << "[" << LG[i] << "," << RG[i] << "]" << setw(25) << kol[i] << endl;
			fout << setw(10) << i + 1 << setw(18) << "[" << LG[i] << "," << RG[i] << "]" << setw(25) << kol[i] << endl;

		}
	}
	else
	{
		out1(fout);
		cout << setw(10) << 1 << setw(18) << "[" << Xmin << "," << Xmax << "]" << setw(25) << NumRanDat << endl;
		fout << setw(10) << 1 << setw(18) << "[" << Xmin << "," << Xmax << "]" << setw(25) << NumRanDat << endl;
	}
}

void generation(int *array, int size, int min, int max) {//функция для генерации массива псевдослучайных чисел

		int i = 0;
	srand(time(0));
	for (i = 0; i < size; i++) {
		array[i] = rand() % (max - min + 1) + min;
	}
}

int compare(const void *x1, const void *x2) {//функция для сравнения двух чисел, необходимая для корректной работы функции qsort

		return(*(int*)x1 - *(int*)x2);
}
