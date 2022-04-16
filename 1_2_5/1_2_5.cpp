#include <iostream>
#include <time.h>
#include <Windows.h>

const int MAX_SIZE = 4;
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

bool isEmpty()
{
    return count == 0;
}

bool isFull()
{
    return count == MAX_SIZE;
}

void Status(int* arr, int first, int last)
{
    int current = first;
    if (isEmpty())
        std::cout << "Очередь пуста\n";
    else if (isFull())
    {
        while (current < count)
        {
            std::cout << arr[current] << "\n";
            ++current;
        }
        current %= MAX_SIZE;
        while (current < last)
        {
            std::cout << arr[current] << "\n";
            ++current;
        }
    }
    else
    {
        while (current != last)
        {
            std::cout << arr[current] << "\n";
            current = (current + 1) % MAX_SIZE;
        }
    }
}

int Pop(int* arr, int& first)
{
    --count;
    int value = arr[first++];
    first %= MAX_SIZE;
    return value;
}

void Push(int* arr, int value, int& last)
{
    ++count;
    arr[last++] = value;
    last %= MAX_SIZE;
}

void Menu(int* queue, int& first, int& last)
{
    int value, choice;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    bool isWorking = true;
    while (isWorking)
    {
        std::cout << "Доступные команды\n" << "1. Состояние кольцевой очереди\n" << "2. Добавить элемент в конец очерелди\n"; 
        std::cout << "3. Удалить элемент из начала очереди\n" << "0. Выход\n" << "Ваш выбор: ";
        choice = Input();
        if (choice == 0)
        {
            isWorking = false;
        }
        else if (choice == 1)
            Status(queue, first, last);
        else if (choice == 2)
        {
            if (isFull())
                std::cout << "Очередь заполнена! Удалите элемент, чтобы добавить новый\n";
            else
            {
                std::cout << "Введите значение: ";
                value = Input();
                Push(queue, value, last);
            }
        }
        else if (choice == 3)
        {
            if (isEmpty())
                std::cout << "Очередь пуста! Удаление невозможно\n";
            else std::cout << "Значение: " << Pop(queue, first) << "\n";
        }
        else std::cout << "Команда отсутствует\n";
    }
}

int main()
{
    int queue[MAX_SIZE];
    int first = 0;
    int last = 0;
    Menu(queue, first, last);
    return 0;
}