#include <Windows.h>
#include <iostream>
#include <time.h>

struct Item 
{
	int data;
	Item* left;
	Item* right;
};

Item* root;

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

Item* AddTree(Item* node, int N)
{
	if (N == 0)
		return nullptr;
	else
	{
		int left = N / 2;
		int right = N - left - 1;
		auto add = new Item;
		add->data = rand() % 100;
		add->left = AddTree(add->left, left);
		add-> right = AddTree(add->right, right);
		return add;
	}
}

void ShowStraight(Item* node, int level = 0)
{
	if (root == nullptr)
	{
		std::cout << "Дерево пустое!\n";
		return;
	}
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
	if (root == nullptr)
	{
		std::cout << "Дерево пустое!\n";
		return;
	}
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
	if (root == nullptr)
	{
		std::cout << "Дерево пустое!\n";
		return;
	}
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
	int count;
	std::cout << "Введите число вершин: ";
	count = Input();
	root = AddTree(root, count);
	std::cout << "Идеально сбалансированное дерево создано!\n";
	std::cout << "Вывод в прямом порядке\n";
	ShowStraight(root);
	std::cout << "Вывод в симметричном порядке\n";
	ShowSymmetry(root);
	std::cout << "Вывод в обратно-симметричном порядке\n";
	ShowBackSymmetry(root);
}

int main()
{
	Init();
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(static_cast<unsigned int>(time(0)));
	Menu();
}