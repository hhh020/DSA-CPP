// minHeap

// program 12-2 ~ 12-4
#ifndef __MIN_HEAP_H__
#define __MIN_HEAP_H__

#include "../myexcption.h"
#include "queueEmpty.h"
#include <algorithm>

using std::copy;

// 改变一维数组长度
template<class T>
void changeLength1D(T*& a, int oldLength, int newLength)
{
    if (newLength < 0)
        throw illegalParameterValue("new length must be >= 0");
    
    T* temp = new T[newLength];                 // 新数组
    int number = min(oldLength,newLength);      // 需要复制的元素个数
    copy(a, a + number, temp);
    delete [] a;
    a = temp;
}

template<typename T>
class minHeap
{
public:
    minHeap(int length = 0);
    ~minHeap() {delete [] heap;}
    void initialize(T *theHeap, int theSize);
    void push(const T& theElement);
    void pop();
    T top() const {if (empty()) throw queueEmpty(); return heap[1];};
    bool empty() const {return heapSize == 0;}
    int size() const {return heapSize;}
    void deactivateArray() {heap = NULL;}

private:
    T *heap;
    int arrayLength;    // 数组heap的容量
    int heapSize;       // 堆的元素个数
};

// 把元素theElement加入堆
template<typename T>
void minHeap<T>::push(const T& theElement)
{
    // 必要时增加数组长度
    if (heapSize == arrayLength - 1)
    {
        changeLength1D(heap, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    // 为元素theElement找到插入位置
    // currentNode 从新叶子向上移动
    int currentNode = ++heapSize;
    while (currentNode != 1 && heap[currentNode / 2] > theElement)
    {
        // 不能把元素theElement插入在heap[currentNode]
        heap[currentNode] = heap[currentNode / 2];      // 把元素向下移动
        currentNode /= 2;                               // currentNode移向parent
    }
    
    heap[currentNode] = theElement;
}

// 删除最大元素
template<typename T>
void minHeap<T>::pop()
{
    if (empty())                // 堆为空
        throw queueEmpty();

    // 删除最大元素
    heap[1].~T();

    // 删除最后一个元素，然后重新建堆
    T lastElement = heap[heapSize--];

    // 从根开始，为最后一个元素寻找位置
    int currentNode = 1, child = 2;
    while (child <= heapSize)
    {
        // heap[child]应该是currentNode的更小的孩子
        if (child < heapSize && heap[child] > heap[child + 1])
            child++;
        
        // 可以把lastElement插入在heap[currentNode]吗
        if (lastElement <= heap[child])     // 可以
            break;
        
        // 不可以
        heap[currentNode] = heap[child];    // 把child向上移动
        currentNode = child;                // 向下一层寻找位置
        child *= 2;
    }
    heap[currentNode] = lastElement;
}

// 在数组theHeap[1:theSize]中建大根堆
template<typename T>
void minHeap<T>::initialize(T *theHeap, int theSize)
{
    delete [] heap;
    heap = theHeap;
    heapSize = theSize;

    // 堆化
    for (int root = heapSize / 2; root >= 1; root--)
    {
        T rootElement = heap[root];
        
        int child = 2 * root;   // child的双亲是元素rootElement的位置
        while (child <= heapSize)
        {
            // heap[child]应该是root的更小的孩子
            if (child < heapSize && heap[child] > heap[child + 1])
                child++;
            
            // rootElement是优先级最大的元素
            if (rootElement <= heap[child])
                break;
            
            // rootElement不是优先级最大的元素
            heap[child / 2] = heap[child];      // 把child上移
            child *= 2;                         // 移到下一层
        }
        heap[child / 2] = rootElement;
    }
}

#endif