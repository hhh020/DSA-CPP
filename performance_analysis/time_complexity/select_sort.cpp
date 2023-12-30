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

template<class T>
void selectionSort(T a[], int n)
{
    for (int size = n; size > 1; size--)
    {
        int j = indexofMax(a, size);
        swap(a[j], a[size - 1]);
    }
}