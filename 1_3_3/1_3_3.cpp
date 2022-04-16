#include <iostream>
#include <Windows.h>

const int MAX_SIZE = 4;
int count = 0;

struct Item {
    int data;
    int next = -1;
};

Item list[MAX_SIZE + 1];

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

int FindSpace()
{
    for (size_t i = 1; i <= MAX_SIZE; i++)
        if (list[i].next == -1)
            return i;
}

bool FindValue(int value)
{
    for (size_t i = 1; i <= MAX_SIZE; i++)
        if (list[i].data == value)
            return true;

    return false;
}

int PrevIndex(int value)
{
    int current = list[0].next;
    int prev = 0;
    while (list[current].data != value)
    {
        prev = current;
        current = list[current].next;
    }
    return prev;
}

void Show()
{
    if (!count)
        std::cout << "Список пуст!\n";
    else
    {
        int current = list[0].next;
        while (current != 0)
        {
            std::cout << list[current].data << "\n";
            current = list[current].next;
        }
    }
}

void AddBefore(int value, int before)
{
    int space = FindSpace();
    list[space].data = value;
    int prev = PrevIndex(before);
    list[space].next = list[prev].next;
    list[prev].next = space;
    count++;
}

void AddAfter(int value, int after)
{
    if (count == 0)
    {
        list[1].data = value;
        list[1].next = 0;
        list[0].next = 1;
        count++;
        return;
    }
    int space = FindSpace();
    list[space].data = value;
    int prev = PrevIndex(after);

    if (list[list[prev].next].next == 0)
    {
        list[space].next = 0;
        list[list[prev].next].next = space;
    }
    else
    {
        list[space].next = list[list[prev].next].next;
        list[list[prev].next].next = space;
    }
    
    count++;
}

void Delete(int value)
{
    int prev = PrevIndex(value);
    int del = list[prev].next;
    list[prev].next = list[del].next;
    list[del].data = 0;
    list[del].next = -1;
    count--;
}

void Menu()
{
    int choice, value, key, add_value;
    bool isWorking = true;
    while (isWorking)
    {
        std::cout << "Доступные команды\n" << "1. Состояние списка\n" << "2. Добавить элемент в список\n";
        std::cout << "3. Удалить заданный элемент\n" << "4. Поиск заданного элемента\n" << "0. Выход\n" << "Ваш выбор: ";
        choice = Input();
        if (choice == 0)
        {
            isWorking = false;
        }
        else if (choice == 1)
            Show();
        else if (choice == 2)
        {
            if (count == MAX_SIZE)
                std::cout << "Список заполнен! Удалите элемент, чтобы добавить новый\n";
            else
            {
                std::cout << "Введите значение: ";
                value = Input();
                if (count == 0)
                    AddAfter(value, 0);
                else
                {
                    while (true)
                    {
                        std::cout << "Добавить до или после? (1 или 0)\nВаш выбор: ";
                        key = Input();
                        if (key == 1)
                        {
                            std::cout << "Введите значение до которого необходимо вставить: ";
                            add_value = Input();
                            if (FindValue(add_value))
                            {
                                AddBefore(value, add_value);
                                break;
                            }
                            else
                                std::cout << "Значение отсутствует!\n";
                        }
                        else if(key == 0)
                        {
                            std::cout << "Введите значение после которого необходимо вставить: ";
                            add_value = Input();
                            if (FindValue(add_value))
                            {
                                AddAfter(value, add_value);
                                break;
                            }
                            else
                                std::cout << "Значение отсутствует!\n";
                        }
                    }
                }
            }
        }
        else if (choice == 3)
        {
            if (count == 0)
                std::cout << "Cписок пуст! Удаление невозможно\n";
            else
            {
                std::cout << "Введите значение: ";
                value = Input();
                if (FindValue(value))
                {
                    Delete(value);
                    std::cout << "Удалено!\n";
                }
                else
                    std::cout << "Значения нет в списке!\n";
            }
        }
        else if (choice == 4) 
        {
            std::cout << "Введите значение: ";
            value = Input();
            if (FindValue(value))
                std::cout << "Данное значение находится в списке!\n";
            else
                std::cout << "Данного значения нет в списке!\n";
        }
        else std::cout << "Команда отсутствует\n";
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Menu();
}