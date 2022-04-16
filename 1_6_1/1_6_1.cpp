#include <iostream>
#include <Windows.h>

struct Item
{
	Item* left;
	Item* right;
	int key;
	int count = 1;
} *root;

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

Item* getParent(int key)
{
	Item* parent = nullptr;
	auto current = root;

	while (current != nullptr)
	{
		if (key == current->key)
		{
			return parent;
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
}

Item* Find(int key) 
{
	Item* parent = nullptr;
	auto current = root;
	bool found = false;

	while (current != nullptr and !found)
	{
		if (key == current->key)
		{
			found = true;
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
	return current;
}

void DeleteItem(int key)
{
	auto found = Find(key);
	auto found_parent = getParent(key);

	if (found->left == nullptr and found->right == nullptr) // нет потомков
	{
		if (key > found_parent->key) // вершина - правый потомок родителя
			found_parent->right = nullptr;
		else // вершина - левый потомок родителя
			found_parent->left = nullptr;

		delete found;
	}
	else if (found->left != nullptr and found->right != nullptr) // есть оба потомка
	{
		auto current = found->left; // левое поддерево
		auto current_parent = found;
		while (current->right != nullptr) // идём до конца вправо (ближайшее наименьшее)
		{
			current_parent = current;
			current = current->right;
		}
		
		found->key = current->key;
		if (found != current_parent)
			current_parent->right = nullptr;
		else
			current_parent->left = nullptr;

		delete current;
	}
	else if (found->left != nullptr) // 1 потомок (левый)
	{
		if (key > found_parent->key) // вершина - правый потомок родителя
		{
			found_parent->right = found->left;
			delete found;
		}
		else // вершина - левый потомок родителя
		{
			found_parent->left = found->left;
			delete found;
		}
	}
	else // 1 потомок (правый)
	{
		if (key > found_parent->key) // вершина - правый потомок родителя
		{
			found_parent->right = found->right;
			delete found;
		}
		else // вершина - левый потомок родителя
		{
			found_parent->left = found->right;
			delete found;
		}
	}
}

Item* AddNode(Item* node, int key) // рекурсивное добавление
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

void AddItem(int key) // нерекурсивное добавление
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
	std::cout << node->key << "(" << node->count << ")" << "\n";
	ShowBackSymmetry(node->left, level + 1);
}

void DeleteTree(Item* node)
{
	if (node == nullptr)
		return;
	DeleteTree(node->left);
	DeleteTree(node->right);
	delete node;
}

void Menu()
{
	bool isWorking = true;
	int choice, value, key;
	while (isWorking)
	{
		std::cout << "1. Вывод дерева в обратно-симметричном порядке\n2. Добавление новой вершины\n" 
			<< "3. Добавление заданного числа вершин со случайными значениями ключей\n4. Удаление вершины с заданным значением ключа\n" 
			<< "5. Поиск вершины с заданным значением ключа\n6. Вывод вершин в одну строку\n0. Выход\nВаш выбор: ";
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
			if (root != nullptr)
			{
				while (true)
				{
					std::cout << "Добавить рекурсивно или нерекурсивно? (1 или 0): ";
					key = Input();
					if (key == 1)
					{
						AddNode(root, value);
						
					}
					else if (key == 0)
					{
						AddItem(value);
						break;
					}
					else
						std::cout << "Команда отсутствует!\n";
				}
			}
			else
				AddItem(value);
			std::cout << "Добавлено!\n";
		}
		else if (choice == 3)
		{
			if (root != nullptr)
			{
				DeleteTree(root);
				Init();
			}
			std::cout << "Введите число вершин: ";
			value = Input();
			for (int i = 0; i < value; i++)
			{
				AddItem(rand() % 101);
			}
			std::cout << "Выполнено!\n";
		}
		else if (choice == 4)
		{
			if (root != nullptr)
			{
				std::cout << "Введите ключ вершины: ";
				value = Input();
				DeleteItem(value);
			}
			else
				std::cout << "Дерево пустое!\n";
		}
		else if (choice == 5)
		{
			std::cout << "Введите значение ключа: ";
			value = Input();
			auto found = Find(value);
			if (found != nullptr)
			{
				std::cout << "Вершина с заданным значением присутствует!\n";
				std::cout << "Кол-во появлений: " << found->count << "\n";
			}
			else
				std::cout << "Вершина с заданным значением отсутствует!\n";
		}
		else if (choice == 6)
		{
			if (root != nullptr)
			{
				ShowLine(root);
				std::cout << "\n";
			}
			else
				std::cout << "Дерево пустое!\n";
		}
		else
			std::cout << "Команда отсутствует!\n";
	}
}

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	Init();
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::cout << "Пустое дерево создано!\n";
	Menu();
}