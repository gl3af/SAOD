#include <iostream>
#include <cstdlib>
#include <time.h>
#include <Windows.h>

struct Item
{
    char value;
    Item* next;
};

char Input()
{
    char a;
    while (!(std::cin >> a) || (std::cin.peek() != '\n'))
    {
        std::cin.clear();
        while (std::cin.get() != '\n');
        std::cout << "Ошибка ввода, попробуйте снова!\n";
    }
    return a;
}

const int add_max = 3;
const int add_min = 1;
const int del_max = 3;
const int del_min = 1;
const int sleep_time = 300;

Item* first; 
Item* last;
int count = 0;

void Init()
{
    first = last = nullptr;
}

bool isEmpty()
{
    return first == nullptr;
}

void Show()
{
    if (isEmpty())
    {
        std::cout << "Очередь пуста\n";
        return;
    }
    auto current = first;
    while (current != nullptr)
    {
        std::cout << current->value << "\n";
        current = current->next;
    }
}

void Push(char value)
{
    if (isEmpty())
    {
        first = new Item();
        first->value = value;
        first->next = last;
        last = first;
        ++count;
        return;
    }
    auto added = new Item();
    added->value = value;
    last->next = added;
    last = added;
    ++count;
}

char Pop()
{
    char value = first->value;
    if (isEmpty())
    {
        std::cout << "Очередь пуста\n";
        return '!';
    }
    auto current = first;
    first = first->next;
    delete current;
    --count;
    if (count == 0)
        last = nullptr;
    return value;
}

void Clear()
{
    while (count)
        Pop();
    last = nullptr;
}

int main()
{
    Clear();
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Init();
    srand(time(0));
    int action, amount;
    char value;
    std::cout << "Начало работы программы. Генератор случайных чисел активирован\n";
    bool is_working = true;
    while (is_working)
    {
        Sleep(sleep_time);
        action = 1 + rand() % 100;
        if (action % 2 == 0)
        {
            std::cout << "Операция: Добавление\n";
            Sleep(sleep_time);
            amount = add_min + rand() % (add_max - add_min + 1);
            std::cout << "Кол-во элементов: " << amount << '\n';
            Sleep(sleep_time);
            for (size_t i = 0; i < amount; i++)
            {
                value = char(65 + rand() % 26);
                Push(value);
            }
            std::cout << "Успешно добавлено!\n";
        }
        else
        {
            std::cout << "Операция: Удаление\n";
            Sleep(sleep_time);
            amount = del_min + rand() % (del_max - del_min + 1);
            std::cout << "Кол-во элементов: " << amount << '\n';
            Sleep(sleep_time);
            if (isEmpty())
                std::cout << "Очередь пуста, удаление невозможно!\n";
            else if (amount > count)
            {
                std::cout << "Удален(-o) " << count << " элемент(-a). Удаление большего числа элементов невозможно\n";
                Clear();
            }
            else
            {
                for (size_t i = 0; i < amount; i++)
                    Pop();
                std::cout << "Успешно удалено!\n";
            }
        }
        Sleep(sleep_time);
        std::cout << "Состояние очереди:\n";
        Show();
        Sleep(sleep_time);
        while (true)
        {
            std::cout << "Продолжаем? [y/n]\nВаш выбор: ";
            char x = Input();
            if (tolower(x) == 'y')
                break;
            else if (tolower(x) == 'n')
            {
                is_working = false;
                break;
            }
            else
                std::cout << "Команда отсутствует. Повторите попытку\n";
        }
    }
    std::cout << "До встречи!\n";
        Clear();
}