#include <Windows.h>
#include <iostream>

struct Item
{
	Item* left;
	Item* right;
	int key;
	int count = 1;
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
			if (node->key == value)
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

Item* AddNode(Item* node, int key)
{
	if (node == nullptr)
	{
		node = new Item;
		node->key = key;
		node->left = node->right = nullptr;
	}
	else if (node->key == key)
		node->count++;
	else if(key < node->key)
		node->left = AddNode(node->left, key);
	else
		node->right = AddNode(node->right, key);
	return node;
}

void AddItem(int key)
{
	if (root == nullptr)
	{
		root = new Item;
		root->key = key;
		root->left = root->right = nullptr;
		return;
	}
	Item* parent = nullptr;
	auto current = root;

	while (current != nullptr)
	{
		if (key ==  current->key)
		{
			current->count++;
			return;
		}
		else if (key < current->key)
		{
			parent = current;
			current = current->left;
		}
		else
		{
			parent = current;
			current = current->right;
		}
	}
	
	auto add = new Item;
	add->key = key;
	add->left = add->right = nullptr;
	if (key < parent->key)
		parent->left = add;
	else
		parent->right = add;
}

void ShowLine(Item* node)
{
	if (node == nullptr)
		return;
	ShowLine(node->left);
	std::cout << node->key << "(" << node->count << ")" << " ";
	ShowLine(node->right);
}

void ShowBackSymmetry(Item* node, int level = 0)
{
	if (node == nullptr)
		return;
	ShowBackSymmetry(node->right, level + 1);
	for (int i = 0; i < level; i++)
		std::cout << "\t";
	std::cout << node->key << "\n";
	ShowBackSymmetry(node->left, level + 1);
}

void Menu()
{
	bool isWorking = true;
	int choice, key, add_value, value;
	while (isWorking)
	{
		std::cout << "1. Вывод дерева в обратно-симметричном порядке\n2. Добавление новой вершины\n3. Удаление вершины с заданным значением ключа\n" 
			<< "4. Поиск вершины с заданным значением ключа\n5. Вывод вершин в одну строку\n0. Выход\nВаш выбор: ";
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
			ShowBackSymmetry(root);
		}
		else if (choice == 2)
		{
			std::cout << "Введите значение ключа: ";
			value = Input();
			//root = AddNode(root, value); - рекурсия
			for (int i = 0; i < 90; i++)
			{
				AddItem(rand() % 101);
			}
		}
		else if (choice == 3)
		{
			if (root != nullptr)
			{
				
			}
			else
				std::cout << "Дерево пустое!\n";
		}
		else if (choice == 4)
		{
			std::cout << "Введите значение ключа: ";
			value = Input();
			FindValue(root, value);
			if (isFound)
			{
				isFound = false;
				auto found = FindValue(root, value);
				std::cout << "Вершина с заданным значением присутствует!\n";
				std::cout << "Кол-во появлений: " << found->count << "\n";
			}
			else
				std::cout << "Вершина с заданным значением отсутствует!\n";
		}
		else if (choice == 5)
			ShowLine(root);
		else
			std::cout << "Команда отсутствует!\n";
	}
}

int main()
{
	int list[5];
	for (auto item : list)
	{

	}
	Init();
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::cout << "Пустое дерево создано!\n";
	Menu();
}