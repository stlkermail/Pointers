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
int* insert(int* arr, int& n, int value, int index);			//��������� �������� � ������ �� �������

int* pop_back(int* arr, int& n);
int* pop_front(int* arr, int& n);
int* erase(int* arr, int& n, int value, int index);						//������� ������� �� �������

#define DYNAMIC_MEMORY_1
//#define DYNAMIC_MEMORY_2


void main()
{
	setlocale(LC_ALL, "");
#ifdef DYNAMIC_MEMORY_1
	int n;
	cout << "������� ������ �������: "; cin >> n;
	int* arr = new int[n];
	FillRand(arr, n);
	Print(arr, n);

	int value;
	//int number;
	cout << "������� ����������� ��������: "; cin >> value;
	arr = push_back(arr, n, value);
	//cout << "������� ���������� ����������� ��������: "; cin >> number;
	Print(arr, n);

	cout << "������� ����������� ��������: "; cin >> value;
	arr = push_front(arr, n, value);
	Print(arr, n);

	int index;

	cout << "������� index ������������ ��������: "; cin >> index;
	cout << "������� ����������� ��������: "; cin >> value;
	arr = insert(arr, n, value, index);
	Print(arr, n);

	arr = pop_back(arr, n);
	Print(arr, n);

	arr = pop_front(arr, n);
	Print(arr, n);

	cout << "������� ������ ��� �������� �������: "; cin >> index;

	arr = erase(arr, n, value, index);
	Print(arr, n);

	delete[] arr;
	//delete[] buffer;  
#endif // DYNAMIC_MEMORY_1

#ifdef DYNAMIC_MEMORY_2
	int rows, cols;
	cout << "������� ��-�� �����: "; cin >> rows;
	cout << "������� ��-�� ��������� ������: "; cin >> cols;

	int** arr = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new int[cols];
	}

	FillRand(arr, rows, cols);
	Print(arr, rows, cols);

	//1) ������� ������
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}
	//2) ������� ������ ����������
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
	//������� �������� ������ ������� ������� (�� 1 ������� ������)
	int* buffer = new int[n + 1];
	//�������� ��� �������� �� ��������� ������� � ��������:
	for (int i = 0; i < n; i++)
	{
		buffer[i] = arr[i];
	}
	//������� �������� ������:
	delete[] arr;
	//�������� ����� ��������� ������� ������� ������ �������:
	arr = buffer;
	buffer = nullptr;	//NULL-pointer (��������� �� ����)
	//cout << typeid(nullptr).name() << endl;
	//� ������ ����� ����� � ������ "arr" ����� �������� ��������:
	arr[n] = value;
	//����� ���������� �������� � ������ ��-�� ��� ��������� ������������� �� 1:
	n++;
	//Mission complete - ������� ��������. 
	return arr;
}
int* push_front(int* arr, int& n, int value)
{
	int* buffer = new int[n + 1];   //1) ��������� ������ new int n + 1, ������� ��������� ������ int buffer ������������ ��� � ��������� ��� ���
	buffer[0] = value;				//2) �������� � ������ �������� �������� � ������� ������� ��� ��� front. ��������� ������ ��������� value (�����)
	for (int i = 0; i < n; i++)		//3) ���������� �������� �� ��������� ������� � ��������� ����� ���� for
	{
		buffer[i + 1] = arr[i];
	}
	delete[] arr;					//4) ������� ������ ������
	arr = buffer;					//5) ��������� ����� ������� ������� ������� ������
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
	arr[index] = value;				//�������� ��������, ���� �������� ������ � ������ 
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
		cout << "������� ������ ��� �������� �������: "; cin >> index;
	}
	int* buffer = new int[n - 1];
	for (int i = 0; i < index; i++)
	{
		buffer[i] = arr[i];
	}
	for (int i = index + 1; i < n; i++)
	{
		buffer[i - 1] = arr[i];
	}
	delete[] arr;
	n--;
	return buffer;
}