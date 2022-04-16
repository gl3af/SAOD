#include <iostream>
#include <chrono>
#include <Windows.h>

int N;

int Input()
{
	int a;
	while (!(std::cin >> a) || (std::cin.peek() != '\n'))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Ошибка ввода, попробуйте снова!\n";
	}
	return a;
}

int* GenerateArray(int* array)
{
	if (array != nullptr)
		delete[] array;
	array = new int[N];
	for (int i = 0; i < N; i++)
		array[i] = rand() % 100;

	return array;
}

int* CreateCopy(int* array)
{
	int* copy = new int[N];

	for (int i = 0; i < N; i++)
		copy[i] = array[i];

	return copy;
}

void Show(int* array)
{
	for (int i = 0; i < N; i++)
		std::cout << array[i] << " ";
	std::cout << "\n";
}

void Bubble(int* array)
{
	long long int compatisons = 0;
	long long int swaps = 0;
	int* copy = CreateCopy(array);

	auto start = std::chrono::steady_clock::now();
	for (int i = 0; i < N; ++i)
	{
		for (int j = i; j > 0; --j)
		{
			compatisons++;
			if (copy[j] < copy[j - 1])
			{
				int temp = copy[j];
				copy[j] = copy[j - 1];
				copy[j - 1] = temp;
				swaps++;
			}
		}
	}
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "Отсортированный массив\n";
	Show(copy);
	std::cout << "\nСравнений: " << compatisons << ", перестановок: " << swaps << "\n";
	std::cout << "Затраченное время: " << elapsed_seconds.count() << " секунд\n";

	delete[] copy;
}

void Insertion(int* array)
{
	long long int compatisons = 0;
	long long int swaps = 0;
	int* copy = CreateCopy(array);

	auto start = std::chrono::steady_clock::now();
	for (int i = 1; i < N; i++) 
	{
		int value = copy[i];
		int j = i - 1;
		compatisons++;

		while (j > -1 && value < copy[j]) 
		{
			copy[j + 1] = copy[j];
			if (j != i - 1)
				swaps++;
			j--;
			compatisons++;
		}
		if (copy[j + 1] != value)
		{
			copy[j + 1] = value;
			swaps++;
		}
	}
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "Отсортированный массив\n";
	Show(copy);
	std::cout << "\nСравнений: " << compatisons << ", перестановок: " << swaps << "\n";
	std::cout << "Затраченное время: " << elapsed_seconds.count() << " секунд\n";
}

void Selection(int* array)
{
	long long int compatisons = 0;
	long long int swaps = 0;
	int min = 0, min_index = 0;
	int* copy = CreateCopy(array);

	auto start = std::chrono::steady_clock::now();
	for (int i = 0; i < N; i++) 
	{
		min_index = i; min = copy[i];
		for (int j = i + 1; j < N; j++) 
		{
			if (copy[j] < min)
			{
				min_index = j;
				min = copy[j];
				compatisons++;
			}
		}
		if (copy[i] != min)
		{
			copy[min_index] = copy[i];
			copy[i] = min;
			swaps++;
		}
	}
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "Отсортированный массив\n";
	Show(copy);
	std::cout << "\nСравнений: " << compatisons << ", перестановок: " << swaps << "\n";
	std::cout << "Затраченное время: " << elapsed_seconds.count() << " секунд\n";
}

void Menu()
{
	int* array = nullptr;
	int choice;
	bool isWorking = true;
	while (isWorking)
	{
		std::cout << "1. Сгенерировать массив\n2. Сортировка обменом\n3. Сортировка вставками\n4. Сортировка выбором\n0. Выход\nВаш выбор: ";
		choice = Input();
		if (choice == 0)
			isWorking = false;
		else if (choice == 1)
		{
			std::cout << "Введите число элементов (до 10000): ";
			N = Input();
			while (N < 0 or N >= 10000)
			{
				std::cout << "Количество элементов введено неверно!\n";
				N = Input();
			}
			array = GenerateArray(array);
			std::cout << "Сгенерированный массив\n";
			Show(array);
		}
		else if (choice == 2)
			Bubble(array);
		else if (choice == 3)
			Insertion(array);
		else if (choice == 4)
			Selection(array);
		else
			std::cout << "Команда отсутствует!\n";
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(static_cast<unsigned int>(time(0)));
	Menu();
}