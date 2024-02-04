# exercise 5.2~5.36

## 5.2

| 操作  | 数组      | listSize |
| ----  | --------- | ------- |
| 初始  | (a,b,c,d,e) | 5 |
| insert(0,f) | (f,a,b,c,d,e) | 6 |
| insert(3,g) | (f,a,b,g,c,d,e) | 7 |
| insert(7,h) | (f,a,b,g,c,d,e,h) | 8 |
| erase(0) | (a,b,g,c,d,e,h) | 7 |
| erase(4) | (a,b,g,c,e,h) | 6 |

## 5.3

```c++
template<class T>
void changeLength2D(T **&a, int oldRowLength, int oldColLength,
                           int newRowLength,int newColLength)
{
    if (newColLength < 0 || newRowLength < 0)
        cerr << "new Col and Row length must be > 0\n";
    
    T** temp = new T*[newRowLength];        // 创建行指针数组
    for (int i = 0; i < newRowLength; i++)  // 创建列指针数组
        temp[i] = new T[newColLength];
    
    // 深拷贝
    int sum = 0;
    for (int i = 0; i < newRowLength; i++)
    {
        for (int j = 0; j < newColLength; j++)
        {
            temp[i][j] = a[sum/oldColLength][sum%oldColLength];
            sum++;
        }
    }

    for (int i = 0; i < oldRowLength; i++)  // 删除每行的列数组
        delete[] a[i];
    
    delete[] a;                             // 删除行指针数组
    a = temp;
}
```

## 5.4

```c++
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
```

## 5.5

```c++
// 使数组的长度等于 max{listSize,1}
template<class T>
void arrayList<T>::trimToSize()
{
    arrayLength = (listSize > 1) ? listSize : 1;
}
```

复杂度为O(1)

## 5.6

```c++
// 使线性表的大小等于指定的大小
// 若线性表开始的大小小于指定的大小，则不增加元素；否则删除多余的元素
template<class T>
void arrayList<T>::setSize(int length)
{
    if (length < 0)
        cerr << "error: linear list length must be positive\n";

    while (listSize > length)
        erase(listSize - 1);
}
```

复杂度为O((listSize - length) * 1) = O(n)

## 5.7

利用get()方法

```c++
// 重载 []
template<class T>
T& arrayList<T>::operator[](int i) const
{
    return get(i);
}
```

## 5.8

```c++
// 重载 ==
template<class T>
bool arrayList<T>::operator==(const arrayList<T>& a) const
{
    if (this->size() != a.size())
        return false;
    
    int i = 0;
    while (i < this->size() && this->get(i) == a.get(i))
        ++i;
    
    return (i == listSize);
}
```

## 5.9

```c++
// 重载 !=
template<class T>
bool arrayList<T>::operator!=(const arrayList<T>& a) const
{
    return !((*this) == a);
}
```
## 5.10

```c++
// 重载 <
template<class T>
bool arrayList<T>::operator<(const arrayList<T>& a) const
{
    int i;
    for (i = 0; i < this->size() && i < a.size() && a[i] == get(i); i++)
        ;
    
    // 只有对应位置元素相等但左边的长度小于右边的长度
    // 或左边某一位置的元素小于右边对应位置元素时, x < y 为真
    if (i == this->size())
        return true;
    else if (i == a.size())
        return false;
    else if (get(i) < a[i])
        return true;
    else
        return false;
}
```

## 5.11

