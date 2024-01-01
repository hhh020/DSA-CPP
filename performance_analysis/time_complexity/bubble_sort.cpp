// program 2-8/2-9/2-13
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

// 输出是否交换了元素
template<class T>
bool isswapped_bubble(T a[], int n)
{
    bool swapped = false;
    for (int i = 0; i < n; i++)
    {
        if (a[i] > a[i+1])
        {
            swap(a[i],a[i+1]);
            swapped = true;
        }
    }
    return swapped;
}

// 及时终止冒泡排序
template<class T>
void terminate_bubbleSort(T a[], int n)
{
    for (int i = n; (i > 1) && !isswapped_bubble(a, i); i--)
        ;
}



