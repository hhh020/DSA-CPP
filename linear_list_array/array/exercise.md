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

## 5.24

1) 假设线性表的长度为L, 循环移动i个位置。第一步，将整个线性表逆转；第二步，将前 L-i 个元素逆转; 第三步，将后i个元素逆转

2) 

```c++
// 将线性表的元素向左循环移动i个位置
template<class T>
void arrayList<T>::circularShift(int i)
{
    // 将整个线性表逆转
    for (int k = 0; k < listSize - k - 1; k++)
        std::swap(element[k], element[listSize-k-1]);
    
    // 将前 L-i 个元素逆转
    for (int k = 0; k < listSize - i - k - 1; k++)
        std::swap(element[k], element[listSize-i-k-1]);

    // 将后i个元素逆转
    for (int k = 0; listSize - i + k < listSize - k - 1; k++)
        std::swap(element[listSize-i+k], element[listSize-k-1]);
}
```

## 5.25

1) 使用快慢指针

```c++
// 将元素隔一个删除一个
template<class T>
void arrayList<T>::half()
{
    int i = 1;
    for (int j = 2; j < listSize; i++, j+=2)
        element[i] = element[j];
    
    listSize = i;
}
```

2) 赋值操作为O(1), 循环遍历步数为 listSize / 2 , 因此复杂度为O(listSize)。

## 5.26

```c++
// 外部函数, 将线性表元素隔一个删除一个
template<class T>
void half(arrayList<T>& a)
{
    // 确定起始删除位置
    int size = a.size();
    int p = size - 1;
    if (size % 2 == 1) p--;

    while (p > 0)
    {
        a.erase(p);
        p -= 2;
    }
}
```

复杂度: 循环 listSize / 2 步, erase函数中的std::copy函数平均复杂度为O(lisSize / 4),
因此half函数复杂度为O(n ^ 2)

## 5.27

随机访问迭代器（Random Access Iterator）是一种强大的迭代器类型，它提供了对容器中元素的高效、灵活且不受限制的访问能力。这种迭代器具备以下关键特征：

1. **快速定位**：
   随机访问迭代器可以在常数时间内（O(1)）跳转到容器中任意位置的元素，无论这个位置相对于当前迭代器是前移还是后移。这意味着可以通过简单的算术运算（如 `it += n` 或 `it -= n`）来一次性移动迭代器到指定偏移量处，而不必连续多次执行前置或后置递增/递减操作。

2. **迭代器算术**：
   支持所有算术和关系运算符，包括：
   - 增量和减量：`++it`, `--it`, `it++`, `it--`
   - 相对位移：`it += n`, `it -= n`
   - 相对访问：`it[n]`（等价于 `*(it + n)`）
   - 关系比较：`it1 < it2`, `it1 > it2`, `it1 <= it2`, `it1 >= it2`
   - 差距计算：`it1 - it2` 返回 `it1` 与 `it2` 之间的距离（类型为 `difference_type`）

3. **双向移动**：
   除了快速随机访问外，随机访问迭代器还继承了双向迭代器的能力，允许向前和向后移动，即支持 `--it` 和 `++it` 操作。

4. **读写访问**：
   随机访问迭代器通常提供对元素的读写访问权限，可以通过解引用 `*it` 获取或修改元素值，还可以通过 `it->member` 访问元素的成员。

5. **性能要求**：
   随机访问迭代器要求底层数据结构支持高效的随机访问，这通常意味着其对应的容器（如 `std::vector`, `std::array`, `std::deque`）内部存储是连续的或具有快速索引机制。相比之下，像 `std::list` 这种基于链表实现的容器，由于其内部结构特性，无法提供随机访问迭代器。

6. **STL算法兼容性**：
   许多标准模板库（STL）算法要求其操作的迭代器至少是随机访问迭代器。这些算法依赖于快速跳跃和随机访问元素的能力，如 `std::sort`, `std::nth_element`, `std::binary_search`, `std::shuffle` 等。只有当迭代器满足随机访问要求时，这些算法才能保证预期的性能和正确性。

