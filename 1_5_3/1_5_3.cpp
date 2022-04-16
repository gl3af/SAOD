#include <Windows.h>
#include <iostream>

struct Item
{
	int data;
	Item* left;
	Item* right;
} *root;

bool isFound = false;

void Init()
{
	root = nullptr;
}

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

Item* FindValue(Item* node, int value)
{
	if (!isFound)
	{
		if (node != nullptr)
		{
			if (node->data == value)
			{
				isFound = true;
				return node;
			}
			FindValue(node->left, value);
			FindValue(node->right, value);
		}
	}
}

void DeleteTree(Item* node)
{
	if (node == nullptr)
		return;
	DeleteTree(node->left);
	DeleteTree(node->right);
	delete node;
}

void AddNode(int add_value, int value)
{
	if (root == nullptr)
	{
		root = new Item;
		root->data = add_value;
		root->left = root->right = nullptr;
		std::cout << "Значение добавлено как вершина дерева\n";
		return;
	}
	auto add = new Item;
	add->data = add_value;
	add->left = add->right = nullptr;

	auto found = FindValue(root, value);
	if (found->left != nullptr and found->right != nullptr)
	{
		std::cout << "У вершины уже есть два потомка\n";
	}
	else if (found->left == nullptr and found->right == nullptr)
	{
		while(true)
		{
			std::cout << "Добавить влево или вправо? (1 или 0)\nВаш выбор: ";
			int choice = Input();
			if (choice == 1)
			{
				found->left = add;
				std::cout << "Добавлено!\n";
				break;
			}
			else if (choice == 0)
			{
				found->right = add;
				std::cout << "Добавлено!\n";
				break;
			}
			else
				std::cout << "Команда отсутствует!\n";
		}
	}
	else if (found->left != nullptr)
	{
		found->right = add;
		std::cout << "Значение добавлено как правый потомок\n";
	}
	else
	{
		found->left = add;
		std::cout << "Значение добавлено как левый потомок\n";
	}
}

void ShowStraight(Item* node, int level = 0)
{
	if (node == nullptr)
		return;
	for (int i = 0; i < level; i++)
		std::cout << "\t";
	std::cout << node->data << "\n";
	ShowStraight(node->left, level + 1);
	ShowStraight(node->right, level + 1);
}

void ShowSymmetry(Item* node, int level = 0)
{
	if (node == nullptr)
		return;
	ShowSymmetry(node->left, level + 1);
	for (int i = 0; i < level; i++)
		std::cout << "\t";
	std::cout << node->data << "\n";
	ShowSymmetry(node->right, level + 1);
}

void ShowBackSymmetry(Item* node, int level = 0)
{
	if (node == nullptr)
		return;
	ShowBackSymmetry(node->right, level + 1);
	for (int i = 0; i < level; i++)
		std::cout << "\t";
	std::cout << node->data << "\n";
	ShowBackSymmetry(node->left, level + 1);
}

void Menu()
{
	bool isWorking = true;
	int choice, key, add_value, value;
	while (isWorking)
	{
		std::cout << "1. Обход дерева\n2. Добавить потомка для заданной вершины\n3. Удаление дерева\n4. Поиск вершины со значением\n0. Выход\nВаш выбор: ";
		choice = Input();
		if (choice == 0)
			isWorking = false;
		else if (choice == 1)
		{
			if (root == nullptr)
			{
				std::cout << "Дерево пустое!\n";
				continue;
			}
			while (true)
			{
				std::cout << "Выберите вид обхода\n";
				std::cout << "1. Прямой\n2. Симметричный \n3. Обратно-симметричный\nВаш выбор: ";
				key = Input();
				if (key == 1)
				{
					ShowStraight(root);
					break;
				}
				else if (key == 2)
				{
					ShowSymmetry(root);
					break;
				}
				else if (key == 3)
				{
					ShowBackSymmetry(root);
					break;
				}
				else
					std::cout << "Команда отсутствует!\n";
			}
		}
		else if (choice == 2)
		{
			std::cout << "Введите значение потомка: ";
			add_value = Input();
			if (root != nullptr)
			{
				std::cout << "Введите значение вершины: ";
				value = Input();
				FindValue(root, value);
				if (isFound)
				{
					isFound = false;
					AddNode(add_value, value);
				}
				else
					std::cout << "Вершина с заданным значением отсутствует!\n";
			}
			else
			{
				AddNode(add_value, 0);
			}
			
		}
		else if (choice == 3)
		{
			if (root != nullptr)
			{
				DeleteTree(root);
				Init();
			}
			else
				std::cout << "Дерево и так пустое!\n";
		}
		else if (choice == 4)
		{
			std::cout << "Введите значение вершины: ";
			value = Input();
			FindValue(root, value);
			if (isFound)
			{
				isFound = false;
				std::cout << "Вершина с заданным значением присутствует!\n";
			}
			else
				std::cout << "Вершина с заданным значением отсутствует!\n";
		}
		else
			std::cout << "Команда отсутствует!\n";
	}
}

int main()
{
	Init();
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::cout << "Пустое дерево создано!\n";
	Menu();
}