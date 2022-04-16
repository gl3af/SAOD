#include <iostream>
#include <Windows.h>

struct Item
{
    int data;
    Item* next;
};

struct MainItem
{
    MainItem* next;
    Item* head;
    int id;
};

int id = 1;
MainItem* Head;
int count = 0;

void Init()
{
    Head = new MainItem();
    Head->next = nullptr;
    Head->head = nullptr;
}

void Show()
{
    if (Head->next == nullptr)
    {
        std::cout << "Основной список пуст!\n";
        return;
    }
    std::cout << "В основном списке " << count << " списка(-ов):\n";
    auto current = Head->next;
    while (current != nullptr)
    {
        std::cout << current->id << ") ";
        auto item = current->head->next;
        if (item == nullptr)
        {
            std::cout << "Пуст\n";
            current = current->next;
        }
        else
        {
            while (item != nullptr)
            {
                std::cout << item->data << " ";
                item = item->next;
            }
            std::cout << "\n";
            current = current->next;
        }
    }
}

void FindValue(int value)
{
    int* lists = new int[count*count];
    int k = 0;
    auto current = Head->next;
    while (current != nullptr)
    {
        auto item = current->head->next;
        while (item != nullptr)
        {
            if (item->data == value)
                lists[k++] = current->id;
            item = item->next;
        }
        current = current->next;
    }
    if (k > 0)
    {
        std::cout << "Значение найдено в ";
        for (int j = 0; j < k; j++)
        {
            std::cout << lists[j];
            if (j < k - 1)
                std::cout << ", ";
        }
        std::cout << " списке/списках\n";
    }
    else
        std::cout << "Значение не найдено!\n";
}

MainItem* PrevList(int number)
{
    auto prev = Head;
    auto current = Head->next;
    while (current->id != number)
    {
        prev = current;
        current = current->next;
    }
    return prev;
}

MainItem* List(int number)
{
    auto current = Head->next;
    while (current->id != number)
    {
        current = current->next;
    }
    return current;
}

Item* PrevItem(int value, int number)
{
    auto current = Head->next;
    while (current->id != number)
    {
        current = current->next;
    }
    auto item = current->head->next;
    auto prev = current->head;
    while (item != nullptr)
    {
        if (item->data == value)
            return prev;
        prev = item;
        item = item->next;
    }
    return nullptr;
}

void AddListBefore(int number)
{
    auto add = new MainItem();
    add->head = nullptr;
    add->id = id++;
    auto prev = PrevList(number);
    add->next = prev->next;
    prev->next = add;
    auto item = new Item;
    add->head = item;
    item->next = nullptr;
    count++;
}

void AddListAfter(int number)
{
    auto add = new MainItem;
    auto item = new Item;
    add->head = item;
    add->id = id++;
    item->next = nullptr;
    count++;
    if (Head->next == nullptr)
    {
        Head->next = add;
        add->next = nullptr;
        return;
    }
    auto prev = PrevList(number);
    add->next = prev->next->next;
    prev->next->next = add;
}

void AddItemBefore(int add_value, int value, int number)
{
    auto add = new Item;
    add->data = add_value;
    auto prev = PrevItem(value, number);
    add->next = prev->next;
    prev->next = add;
    std::cout << "Добавлено!\n";
}

void AddItemAfter(int add_value, int value, int number)
{
    auto add = new Item();
    add->data = add_value;
    auto prev = PrevItem(value, number);
    if (List(number)->head->next == nullptr) // если подсписок пуст
    {
        List(number)->head->next = add;
        add->next = nullptr;
        return;
    }
    add->next = prev->next->next;
    prev->next->next = add;
    std::cout << "Добавлено!\n";
}

void DeleteItem(int value, int number)
{
    auto prev = PrevItem(value, number);
    if (prev == nullptr)
    {
        std::cout << "В этом списке заданный элемент отсутствует!\n";
        return;
    }
    auto del = prev->next;
    prev->next = del->next;
    
    delete del;
}

