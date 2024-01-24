// exercise
#include "exercise_array_list.h"

#include <algorithm>
#include <iterator>
#include <iostream>

using std::find;
using std::min;
using std::copy;
using std::copy_backward;
using std::ostream_iterator;
using std::cout;
using std::cerr;

// 构造函数
template<class T>
arrayList<T>::arrayList(int initCapacity, int initCoefficient)
{
    if (initCapacity < 1 || initCoefficient < 1)
        cerr << "Initial capacity and initial coefficient must be > 0\n";
    
    arrayLength = initCapacity;
    element = new T[arrayLength];
    listSize = 0;
    coefficient = initCoefficient;
}

// 复制构造函数
template<class T>
arrayList<T>::arrayList(const arrayList<T>& theList)
{
    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    element = new T[arrayLength];
    copy(theList.element, theList.element + listSize, element);
}

// 确定索引在 0 ~ listSize - 1 之间
template<class T>
void arrayList<T>::checkIndex(int theIndex) const
{
    if (theIndex < 0 || theIndex >= listSize)
        cerr << "index = " << theIndex << " size = " << listSize << '\n';
    
}

// 返回索引为 theIndex 的元素
// 若此元素不存在，则抛出异常
template<class T>
T& arrayList<T>::get(int theIndex) const
{
    checkIndex(theIndex);
    return element[theIndex];
}

// 返回元素 theElement 第一次出现时的索引
// 若该元素不存在，则返回-1
template<class T>
int arrayList<T>::indexOf(const T& theElement) const
{
    int theIndex = (int) (find(element, element + listSize, theElement) - element);

    if (theIndex == listSize)
        return -1;
    else
        return theIndex;
}

// 改变一维数组长度
template<class T>
void changeLength1D(T*& a, int oldLength, int newLength)
{
    if (newLength < 0)
        cerr << "new length must be >= 0\n";
    
    T* temp = new T[newLength];                 // 新数组
    int number = min(oldLength,newLength);      // 需要复制的元素个数
    copy(a, a + number, temp);
    delete [] a;
    a = temp;
}

// 删除索引为 theIndex 的元素
// 如果元素不存在，则抛出异常
template<class T>
void arrayList<T>::erase(int theIndex)
{
    checkIndex(theIndex);

    // 有效索引， 移动其索引大于 theIndex 的元素
    copy(element + theIndex + 1, element + listSize, element + theIndex);
    
    element[--listSize].~T();   // 调用析构函数
}

// 在索引 theIndex 处插入元素 theElement
template<class T>
void arrayList<T>::insert(int theIndex, const T& theElement)
{
    // 无效索引
    if (theIndex < 0 || theIndex > listSize)
    {
        cerr << "index = " << theIndex << " size = " << listSize << '\n';
    }

    // 有效索引，确认数组是否已满
    if (listSize == arrayLength)
    {
        if (coefficient == 0)
        {
            changeLength1D(element, arrayLength, 2 * arrayLength);
            arrayLength *= 2;
        }
        else 
        {
            changeLength1D(element, arrayLength, coefficient * arrayLength);
            arrayLength *= coefficient;
        }
    }

    // 把元素向右移动一个位置
    copy_backward(element + theIndex, element + listSize, element + listSize + 1);
    element[theIndex] = theElement;

    listSize++;
}

// 使数组的长度等于 max{listSize,1}
template<class T>
void arrayList<T>::trimToSize()
{
    arrayLength = (listSize > 1) ? listSize : 1;
}

// 使线性表的大小等于指定的大小
// 若线性表开始的大小小于指定的大小，则不增加元素；否则删除多余的元素
template<class T>
void arrayList<T>::setSize(int length)
{
    if (length < 0)
        cerr << "error: linear list length must be positive\n";

    while (listSize > length)
        erase(0);
}

// 把线性表插入输出流
template<class T>
void arrayList<T>::output(ostream &out) const
{
    copy(element, element + listSize, ostream_iterator<T>(cout, " "));
}

// 重载 <<
template<class T>
ostream& operator<<(ostream &out, const arrayList<T>& x)
{
    x.output(out);
    return out;
}

// 重载 []
template<class T>
T& arrayList<T>::operator[](int i)
{
    
}

void test4()
{
    auto a = new arrayList<int>(5);
    for (int i = 0; i < 6; i++)
        a->insert(0,i);
    cout << "系数为默认值(2)时, a扩展的容量为" << a->capacity() << '\n';

    auto b = new arrayList<int>(5,3);
    for (int i = 0; i < 6; i++)
        b->insert(0,i);
    cout << "系数为3时, a扩展的容量为" << b->capacity() << '\n';
    delete a;
}

void test5()
{
    auto a = new arrayList<int>(5);
    cout << "数组初始长度为" << a->capacity() << '\n';
    for (int i = 0; i < 3; i++)
        a->insert(0,i);
    a->trimToSize();
    cout << "数组在trimToSize方法作用后长度为" << a->capacity() << '\n';
    delete a;
}

void test6()
{
    auto a = new arrayList<int>(5);
    for (int i = 0; i < 3; i++)
        a->insert(0,i);
    cout << "线性表初始大小为" << a->size() << '\n';
    cout << "元素为: " << *a << '\n';
    a->setSize(2);
    cout << "数组在setSize方法作用后长度为" << a->size() << '\n';
    cout << "元素为: " << *a << '\n';
    delete a;
}

int main()
{
    test6();
    return 0;
}