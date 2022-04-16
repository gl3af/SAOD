#include <iostream>
#include <Windows.h>

struct Item
{
    int data;
    Item* next;
    Item* prev;
};

Item* head;

void Init()
{
    head = new Item;
    head->next = head;
    head->prev = head;
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

bool FindValue(int value, bool isStraight)
{
    if (isStraight)
    {
        auto current = head->next;
        while (current != head)
        {
            if (current->data == value)
                return true;
            current = current->next;
        }
    }
    else
    {
        auto current = head->prev;
        while (current != head)
        {
            if (current->data == value)
                return true;
            current = current->prev;
        }
    }
    return false;
}

Item* getItem(int value)
{
    auto current = head->next;
    while (current != head)
    {
        if (current->data == value)
            return current;
        current = current->next;
    }
}

void AddBefore(int add_value, int value)
{
    auto item = getItem(value);
    auto add = new Item;
    add->data = add_value;
    add->next = item;
    add->prev = item->prev;
    item->prev->next = add;
    item->prev = add;
}

void AddAfter(int add_value, int value)
{
    auto add = new Item;
    add->data = add_value;
    if (head->next == head)
    {
        head->next = add;
        head->prev = add;
        add->next = head;
        add->prev = head;
    }
    else
    {
        auto item = getItem(value);
        add->next = item->next;
        add->prev = item;
        item->next->prev = add;
        item->next = add;
    }
}

void Show(bool isStraight)
{
    if (isStraight)
    {
        auto current = head->next;
        while (current != head)
        {
            std::cout << current->data << "\n";
            current = current->next;
        }
    }
    else
    {
        auto current = head->prev;
        while (current != head)
        {
            std::cout << current->data << "\n";
            current = current->prev;
        }
    }
}

void Delete(int value)
{
    auto del = getItem(value);
    del->prev->next = del->next;
    del->next->prev = del->prev;
    
    delete del;
}

void Menu()
{
    int choice, value, key, add_value;
    bool isWorking = true;
    while (isWorking)
    {
        std::cout << "Доступные команды\n" << "1. Просмотр списка\n" << "2. Добавить элемент в список\n";
        std::cout << "3. Удалить заданный элемент\n" << "4. Поиск заданного элемента\n" << "0. Выход\n" << "Ваш выбор: ";
        choice = Input();
        if (choice == 0)
        {
            isWorking = false;
        }
        else if (choice == 1) 
        {
            if (head->next == head)
                std::cout << "Список пуст!\n";
            else 
            {
                while (true)
                {
                    std::cout << "В прямом или обратном направлении? (1 или 0)\nВаш выбор: ";
                    key = Input();
                    if (key == 1)
                    {
                        Show(true);
                        break;
                    }
                    else if (key == 0)
                    {
                        Show(false);
                        break;
                    }
                    else std::cout << "Команда отсутствует! Повторите попытку\n";
                }
            }
        }
        else if (choice == 2)
        {
            std::cout << "Введите значение: ";
            value = Input();
            if (head->next == head)
                AddAfter(value, 0);
            else
            {
                std::cout << "Добавить до или после? (1 или 0)\nВаш выбор: ";
                key = Input();
                if (key == 1)
                {
                    std::cout << "Введите значение до которого необходимо вставить: ";
                    add_value = Input();
                    if (FindValue(add_value, true))
                        AddBefore(value, add_value);
                    else std::cout << "Значение отсутствует!\n";
                }
                else if (key == 0)
                {
                    std::cout << "Введите значение после которого необходимо вставить: ";
                    add_value = Input();
                    if (FindValue(add_value, true))
                        AddAfter(value, add_value);
                    else
                        std::cout << "Значение отсутствует!\n";
                }
                else std::cout << "Команда отсутствует! Повторите попытку\n";
            }
            std::cout << "Добавлено!\n";
        }
        else if (choice == 3)
        {
            if (head->next == head)
                std::cout << "Cписок пуст! Удаление невозможно\n";
            else
            {
                std::cout << "Введите значение: ";
                value = Input();
                if (FindValue(value, true))
                {
                    std::cout << "Удалено!\n";
                    Delete(value);
                }
                else std::cout << "Значение отсутствует в списке!\n";
            }
        }
        else if (choice == 4)
        {
            std::cout << "Введите значение: ";
            value = Input();
            while (true)
            {
                std::cout << "В прямом или обратном направлении? (1 или 0)\nВаш выбор: ";
                key = Input();
                if (key == 1)
                {
                    if (FindValue(value, true))
                        std::cout << "Данное значение находится в списке!\n";
                    else
                        std::cout << "Данного значения нет в списке!\n";
                    break;
                }
                else if (key == 0)
                {
                    if (FindValue(value, false))
                        std::cout << "Данное значение находится в списке!\n";
                    else
                        std::cout << "Данного значения нет в списке!\n";
                    break;
                }
                else std::cout << "Команда отсутствует! Повторите попытку\n";
            }
        }
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