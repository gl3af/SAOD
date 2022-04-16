#include <iostream>
#include <Windows.h>

std::string list[10];
int count = 0;

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

std::string stringInput()
{
    std::string a;
    while (true)
    {
        while (!(std::cin >> a) || (std::cin.peek() != '\n'))
        {
            std::cin.clear();
            while (std::cin.get() != '\n');
            std::cout << "Ошибка ввода, попробуйте снова!\n";
        }
        int digit = 0;
        int letter = 0;
        for (size_t i = 0; i < a.size(); i++)
        {
            if (isdigit(a[i])) digit++;
            else letter++;
        }
        if (digit > 0 and letter > 0)
            std::cout << "Ошибка ввода, попробуйте снова!\n";
        else
            break;
    }
    return a;
}

bool lessThan(std::string a, std::string b)
{
    if (isdigit(a[0]) && isdigit(b[0]))
    {
        if (a.size() < b.size())
            return true;
        else if (a.size() > b.size())
            return false;
        else
        {
            for (int i = 0; i < a.size(); ++i)
            {
                if (a[i] < b[i])
                    return true;
                else if (a[i] > b[i])
                    return false;
            }
            return true;
        }
    }
    int size = a.size();
    if (size > b.size())
        size = b.size();
    for (int i = 0; i < size; ++i)
    {
        if (a[i] < b[i])
            return true;
        else if (a[i] > b[i])
            return false;
    }
    return true;
}

void Push(std::string value)
{
    bool added = false;
    if (count == 0)
        list[0] = value;
    else
    {
        for (int i = 0; i < count; i++)
        {
            if (lessThan(value, list[i]))
            {
                added = true;
                for (int j = count; j > i; --j)
                    list[j] = list[j - 1];
                list[i] = value;
                break;
            }
        }
        if (!added)
            list[count] = value;
    }
    ++count;
}

std::string Pop(std::string value)
{
    bool finded = false;
    std::string result;
    for (int i = 0; i < count; i++)
    {
        if (list[i] == value)
        {
            finded = true;
            result = "найдено и удалено!";
            for (int j = i; j < count - 1; ++j)
                list[j] = list[j + 1];
            --count;
            break;
        }
    }
    if (!finded)
        result = "не найдено!";
    return result;
}

void Show() 
{
    if (count == 0) 
    {
        std::cout << "Список пуст!\n";
        return;
    }
    for (int i = 0; i < count; i++)
        std::cout << list[i] << "\n";
}

void Menu()
{
    int choice;
    std::string value;
    bool isWorking = true;
    while (isWorking)
    {
        std::cout << "Доступные команды\n" << "1. Состояние списка\n" << "2. Добавить элемент в список\n";
        std::cout << "3. Удалить заданного элемента\n" << "0. Выход\n" << "Ваш выбор: ";
        choice = Input();
        if (choice == 0)
        {
            isWorking = false;
        }
        else if (choice == 1)
            Show();
        else if (choice == 2)
        {
            if (count == 10)
                std::cout << "Список заполнен! Удалите элемент, чтобы добавить новый\n";
            else
            {
                std::cout << "Введите значение: ";
                value = stringInput();
                Push(value);
            }
        }
        else if (choice == 3)
        {
            if (count == 0)
                std::cout << "Cписок пуст! Удаление невозможно\n";
            else
            {
                std::cout << "Введите значение: ";
                value = stringInput();
                std::cout << "Значение " << Pop(value) << "\n";
            }
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
