#include<iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;


void FillRand(int arr[], const int n);
void FillRand(int** arr, const int rows, const int cols);

void Print(int arr[], const int n);
void Print(int** arr, const int rows, const int cols);

int* push_back(int* arr, int& n, int value);
int* push_front(int* arr, int& n, int value);
int* insert(int* arr, int& n, int value, int index);			//вставляет значение в массив по индексу

int* pop_back(int* arr, int& n);
int* pop_front(int* arr, int& n);
int* erase(int* arr, int& n, int value, int index);				//удаляем элемент по индексу



//#define DYNAMIC_MEMORY_1
#define DYNAMIC_MEMORY_2


void main()
{
	setlocale(LC_ALL, "");
#ifdef DYNAMIC_MEMORY_1
	int n;
	cout << "Введите размер массива: "; cin >> n;
	int* arr = new int[n];
	FillRand(arr, n);
	Print(arr, n);

	int value;
	//int number;
	cout << "Введите добавляемое значение: "; cin >> value;
	arr = push_back(arr, n, value);
	//cout << "Введите количество добавляемых значений: "; cin >> number;
	Print(arr, n);

	cout << "Введите добавляемое значение: "; cin >> value;
	arr = push_front(arr, n, value);
	Print(arr, n);

	int index;

	cout << "Введите index добавляемого элемента: "; cin >> index;
	cout << "Введите добавляемое значение: "; cin >> value;
	arr = insert(arr, n, value, index);
	Print(arr, n);

	arr = pop_back(arr, n);
	Print(arr, n);

	arr = pop_front(arr, n);
	Print(arr, n);

	cout << "Введите индекс для удаления массива: "; cin >> index;

	arr = erase(arr, n, value, index);
	Print(arr, n);

	delete[] arr;
	//delete[] buffer;  
#endif // DYNAMIC_MEMORY_1

#ifdef DYNAMIC_MEMORY_2
	int rows, cols;
	cout << "Введите ко-во строк: "; cin >> rows;
	cout << "Введите ко-во элементов строки: "; cin >> cols;

	int** arr = new int* [rows];

	for (int i = 0; i < rows; i++)
	{
		arr[i] = new int[cols];
	}

	FillRand(arr, rows, cols);
	Print(arr, rows, cols);

	//1) удаляем строки
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}
	//2) Удаляем массив указателей
	delete[] arr;
#endif // DYNAMIC_MEMORY_2
}

void FillRand(int arr[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = rand() % 100;
	}
}
void FillRand(int** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = rand() % 100;
		}
	}
}

void Print(int arr[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;
}
void Print(int** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << arr[i][j] << "\t";
		}
		cout << endl;
	}
}

int* push_back(int* arr, int& n, int value)
{
	//создаем буферный массив нужного размера (на 1 элемент больше)
	int* buffer = new int[n + 1];
	//копируем все значения из исходного массива в буферный:
	for (int i = 0; i < n; i++)
	{
		buffer[i] = arr[i];
	}
	//удаляем исходный массив:
	delete[] arr;
	//подмняем адрес исходного массива адресом нового массива:
	arr = buffer;
	buffer = nullptr;	//NULL-pointer (указатель на ноль)
	//cout << typeid(nullptr).name() << endl;
	//И только после этого в массив "arr" можно добавить значение:
	arr[n] = value;
	//после добавления элемента в массив ко-во его элементов увеличивается на 1:
	n++;
	//Mission complete - элемент добавлен. 
	return arr;
}
int* push_front(int* arr, int& n, int value)
{
	int* buffer = new int[n + 1];   //1) присвоить буффер new int n + 1, создать буфферный массив int buffer разыменовать его и присвоить нью инт
	buffer[0] = value;				//2) добавить в массив буферный значение в нулевой элемент птм что front. Буфферный массив присвоить value (вэлью)
	for (int i = 0; i < n; i++)		//3) копировать значения из исходного массива в буфферный через цикл for
	{
		buffer[i + 1] = arr[i];
	}
	delete[] arr;					//4) удаляем старый массив
	arr = buffer;					//5) подменить адрес старого массива адресом нового
	n++;
	return arr;
}

int* insert(int* arr, int& n, int value, int index)
{
	int* buffer = new int[n + 1];
	for (int i = 0; i < index; i++)
	{
		buffer[i] = arr[i];
	}
	for (int i = index; i < n; i++)
	{
		buffer[i + 1] = arr[i];
	}
	delete[] arr;
	arr = buffer;
	arr[index] = value;				//добавяем значение, само значение кладем в массив 
	n++;
	return arr;
}

int* pop_back(int* arr, int& n)
{
	/*int* buffer = new int[n - 1];
	for (int i = 0; i < n - 1; i++)
	{
		buffer[i] = arr[i];
	}
	delete[] arr;
	arr = buffer;
	n--;
	return arr;*/

	int* buffer = new int[--n];
	for (int i = 0; i < n; i++) buffer[i] = arr[i];
	delete[] arr;
	return buffer;
}
int* pop_front(int* arr, int& n)
{
	int* buffer = new int[--n];
	for (int i = 0; i < n; i++)  buffer[i] = arr[i + 1];
	delete[] arr;
	return buffer;
}

int* erase(int* arr, int& n, int value, int index)
{
	while (index < 0 || index >= n)
	{
		cout << "Введите индекс для удаления массива: "; cin >> index;
	}
	int* buffer = new int[n - 1];
	for (int i = 0; i < index; i++) buffer[i] = arr[i];

	for (int i = index + 1; i < n; i++) buffer[i - 1] = arr[i];
	delete[] arr;
	n--;
	return buffer;
}