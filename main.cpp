#include <iostream>

using namespace std;
    
// Тип данных, описывающий каждый отдельно взятый узел списка
struct Node
{
    int info;     // полезная информация, хранящаяся в этом узле
    Node * next;  // адрес следующего узла списка
                  // (nullptr, если данный элемент является последним)
};

// Распечатать список
void print_list(Node * top)
{
    Node * p = top;  // Адрес текущего элемента списка
    while (p != nullptr) {
        cout << p->info << " ";  // Печатаем полезную информацию текущего узла
        p = p->next;  // Адрес следующего узла становится текущим
    }
}


// Функция, проверяющая, что все элементы списка с вершиной `top`
// упорядочены по неубыванию первой цифры.
bool list_is_sorted_by_first_digit(Node * top)
{
    Node * p = top; // Адрес текущего узла списка
    int first_digit1, first_digit2;

    while (p->next != nullptr) {
        first_digit1 = p->info;
        while (first_digit1 >= 10) {
            first_digit1 /= 10;
        }
        first_digit2 = p->next->info;
        while (first_digit2 >= 10) {
            first_digit2 /= 10;
        }
        // Сравниваем числа в текущем узле и следующем
        if (first_digit1 > first_digit2)
            return false;
        else
            p = p->next;  // Адрес следующего узла становится текущим
    }

    return true;
}

// Функция, проверяющая, что все элементы списка с вершиной `top`
// упорядочены по неубыванию последней цифры.
bool list_is_sorted_by_last_digit(Node * top)
{
    Node * p = top; // Адрес текущего узла списка
    int last_digit1, last_digit2;

    while (p->next != nullptr) {
        last_digit1 = p->info%10;
        last_digit2 = p->next->info%10;
        // Сравниваем числа в текущем узле и следующем
        if (last_digit1 > last_digit2)
            return false;
        else
            p = p->next;  // Адрес следующего узла становится текущим
    }

    return true;
}

// Отсортировать список по неубыванию (алгоритм сортировки обменами)
void sort_list(Node * top)
{
    for (Node * a = top; a->next != nullptr; a = a->next)
        for (Node * b = a->next; b != nullptr; b = b->next)
            if (a->info > b->info) swap(a->info, b->info);
}

// Проверяем входит ли цифры 6 и 9 и возвращаем true если да, чтобы дублировать этот элемент
bool duplicate_digit(int remdig)
{
    int digit;
    while (remdig >= 1) {
        digit = remdig%10;
        if (digit == 6 or digit == 9) {
            return true;
        }
       remdig /= 10;
    }
    return false;
}

// Продублировать в списке все элементы, содержащие цифры 6 и 9
void duplicate_numbers(Node * top)
{
    Node * p = top;
    while (p != nullptr) {
        // Если число в текущем узле делится на 3
        if (duplicate_digit(p->info)) {
            Node * q = new Node;  // Создаём новый узел
            q->info = p->info;    // и заполняем содержимое,
            q->next = p->next;    // а также прописываем адреса.
            p->next = q;
            p = q->next;
        }
        else {
            p = p->next;  // Иначе адрес следующего узла становится текущим.
        }
    }
}

// Проверяем входит ли цифры 2,4 и 6 и возвращаем true если нет, чтобы удалить этот элемент
bool deleted_digit(int remdig)
{
    int digit;
    while (remdig >= 1) {
        digit = remdig%10;
        if (digit == 2 or digit == 4 or digit == 6) {
            return false;
        }
       remdig /= 10;
    }
    return true;
}


// Удалить из списка все элементы, в которые не входят цифры 2,4 и 6
void remove_numbers(Node * &top)
{
     // Если удаляемое число расположено на вершине
    while (top != nullptr && deleted_digit(top->info)) {
        Node * temp = top->next;
        delete top;
        top = temp;
    }

    Node * p = top;
    while (p != nullptr && p->next != nullptr) {
        Node * temp = p->next;
        if (deleted_digit(temp->info)) {
            p->next = temp->next;
            delete temp;
        }
        else {
            p = temp;
        }
    }
}

int main()
{
    // Объявим переменную, в которой будет храниться адрес
    // первого узла списка (то есть адрес его вершины).
    // Изначально список пуст и узлов у него нет, даже вершины.
    // Поэтому top вначале равняется nullptr.
    Node * top = nullptr;

    int n;    // Количество элементов последовательности,
    cin >> n; // которое мы предварительно читаем с клавиатуры.

    // Первый элемент последовательности читаем отдельно, потому что
    // он разместится в вершине списка.
    int x;
    cin >> x;

    // Создаём вершину списка и размещаем в ней число `x`.
    top = new Node;
    top->info = x;
    top->next = nullptr;

    // Объявим вспомогательную переменную `pp`, в которой будем
    // хранить адрес последнего узла списка.
    // Пока что последний совпадает с первым.
    Node * pp = top;

    // Все остальные элементы последовательности читаем в цикле.
    for (int i = 1; i < n; i++) {
        cin >> x;
        Node * p = new Node;  // Создаём новый узел и получаем его адрес
        pp->next = p;  // Записываем адрес нового узла у предыдущего
        p->info = x;  // Записываем прочитанное число в новый узел
        p->next = nullptr;  // Пока что новый узел последний, и следующего у него нет.
        pp = p;  // на следующей итерации цикла новый узел станет предыдущим
    }

    cout << "Введённый список: ";
    print_list(top);

    cout << endl;

    if (list_is_sorted_by_first_digit(top) or list_is_sorted_by_last_digit(top)) {
        remove_numbers(top);
        duplicate_numbers(top);
        cout << "Список после удаления и дублирования элементов: ";
    }
    else {
        sort_list(top);
        cout << "Отсортированный список: ";
    }
    print_list(top);

    return 0;
