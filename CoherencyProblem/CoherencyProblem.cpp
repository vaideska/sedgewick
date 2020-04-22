/* 20042019>>TKUZNETSOVA

Примеры решения задачи связности:
Имеется последовательность пар цел чисел p-q (p связанно с q). Предполагается, что отношение "связано с" транзитивное:
если p-r, а q-r, то p-r. Задача состоит в том, чобы исключить лишние пары из набора: программа выводит пару только в том случае,
если она не является связной. Если в соответсвии с ранее просмотренными парами следует, что пара связана, то программа игнорирует
ввод и переходит к вводу следующей паре.

Задача решается с помощью абстракных операций поиска и объединения. После считывания пары мы производим поиск
для каждого члена пары. Если они находятся в одном множестве, то переходим к новой паре.
Если нет, то объединяем множества и сохраняем пару.
*/

#include <iostream>
using namespace std;

static const int N = 10;

void QuickSearch(int* id);
void QuickUnion(int* id);
void WeightedQuickUnion(int* id, int* sz);
void WeightedQuickUnion_WithPathCompression(int* id, int* sz);
void WeightedQuickUnion_WithPathCompressionByHalving(int* id, int* sz);

int main()
{
    setlocale(LC_ALL, "Russian");
    int i, id[N], sz[N];
    char ch;

    cout << "1 - Быстрый поиск" << endl;
    cout << "2 - Быстрое объединение" << endl;
    cout << "3 - Взвешенная версия быстрого объединения" << endl;
    cout << "4 - Сжатие пути (полное) - упражнение 1.16" << endl;
    cout << "5 - Сжатие пути делением пополам" << endl;
    cin >> ch;

    for (i = 0; i < N; i++)
    {
        id[i] = i;  //Члены массива id равны, когда объекты p и q - связаны.
        sz[i] = 1;  //Дополнительный массив для хранения кол-ва узов в соответсвующих деревьях для версии со взвешениванием
    }

    switch(ch) {
        case '1': QuickSearch(id);                                                      //Быстрый поиск
            break;
        case '2': QuickUnion(id);                                                       //Быстрое объединение
            break;
        case '3': WeightedQuickUnion(id, sz);                                           //Взвешенная версия быстрого объединения
            break;
        case '4': WeightedQuickUnion_WithPathCompression(id, sz);                       //Сжатие пути (полное) - упражнение 1.16
            break;
        case '5': WeightedQuickUnion_WithPathCompressionByHalving(id, sz);              //Сжатие пути делением пополам
            break;
        default: cout << "Неверный ввод!";
            return 1;
    }
    return 0;
}


/* Решение задачи методом быстрого поиска.
Алгоритм выполняет не менее MN инструкций для решения задачи связности при наличии N объектов,
для которых требуется выполнение M операций объединений.
*/
void QuickSearch(int* id)
{
    int i, p, q;
    cout << "Вводите пару чисел:" << endl;
    while (cin >> p >> q)
    {
        int t = id[p];
        if (t == id[q]) continue;                       //пара находится в одном множестве
        for (i = 0; i < N; i++)                         //поиск множества, где находится объект p
            if (id[i] == t) id[i] = id[q];              //объединение множества p с множеством q

        cout << " " << p << " " << q << endl;           //выводим пару на экран, т.к. она не была еще связана
        for (i = 0; i < N; i++) cout << i << " ";       //выводим объекты на экран
        cout << endl;
        for (i = 0; i < N; i++) cout << id[i] << " ";   //выводим ссылки на множества (деревья) на экран
        cout << endl;
    }
    return;
}


