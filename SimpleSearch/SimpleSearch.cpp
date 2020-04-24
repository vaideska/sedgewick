// 23042020>>TKUZNETSOVA
//Примеры решения задачи поиска: входит ли некоторая последовательность объектов в заданное множество объектов.
//Предполагаем, что каждая операция занимает постоянное время.
//Тогда можно заключить, что время выполнение бинарного поиска пропорционально lgN, в отличии от последовательного.
//При удовоении N время бинарного поиска несколько увеличиться, н не удваивается, как для последовательного.

#include <iostream>
#include <cstdlib>          //для rand()
#include <stdlib.h>         //для qsort()

using namespace std;
static const int N = 10;

//Для проверки сортировки qsort
int comp(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

/*Последовательный поиск ("в лоб")
Проверяет N чисел при каждом неудачном поиске и в среднем порядка N/2 чисел при каждом успешном поиске.
В упоядочной таблице алгоритм проверет N чисел в худшем случае и N/2 чисел в среднем.
*/
int SequentialSearch(int a[], int v, int l, int r)
{
    for (int i = l; i <= r; i++)
        if (v == a[i]) return i;
    return -1;
}

/*Бинарный поиск (деление по полам)
Бинарный поиск проверяет не более lgN + 1 чисел.
*/
int BinarySearch(int a[], int v, int l, int r)
{
    while (r >= l) {
        int m = (l + r) / 2;                        //делим множество пополам
        if (v == a[m]) return m;                    //проверяем "средний элемент"
        if (v < a[m]) r = m - l; else l = m + 1;    //проверяем какую часть будем делить в следующий раз
    }
    return -1;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int i, a[N], v, res;
    char ch;
    for (i = 0; i < N; i++) a[i] = rand();
    qsort(a, N, sizeof(int), comp);
    for (i = 0; i < N; i++) cout << a[i] << " " << endl;
    cout << "Введите число, какое хотите найти:" << endl;
    cin >> v;

    cout << "Каким поиском хотите воспользоваться?" << endl;
    cout << "1 - последовательный поиск" << endl;
    cout << "2 - бинарный поиск" << endl;
    cin >> ch;

    switch (ch) {
    case '1': res = SequentialSearch(a, v, 0, N);        //Последовательный поиск
        break;
    case '2': res = BinarySearch(a, v, 0, N);            //Бинарный поиск
        break;
    default: cout << "Неверный ввод!";
        return 1;
    }
    cout << "Результат: " << res + 1 << endl;
    //system("pause");
    return 0;
}

