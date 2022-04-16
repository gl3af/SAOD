#include <iostream>
#include <time.h>
#include <Windows.h>

struct Item
{
    int value;
    Item* next;
};

Item* top;
Item* top_second;

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

inline void Init()
{
    top = nullptr;
    top_second = nullptr;
}

bool isEmpty(Item* top)
{   
    return top == nullptr;
}

void Show(Item* top)
{
    if (isEmpty(top))
        std::cout << "Стек пуст\n";
    else
    {
        Item* current = top;
        while (current != nullptr)
        {
            std::cout << current->value << "\n";
            current = current->next;
        }
    }
}

int Pop(bool useSecond)
{
    int value = top->value;
    Item* current = top;    
    top = top->next;
    if (useSecond)
    {
        current->next = top_second;
        top_second = current;
    }
    else
        delete current;
    return value;
}

void Push(bool useSecond, int value = 0)
{
    if (useSecond)
    {
        Item* current = top_second;
        top_second = top_second->next;
        current->next = top;
        top = current;
    }
    else
    {
        Item* current = new Item;
        current->value = value;
        current->next = top;
        top = current;
    }
}

void Clear()
{
    while (top_second)
        Push(true);
    while (top)
        Pop(false);
}

void Menu()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choice, comd, value;
    bool isWorking = true;
    while (isWorking)
    {
        std::cout << "Доступные команды\n" << "1. Состояние основного стека\n" << "2. Состояние вспомогательного стека\n";
        std::cout << "3. Добавить элемент в стек\n" << "4. Удалить элемент из стека\n";
        std::cout << "5. Добавить несколько случайных значений\n" << "0. Выход\n" << "Ваш выбор: ";
        choice = Input();
        if (choice == 0)
        {
            isWorking = false;
            Clear();
        }
        else if (choice == 1)
            Show(top);
        else if (choice == 2)
            Show(top_second);
        else if (choice == 3)
        {
            while (true)
            {
                std::cout << "1. Добавить новый элемент\n2. Добавить элемент из вспомогательного стека\nВаш выбор: ";
                comd = Input();
                if (comd == 1)
                {
                    std::cout << "Введите число: ";
                    value = Input();
                    Push(value,false);
                    break;
                }
                else if (comd == 2)
                {
                    if (isEmpty(top_second))
                        std::cout << "Вспомогательный стек пуст\n";
                    else
                        Push(true);
                    break;
                }
                else std::cout << "Команда отсутствует\n";
            }
        }
        else if (choice == 4)
        {
            if (isEmpty(top))
                std::cout << "Стек пуст! Удаление невозможно\n";
            else
            {
                while (true)
                {
                    std::cout << "1. Удалить элемент полностью\n2. Удалить элемент с добавлением в вспомогательный стек\nВаш выбор: ";
                    comd = Input();
                    if (comd == 1)
                    {
                        std::cout << "Значение: " << Pop(false) << "\n";
                        break;
                    }
                    else if (comd == 2)
                    {
                        std::cout << "Значение: " << Pop(true) << "\n";
                        break;
                    }
                    else std::cout << "Команда отсутствует\n";
                }
            }
        }
        else if (choice == 5)
        {
            int number;
            std::cout << "Введите кол-во элементов: ";
            number = Input();
            for (int i = 0; i < number; ++i)
                Push(false, rand());
        }
        else std::cout << "Команда отсутствует\n";
    }
}

int main()
{
    srand(static_cast<int>(time(0)));
    Init();
    Menu();
    return 0;
}