```c++
// 把元素 theElement 插入线性表的右端
template<class T>
void arrayList<T>::push_back(const T& theElement)
{
    if (listSize == arrayLength)
    {
        changeLength1D(element, arrayLength, coefficient * arrayLength);
        arrayLength *= coefficient;
    }

    element[listSize++] = theElement;    
}

当数组已满时复杂度O(n), 未满时复杂度O(1)

## 5.12

```c++
// 把线性表右端的元素删除
template<class T>
void arrayList<T>::pop_back()
{
    if (listSize > 0)
        element[--listSize].~T();
}
```

复杂度O(1)

## 5.13

创建中间变量，进行深拷贝

```c++
// 交换线性表的元素
template<class T>
void arrayList<T>::swap(arrayList<T>& theList)
{
    // theList -> temp
    auto temp = new arrayList<T>(theList);
    
    // this -> theList
    theList.arrayLength = this->arrayLength;
    theList.coefficient = this->coefficient;
    theList.listSize = this->listSize;
    delete [] theList.element;
    theList.element = new T[theList.listSize];
    copy(this->element, this->element + this->listSize, theList.element);
    
    // temp -> this
    this->arrayLength = temp->arrayLength;
    this->coefficient = temp->coefficient;
    this->listSize = temp->listSize;
    delete [] this->element;
    this->element = new T[this->listSize];
    copy(temp->element, temp->element + temp->listSize, this->element);

    delete temp;
}
```

复杂度O(n)

## 5.14

```c++
// 将数组容量改变为当前容量和参数的较大者
template<class T>
void arrayList<T>::reserve(int theCapacity)
{
    if (theCapacity > arrayLength)
    {
        changeLength1D(element,arrayLength,theCapacity);
        arrayLength = theCapacity;
    }
}
```

## 5.15

```c++
// 将索引为theIndex的元素替换为元素theElement
// 返回原来索引为theIndex的元素
template<class T>
T arrayList<T>::set(int theIndex, const T& theElement)
{
    checkIndex(theIndex);
    T temp = element[theIndex];
    element[theIndex] = theElement;
    return temp;
}
```

## 5.16

```c++
// 使线性表为空
template<class T>
void arrayList<T>::clear()
{
    while (listSize > 0)
        element[--listSize].~T();
}
```

时间复杂度O(n)

## 5.17

```c++
// 删除指定索引范围[b,e)内的所有元素
template<class T>
void arrayList<T>::removeRange(int b, int e)
{
    checkIndex(b);
    checkIndex(e - 1);

    if (e <= b)
        cerr << "end should be > begin\n";
    
    copy(element + e, element + listSize, element + b);

    for (int i = listSize - 1; i > b - 1 + (listSize - e); i--)
        element[i].~T();
    
    listSize -= (e - b);
}
```

时间复杂度O(n)

## 5.18

```c++
// 返回指定元素最后出现的索引，如果指定元素不存在，则返回-1
template<class T>
int arrayList<T>::lastIndexOf(const T& theElement)
{
    int i;
    for (i = listSize - 1; i >= 0; i--)
        if (element[i] == theElement)
            break;
    
    return i;
}
```

时间复杂度O(n)

## 5.20

```c++
// 删除索引为 theIndex 的元素
// 如果元素不存在，则抛出异常
// 如果删除后listSize小于arrayLength / 4, 就创建一个新数组
// 长度为max{arrayLength / 2, initCapacity}
template<class T>
void arrayList<T>::erase_shrink(int theIndex)
{
    checkIndex(theIndex);

    // 有效索引， 移动其索引大于 theIndex 的元素
    copy(element + theIndex + 1, element + listSize, element + theIndex);
    
    element[--listSize].~T();   // 调用析构函数

    if (listSize < arrayLength / 4)
    {
        arrayLength = max(arrayLength / 2, initialCapacity);
        auto temp = new T[arrayLength];
        copy(element, element + listSize, temp);
        delete [] element;
        element = temp;
    }
}
```

## 5.22

1) 

```c++
// 原地颠倒线性表元素的顺序
template<class T>
void arrayList<T>::reverse()
{
    for (int i = 0; i < listSize - i - 1; i++)
        std::swap(element[i], element[listSize-i-1]);
}
```

2) std::swap函数的复杂度为O(1), for循环的复杂度为O(listSize / 2), 因此reverse函数的复杂度为O(n)

3) 见测试文件./test.cpp

4) 利用arrayList的set和get方法

```c++
// 另一个原地颠倒arrayList对象的方法
template<class T>
void reverse(arrayList<T>& a)
{
    T temp1, temp2;
    for (int i = 0; i < a.size() / 2; i++)
    {
        //  等价于
        //  temp = a.set(i, a.get(a.size() - i -1));
        //  a.set(a.size() - i -1, temp);
        temp1 = a.get(i);
        temp2 = a.get(a.size() - i - 1);
        a.set(i, temp2);
        a.set(a.size() - i - 1, temp1);
    }
}
```

5) get函数时间复杂度为O(1), set函数时间复杂度为O(1), 因此循环内部时间复杂度为O(1), for循环的复杂度为O(listSize / 2), 所以该函数的复杂度为O(n)

6) 第二个算法的运行时间大约是第一个算法的1.5~2.5倍左右

## 5.23

1) 

```c++
// 将线性表的元素向左移动i个位置
template<class T>
void arrayList<T>::leftshift(int i)
{
    // 确保 0 < i < listSize - 1
    checkIndex(i - 1);
    copy(element + i, element + listSize, element);
    listSize -= i;
}
```

2) 复杂度O(n)

3) 见test.cpp

## 5.24

1) 假设线性表的长度为L, 循环移动i个位置。第一步，将整个线性表逆转；第二步，将前 L-i 个元素逆转; 第三步，将后i个元素逆转

2) 