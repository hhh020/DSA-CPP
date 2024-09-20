// maxheap for exercises
#include "../../myexcption.h"
#include "../queueEmpty.h"
#include <algorithm>
#include <iostream>

using std::copy;
using std::cout;
using std::min;

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
class maxHeap
{
public:
    maxHeap(int length = 0);
    maxHeap(const maxHeap& rhs);
    ~maxHeap() {delete [] heap;}
    void initialize(T *theHeap, int theSize);
    void push(const T& theElement);
    void pop();
    T top() const {if (empty()) throw queueEmpty(); return heap[1];};
    bool empty() const {return heapSize == 0;}
    int size() const {return heapSize;}
    void remove(int theIndex);
    void printInArray() const;
    void printInTree() const;

private:
    T *heap;
    int arrayLength;    // 数组heap的容量
    int heapSize;       // 堆的元素个数
};

// 把元素theElement加入堆
template<typename T>
void maxHeap<T>::push(const T& theElement)
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
    while (currentNode != 1 && heap[currentNode / 2] < theElement)
    {
        // 不能把元素theElement插入在heap[currentNode]
        heap[currentNode] = heap[currentNode / 2];      // 把元素向下移动
        currentNode /= 2;                               // currentNode移向parent
    }
    
    heap[currentNode] = theElement;
}

// 删除最大元素
template<typename T>
void maxHeap<T>::pop()
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
        // heap[child]应该是currentNode的更大的孩子
        if (child < heapSize && heap[child] < heap[child + 1])
            child++;
        
        // 可以把lastElement插入在heap[currentNode]吗
        if (lastElement >= heap[child])     // 可以
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
void maxHeap<T>::initialize(T *theHeap, int theSize)
{
    delete [] heap;
    heap = theHeap;
    heapSize = theSize;
    arrayLength = theSize + 1;

    // 堆化
    for (int root = heapSize / 2; root >= 1; root--)
    {
        T rootElement = heap[root];
        
        int child = 2 * root;   // child的双亲是元素rootElement的位置
        while (child <= heapSize)
        {
            // heap[child]应该是root的更大的孩子
            if (child < heapSize && heap[child] < heap[child + 1])
                child++;
            
            // rootElement是优先级最大的元素
            if (rootElement >= heap[child])
                break;
            
            // rootElement不是优先级最大的元素
            heap[child / 2] = heap[child];      // 把child上移
            child *= 2;                         // 移到下一层
        }
        heap[child / 2] = rootElement;
    }
}

// 构造函数
template<typename T>
maxHeap<T>::maxHeap(int length)
{
    if (length < 1)
        throw illegalParameterValue("length must be >= 1");
    
    arrayLength = length + 1;
    heap = new T[arrayLength];
    heapSize = 0;
}

// 复制构造函数
template<typename T>
maxHeap<T>::maxHeap(const maxHeap& rhs)
{
    arrayLength = rhs.arrayLength;
    heapSize = rhs.heapSize;
    heap = new T[arrayLength];
    copy(rhs.heap, rhs.heap + heapSize + 1, heap);
}

// 以数组的形式显示堆
template<typename T>
void maxHeap<T>::printInArray() const
{
    for (int i = 1; i <= heapSize; i++)
        cout << heap[i] << " ";
    cout << '\n';
}

// 以树的形式显示堆
template<typename T>
void maxHeap<T>::printInTree() const
{
    int i = 1;
    int j = 2;
    while (i <= heapSize)
    {
        cout << heap[i] << " ";
        i++;
        if (i == j)
        {
            cout << '\n';
            j *= 2;
        }
    }
    cout << '\n';
}
