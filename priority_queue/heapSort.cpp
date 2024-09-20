// program 12-8 
#include "maxHeap.h"

// 使用堆排序的方法给数组a[1:n]按递增排序
template<typename T>
void heapSort(T a[], int n)
{
    // 在数组上建大根堆
    maxHeap<T> heap(1);
    heap.initialize(a, n);

    // 逐个从大根堆中提取元素
    for (int i = n - 1; i >= 1; i--)
    {
        T x = heap.top();
        heap.pop();
        a[i+1] = x;
    }

    // 从堆的析构函数中保存数组a
    heap.deactivateArray();
}