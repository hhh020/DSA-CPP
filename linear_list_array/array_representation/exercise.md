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