exercise_iterator.h
```c++
// exercise 5.27
#ifndef __Iterator__
#define __Iterator__

#include <iterator>

using std::random_access_iterator_tag;

template<typename T>
class Iterator
{
public:
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;

    // 构造函数
    Iterator(T* thePosition = 0) : position(thePosition) {}
    Iterator(T* thePosition, int offset) : position(thePosition + offset) {}

    // 赋值
    void operator=(T* thePostion) {position = thePostion;}
    
    // 解引用操作符
    T& operator*() const {return *position;}
    T* operator->() const {return &*position;}

    // 迭代器的值增加
    // 前加
    Iterator& operator++() 
                {++position; return *this;}
    // 后加
    Iterator operator++(int)
    {
        Iterator old = *this;
        ++position;
        return old;
    }

    // 迭代器的值减少
    // 前减
    Iterator& operator--()
                {--position; return *this;}
    // 后减
    Iterator operator--(int)
    {
        Iterator old = *this;
        --position;
        return old;
    }

    // 测试是否相等
    bool operator!=(const Iterator right) const
            {return position != right.position;}
    bool operator==(const Iterator right) const
            {return position == right.position;}
    
    // 关系运算符
    bool operator<(const Iterator& right) const
            {return position < right.position;}
    
    bool operator<=(const Iterator& right) const
            {return position <= right.position;}

    bool operator>(const Iterator& right) const
            {return position > right.position;}    

    bool operator>=(const Iterator& right) const
            {return position >= right.position;}     

    // 下标访问
    T& operator[](int p) const
            {return *(position + p);}
    
    // 前进指定数量的元素
    void operator+=(difference_type n)
            {position += n;}
    
    // 后退指定数量的元素
    void operator-=(difference_type n)
            {position -= n;}
    
    // 与difference_type相加
    Iterator& operator+(difference_type n)
            {position += n; return *this;}

    // 与difference_type相减
    Iterator& operator-(difference_type n)
            {position -= n; return *this;}
    
    // 两个迭代器之间的距离
    int operator-(const Iterator iter)
            {return iter.position - position;}
protected:
    T* position;
};

#endif
```

begin()和end()
```c++
    Iterator<T> begin() {return Iterator<T>(element);}
    Iterator<T> end() {return Iterator<T>(element, listSize);}

    // 迭代器成员
    Iterator<T> iter;
```

## 5.28

1) 

```c++

// 生成一个新的线性表，交替包含a和b中的元素
template<class T>
arrayList<T> meld(const arrayList<T>& a, const arrayList<T>& b)
{
    int minsize = min(a.size(), b.size());
    auto c = new arrayList<T>(a.size() + b.size());

    for (int i = 0; i < 2 * minsize; i++)
    {
        if (i % 2 == 0) c->push_back(a[i/2]);
        else c->push_back(b[i/2]);
    }
    while (minsize < a.size())  c->push_back(a[minsize++]);
    while (minsize < b.size())  c->push_back(b[minsize++]);

    return *c;
}
```

2) 方法meld中, min函数O(1), 构造函数O(a + b), for循环O(2 * minsize), while循环O(a + b - 2 * minszie). 
   因此复杂度为**O(a + b)**, 具有线性复杂度, 实际上考虑到遍历过程从c[0]到c[a+b-1], 也可以轻松得出结果

3) test28执行结果:  **c: 0 0 1 1 2 2 3 4**

## 5.29

1) 

```c++

// merge, 使用有序线性表a、b生成一个新的有序线性表
template<class T>
void arrayList<T>::merge(const arrayList<T>& a, const arrayList<T>& b)
{
    this->clear();
    int it1 = 0, it2 = 0;
    while (it1 < a.size() && it2 < b.size())
    {
        if (a[it1] <= b[it2])
        {
            this->push_back(a[it1]);
            it1++;
        }
        else
        {
            this->push_back(b[it2]);
            it2++;
        }
    }
    while (it1 < a.size())  this->push_back(a[it1++]);
    while (it2 < b.size())  this->push_back(b[it2++]);
}

```

2) merge方法遍历了线性表a和b, 复杂度为**O(a + b)**

3) test29执行结果:  **c: 0 1 2 3 4 5 6**

## 5.30

1) 

```c++

// spilt, 生成两个线性表a,b. a包含索引为偶数的元素, b包含索引为奇数的元素
template<class T>
void arrayList<T>::spilt(arrayList<T>& a, arrayList<T>& b)
{
    a.clear();
    b.clear();
    for (int i = 0; i < this->size(); i++)
    {
        if (i & 0x1)    b.push_back(get(i));
        else            a.push_back(get(i));
    }
}

```

2) 遍历了this的整个线性表, 复杂度**O(n)**

3) test30测试结果:

c: 0 1 2 3 4 5 6 
a: 0 2 4 6 
b: 1 3 5

## 5.31~5.36

写不动了，略...