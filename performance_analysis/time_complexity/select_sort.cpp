// program 2-7/2-12
#include <algorithm>
#include <iostream>

using std::cerr;
using std::swap;

template<class T>
int indexOfMax(T a[], int n)
{
    if (n < 0)
        cerr << "n cannot less than 0\n";
    int indexOfMax = 0;
    for (int i = 1; i < n; i++)
        if (a[indexOfMax] < a[i])
            indexOfMax = i;
    return indexOfMax;
}

// 选择排序
template<class T>
void selectionSort(T a[], int n)
{
    for (int size = n; size > 1; size--)
    {
        int j = indexofMax(a, size);
        swap(a[j], a[size - 1]);
    }
}

// 及时终止的选择排序
template<class T>
void terminate_selectionSort(T a[], int n)
{
    bool sorted = false;
    for (int size = n; !sorted && (size > 1); size--)
    {
        int Maxindex = 0;
        sorted = true;
        for (int i = 1; i < size; i++)
        {
            if (a[Maxindex] <= a[i]) Maxindex = i;
            else sorted = false;    // 无序
        }
        swap(a[Maxindex],a[size - 1]);
    }
}