/* Решение задачи методом быстрого объединения.
Для M пар из N объектов, когда M > N, решение данным алгоритмом может потребовать выплнения более чем MN/2 инструкций.
*/
void QuickUnion(int* id)
{
    int i, j, p, q;
    cout << "Вводите пару чисел:" << endl;
    while (cin >> p >> q)
    {
        for (i = p; i != id[i]; i = id[i]);     //если массив представить в виде дерева - тут идет поиск корня
        for (j = q; j != id[j]; j = id[j]);     //для объектов p и q. id[x] - ссылка на следующий элемент дерева.
        if (i == j) continue;                   //"корень" один, значит объекты в одном множестве, иначе:
        id[i] = j;                              //происходит объединение

        cout << " " << p << " " << q << endl;
        for (i = 0; i < N; i++) cout << i << " ";
        cout << endl;
        for (i = 0; i < N; i++) cout << id[i] << " ";
        cout << endl;
    }
    return;
}


/* Решение задачи взвешенной версией быстрого объединения.
Для определения того, связаны ли два из N объектов, алгоритм переходит максимум по logN указателям.
*/
void WeightedQuickUnion(int* id, int* sz)
{
    int i, j, p, q;
    cout << "Вводите пару чисел:" << endl;
    while (cin >> p >> q)
    {
        for (i = p; i != id[i]; i = id[i]);         //аналогично версии простого быстрого объединения
        for (j = q; j != id[j]; j = id[j]);
        if (i == j) continue;
        if (sz[i] < sz[j]) {                        //проверяется в каком из узлов меньше вершин
            id[i] = j; sz[j] += sz[i];                //с таким и происходит объединение, а кол-во узлов складывается
        }
        else {                                    //т.о. предотвращая разрастания длинных путей в деревьях
            id[j] = i; sz[i] += sz[j];                //и поиск вершины происходит быстрей
        }

        cout << " " << p << " " << q << endl;
        for (i = 0; i < N; i++) cout << i << " ";
        cout << endl;
        for (i = 0; i < N; i++) cout << id[i] << " ";
        cout << endl;
    }
    return;
}


/* Решение задачи взвешенной версией быстрого объединения с полным сжатием пути.
Делаем все проверяемые узлы, указывающими на корень.
*/
void WeightedQuickUnion_WithPathCompression(int* id, int* sz)
{
    int i, j, p, q;
    cout << "Вводите пару чисел:" << endl;
    while (cin >> p >> q)
    {
        for (i = p; i != id[i]; i = id[i]);         //аналогично версии простого быстрого объединения
        for (j = q; j != id[j]; j = id[j]);
        if (i == j) continue;
        if (sz[i] < sz[j]) {
            id[i] = j; sz[j] += sz[i];
            for (i = p; i != id[i]; i = id[i])     //еще раз просматрваем объекты дерева
                id[i] = j;                         //заносим в них указатель на корень нового дерева
        }                                          //т.о. делаем дерево плоским
        else {
            id[j] = i; sz[i] += sz[j];
            for (j = q; j != id[j]; j = id[j])
                id[j] = i;
        }

        cout << " " << p << " " << q << endl;
        for (i = 0; i < N; i++) cout << i << " ";
        cout << endl;
        for (i = 0; i < N; i++) cout << id[i] << " ";
        cout << endl;
    }
    return;
}


/* Решение задачи взвешенной версией быстрого объединения со сжатием пути делением пополам.
Конечный результат - превращение деревьев в почти совершенно плоские.
*/
void WeightedQuickUnion_WithPathCompressionByHalving(int* id, int* sz)
{
    int i, j, p, q;
    cout << "Вводите пару чисел:" << endl;
    while (cin >> p >> q)
    {
        for (i = p; i != id[i]; i = id[i])
            id[i] = id[id[i]];                  //сдвигает каждую ссылку на следующий узел в пути вверх по дереву
        for (j = q; j != id[j]; j = id[j])      //т.о. находим корень дерева в два раза быстрей
            id[j] = id[id[j]];
        if (i == j) continue;
        if (sz[i] < sz[j]) {
            id[i] = j; sz[j] += sz[i];
        }
        else {
            id[j] = i; sz[i] += sz[j];
        }

        cout << " " << p << " " << q << endl;
        for (i = 0; i < N; i++) cout << i << " ";
        cout << endl;
        for (i = 0; i < N; i++) cout << id[i] << " ";
        cout << endl;
    }
    return;
}