void DeleteList(int number)
{
    auto list = PrevList(number);
    auto del_list = list->next;
    auto head = del_list->head;
    while (head->next != nullptr)
    {
        DeleteItem(head->next->data, number);
    }
    list->next = del_list->next;
    count--;
    delete head->next, head, del_list;
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

void Menu()
{
    int choice, value, key, add_value, number;
    bool isWorking = true;
    while (isWorking)
    {
        std::cout << "Доступные команды\n" << "1. Вывод списка\n" << "2. Добавить пустой элемент-список в основной список\n";
        std::cout << "3. Добавить элемент в элемент-список\n" << "4. Поиск заданного элемента\n"; 
        std::cout << "5. Удалить заданный элемент из элемента-списка\n" << "6. Удалить элемент-список из основного списка\n" << "0. Выход\n" << "Ваш выбор: ";
        choice = Input();
        if (choice == 0)
        {
            isWorking = false;
        }
        else if (choice == 1)
            Show();
        else if (choice == 2)
        {
            if (count == 0)
                AddListAfter(0);
            else
            {
                std::cout << "Введите номер списка, до/после которого нужно вставить элемент-список: ";
                number = Input();
                if (number > count or number <= 0)
                    std::cout << "В списке всего " << count << " списков!\n";
                else
                {
                    while (true)
                    {
                        std::cout << "Вставить до или после? (1 или 0)\nВаш выбор: ";
                        key = Input();
                        if (key == 1)
                        {
                            AddListBefore(number);
                            break;
                        }
                        else if (key == 0)
                        {
                            AddListAfter(number);
                            break;
                        }
                        else
                            std::cout << "Команда отсутствует! Повторите попытку\n";
                    }
                }
            }
            std::cout << "Добавлено!\n";
        }
        else if (choice == 3)
        {
            if (count == 0)
                std::cout << "Основной список пуст!\n";
            else
            {
                std::cout << "Введите номер списка, в который хотите добавить элемент: ";
                number = Input();
                if (number > count or number <= 0)
                    std::cout << "В списке всего " << count << " списков!\n";
                else
                {
                    std::cout << "Введите значение элемента: ";
                    add_value = Input();
                    if(List(number)->head->next == nullptr)
                        AddItemAfter(add_value, 0, number);
                    else
                    {
                        std::cout << "Введите элемент, до/после которого хотите вставить заданный элемент: ";
                        value = Input();
                        auto prev = PrevItem(value, number);
                        if (prev == nullptr)
                            std::cout << "В этом списке заданный элемент отсутствует!\n";
                        else
                        {
                            while (true)
                            {
                                std::cout << "Вставить до или после? (1 или 0)\nВаш выбор: ";
                                key = Input();
                                if (key == 1)
                                {
                                    AddItemBefore(add_value, value, number);
                                    break;
                                }
                                else if (key == 0)
                                {
                                    AddItemAfter(add_value, value, number);
                                    break;
                                }
                                else
                                    std::cout << "Команда отсутствует! Повторите попытку\n";
                            }

                        }
                    }
                }
            }
        }
        else if (choice == 4)
        {
            if(count == 0)
                std::cout << "Основной список пуст!\n";
            else
            {
                std::cout << "Введите значение элемента: ";
                value = Input();
                FindValue(value);
            }
        }
        else if (choice == 5)
        {
            if (count == 0)
                std::cout << "Основной список пуст!\n";
            else
            {
                std::cout << "Введите номер списка, из которого хотите удалить элемент: ";
                number = Input();
                if (number > count or number <= 0)
                    std::cout << "В списке всего " << count << " списков!\n";
                else
                {
                    std::cout << "Введите значение элемента: ";
                    value = Input();
                    DeleteItem(value, number);
                }
            }
        }
        else if (choice == 6)
        {
            if (count == 0)
                std::cout << "Основной список пуст!\n";
            else
            {
                std::cout << "Введите номер списка, который хотите удалить: ";
                number = Input();
                if (number > count or number <= 0)
                    std::cout << "В списке всего " << count << " списков!\n";
                else
                    DeleteList(number);
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
    while (Head->next != nullptr)
        DeleteList(count);
    delete Head;
}