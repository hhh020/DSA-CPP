#include <algorithm>

using std::swap;

// 把 a[0:n-1]中的最大元素移到右边
template<class T>
void bubble(T a[], int n)
{
    for (int i = 0; i < n - 1; i++)
        if (a[i] > a[i+1])
            swap(a[i], a[i+1]);
}

// 对数组元素进行冒泡排序
template<class T>
void bubbleSort(T a[], int n)
{
    for (int i = n; i > 1; i--)
        bubble(a, i);
}