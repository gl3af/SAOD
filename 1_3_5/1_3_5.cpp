#include <iostream>
#include <Windows.h>

struct Item
{
    int data;
    Item* next;
};

Item* head;
Item* stack;

void Init()
{
    head = new Item;
    head->next = nullptr;
    stack = nullptr;
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

bool FindValue(int value)
{
    auto current = head->next;
    while (current != nullptr)
    {
        if (current->data == value)
            return true;
        current = current->next;
    }
    return false;
}

Item* prevItem(int value)
{
    auto current = head->next;
    auto prev = head;
    while (current != nullptr)
    {
        if (current->data == value)
            return prev;
        prev = current;
        current = current->next;
    }
}

void AddBefore(int add_value, int value)
{
    auto prev = prevItem(value);
    auto add = new Item;
    add->data = add_value;
    add->next = prev->next;
    prev->next = add;
}

void AddAfter(int add_value, int value)
{
    auto add = new Item;
    add->data = add_value;
    if (head->next == nullptr)
    {
        head->next = add;
        add->next = nullptr;
    }
    else
    {
        auto prev = prevItem(value);
        add->next = prev->next->next;
        prev->next->next = add;
    }
}

void Show(bool isList)
{
    if (isList)
    {
        auto current = head->next;
        if (current == nullptr)
        {
            std::cout << "Список пуст!\n";
            return;
        }
        while (current != nullptr)
        {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << "\n";
    }
    else
    {
        auto current = stack;
        if (current == nullptr)
        {
            std::cout << "Вспомогательный список пуст!\n";
            return;
        }
        while (current != nullptr)
        {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << "\n";
    }
}

void Delete(int value, bool useStack)
{
    auto prev = prevItem(value);
    auto del = prev->next;
    prev->next = del->next;
    if (!useStack)
    {
        delete del;
    }
    else
    {
        if (stack == nullptr)
        {
            stack = new Item;
            stack->data = del->data;
            stack->next = nullptr;
        }
        else
        {
            del->next = stack;
            stack = del;
        }
    }
}

void Menu()
{
    int choice, value, key, add_value;
    bool isWorking = true;
    while (isWorking)
    {
        std::cout << "Доступные команды\n" << "1. Состояние списка\n" << "2. Добавить элемент в список\n";
        std::cout << "3. Удалить заданный элемент\n" << "4. Поиск заданного элемента\n" << "5. Состояние вспомогательного списка/стека\n" 
            << "0. Выход\n" << "Ваш выбор: ";
        choice = Input();
        if (choice == 0)
        {
            isWorking = false;
        }
        else if (choice == 1)
            Show(true);
        else if (choice == 2)
        {
            std::cout << "Введите значение: ";
            value = Input();
            if (head->next == nullptr)
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
                    else if (key == 0)
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
            std::cout << "Добавлено!\n";
        }
        else if (choice == 3)
        {
            if (head->next == nullptr)
                std::cout << "Cписок пуст! Удаление невозможно\n";
            else
            {
                std::cout << "Введите значение: ";
                value = Input();
                if (FindValue(value))
                {
                    while (true)
                    {
                        std::cout << "Удалить с использованием вспомогательного списка? (1 - Да, 0 - Нет)\nВаш выбор: ";
                        key = Input();
                        if (key == 1)
                        {
                            Delete(value, true);
                            break;
                        }
                        else if (key == 0)
                        {
                            Delete(value, false);
                            break;
                        }
                        else
                            std::cout << "Команда отсутствует, повторите попытку!\n";
                    }
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
        else if (choice == 5)
            Show(false);
        else std::cout << "Команда отсутствует\n";
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Init();
    Menu();
}