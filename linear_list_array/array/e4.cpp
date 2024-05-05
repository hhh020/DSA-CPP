// exercise 5.4 ~ 5.18, 5.20, 5.22 ~ 5.26, 5.28
#include "exercise_array_list.h"
#include "../../myexcption.h"

#include <algorithm>
#include <iterator>
#include <iostream>
#include <chrono>

using std::find;
using std::min;
using std::max;
using std::copy;
using std::copy_backward;
using std::ostream_iterator;
using std::cout;
using std::cerr;
using std::sort;

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
    initialCapacity = initCapacity;
}

// 复制构造函数
template<class T>
arrayList<T>::arrayList(const arrayList<T>& theList)
{
    arrayLength = theList.arrayLength;
    initialCapacity = theList.initialCapacity;
    listSize = theList.listSize;
    element = new T[arrayLength];
    copy(theList.element, theList.element + listSize, element);
}

// 确定索引在 0 ~ listSize - 1 之间
template<class T>
void arrayList<T>::checkIndex(int theIndex) const
{
    if (theIndex < 0 || theIndex >= listSize)
        throw illegalIndex("error: index must between 0 and listSize - 1");    
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
        changeLength1D(element, arrayLength, coefficient * arrayLength);
        arrayLength *= coefficient;
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
// 若线性表开始的大小等于指定的大小，则不增加元素；否则删除多余的元素
template<class T>
void arrayList<T>::setSize(int length)
{
    if (length < 0)
        cerr << "error: linear list length must be positive\n";

    while (listSize > length)
        erase(listSize - 1);
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
T& arrayList<T>::operator[](int i) const
{
    return get(i);
}

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

// 重载 !=
template<class T>
bool arrayList<T>::operator!=(const arrayList<T>& a) const
{
    return !((*this) == a);
}

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

// 把线性表右端的元素删除
template<class T>
void arrayList<T>::pop_back()
{
    if (listSize > 0)
        element[--listSize].~T();
}

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

// 使线性表为空
template<class T>
void arrayList<T>::clear()
{
    while (listSize > 0)
        element[--listSize].~T();
}

// 删除指定索引范围[b,e)内的所有元素
template<class T>
void arrayList<T>::removeRange(int b, int e)
{
    checkIndex(b);
    checkIndex(e - 1);

    if (e <= b)
        cerr << "end should be > p\n";
    
    copy(element + e, element + listSize, element + b);

    for (int i = listSize - 1; i > b - 1 + (listSize - e); i--)
        element[i].~T();
    
    listSize -= (e - b);
}

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

// 原地颠倒线性表元素的顺序
template<class T>
void arrayList<T>::reverse()
{
    for (int i = 0; i < listSize - i - 1; i++)
        std::swap(element[i], element[listSize-i-1]);
}

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

// 将线性表的元素向左移动i个位置
template<class T>
void arrayList<T>::leftshift(int i)
{
    // 确保 0 < i < listSize - 1
    checkIndex(i - 1);
    copy(element + i, element + listSize, element);
    listSize -= i;
}

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

// 将线性表元素隔一个删除一个
template<class T>
void arrayList<T>::half()
{
    int i = 1;
    for (int j = 2; j < listSize; i++, j+=2)
        element[i] = element[j];
    
    listSize = i;
}

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
    delete b;
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

void test7()
{
    auto a = new arrayList<int>(5);
    for (int i = 0; i < 5; i++)
        a->insert(0,i);
    for (int i = 0; i < 5; i++)
        cout << (*a)[i] << ' ';
    cout << '\n';

    try {
        cout << (*a)[5] << '\n';
    }
    catch(const illegalIndex& e)
    {
        std::cerr << e.what() << '\n';
    }
    delete a;
}

void test8()
{
    auto a = new arrayList<int>(5);
    auto b = new arrayList<int>(5);
    auto c = new arrayList<int>(5);
    for (int i = 0; i < 5; i++)
    {
        a->insert(0,i);
        b->insert(0,i);
        c->insert(0, 4 - i);
    }
        
    cout << "a == b ? " << ((*a) == (*b)) << '\n';
    cout << "a == c ? " << ((*a) == (*c)) << '\n';
    cout << "a != b ? " << ((*a) != (*b)) << '\n';
    cout << "a != b ? " << ((*a) != (*c)) << '\n';
    delete a;
    delete b;
    delete c;
}

void test10()
{
    auto a = new arrayList<char>(5);
    auto b = new arrayList<char>(6);
    auto c = new arrayList<char>(5);
    for (int i = 0; i < 5; i++)
    {
        a->insert(i,'a' + i);
        b->insert(i,'a' + i);
        c->insert(i,'z' - i);
    }
    b->insert(5,'f');

    cout << "a = " << (*a) << '\n';
    cout << "b = " << (*b) << '\n';
    cout << "c = " << (*c) << '\n';
    cout << "a < b ? " << ((*a) < (*b)) << '\n';
    cout << "a < c ? " << ((*a) < (*c)) << '\n';

    b->erase(b->size() - 1);
    b->erase(b->size() - 1);
    cout << "b删除末尾两个元素后 a < b ? " << ((*a) < (*b)) << '\n';
    b->insert(1,'a');
    cout << "b在位置1插入字符'a'后 a < b ? " << ((*a) < (*b)) << '\n';

    delete a;
    delete b;
    delete c;
}

void test11()
{
    auto a = new arrayList<int>(5);
    for (int i = 0; i < 5; i++)
        a->insert(i,i);
    cout << "线性表初始大小为" << a->size() << '\n';
    cout << "元素为: " << *a << '\n';
    a->push_back(5);
    cout << "线性表在push_back方法作用后长度为" << a->size() << '\n';
    cout << "元素为: " << *a << '\n';
    delete a;
}

void test12()
{
    auto a = new arrayList<int>(5);
    for (int i = 0; i < 5; i++)
        a->insert(i,i);
    cout << "线性表初始大小为" << a->size() << '\n';
    cout << "元素为: " << *a << '\n';
    a->pop_back();
    cout << "线性表在pop_back方法作用后长度为" << a->size() << '\n';
    cout << "元素为: " << *a << '\n';
    delete a;
}

void test13()
{
    auto a = new arrayList<int>(5);
    auto b = new arrayList<int>(8);

    for (int i = 0; i < 5; i++)
    {
        a->insert(i,i);
        b->insert(i,i);
    }
    for (int i = 5; i < 8; i++)
        b->insert(i,i);

    cout << "a = " << (*a) << '\n';
    cout << "b = " << (*b) << '\n';
    cout << "交换后:\n";
    a->swap(*b);
    cout << "a = " << (*a) << '\n';
    cout << "b = " << (*b) << '\n';
    delete a;
    delete b;
}

void test14()
{
    auto a = new arrayList<int>(5);
    cout << "线性表初始容量为" << a->capacity() << '\n';
    a->reserve(8);
    cout << "数组在reserve方法作用后容量为" << a->capacity() << '\n';
    delete a;
}

void test15()
{
    auto a = new arrayList<int>(5);
    for (int i = 0; i < 5; i++)
        a->insert(i,i);
    cout << "a: " << (*a) << '\n';
    a->set(4,1);
    cout << "a在set方法作用后为 " << (*a) << '\n';
    delete a;
}

void test16()
{
    auto a = new arrayList<int>(5);
    for (int i = 0; i < 5; i++)
        a->insert(i,i);
    cout << "a: " << (*a) << '\n';
    a->clear();
    cout << "a在clear方法作用后为 " << (*a) << '\n';
    delete a;
}

void test17()
{
    auto a = new arrayList<int>(5);
    for (int i = 0; i < 5; i++)
        a->insert(i,i);
    cout << "a: " << (*a) << '\n';
    a->removeRange(2,4);
    cout << "a在removeRange(2,3)作用后为 " << (*a) << '\n';
    delete a;
}

void test18()
{
    auto a = new arrayList<int>(5);
    for (int i = 0; i < 5; i++)
        a->insert(i,i);
    cout << "a: " << (*a) << '\n';
    cout << "元素3最后出现的索引是" << a->lastIndexOf(3) << '\n';
    a->erase(3);
    cout << "删除元素3后元素3最后出现的索引是 " << a->lastIndexOf(3) << '\n';
    delete a;
}

void test20()
{
    auto a = new arrayList<int>(8,3);
    cout << "initialCapacity = " << a->capacity() << '\n';
    for (int i = 0; i < 9; i++)
        a->insert(i,i);
    cout << "a: " << (*a) << " arrayLength = " << a->capacity() << '\n';
    
    for (int i = 8; i > 4; i--)
        a->erase_shrink(i);

    cout << "删除4个元素后, a: " << (*a) << " arrayLength = " 
         << a->capacity() << '\n';
    
    delete a;
}

void test22()
{
    auto a = new arrayList<int>(10,10);
    for (int i = 0; i < 5; i++)
        a->insert(i,i);
    cout << "a: " << (*a) << '\n';
    a->reverse();
    cout << "使用成员函数颠倒顺序后a: " << (*a) << '\n';

    auto b = new arrayList<int>(10,10);
    for (int i = 0; i < 5; i++)
        b->insert(i,i);
    cout << "b: " << (*b) << '\n';
    reverse<int>(*b);
    cout << "使用外部函数颠倒顺序后b: " << (*b) << '\n';

    // 比较运行时间性能
    int len;
    cout << "请输入线性表长度:\n";
    std::cin >> len;
    if (len < 6) cerr << "len must be gt 6\n";

    for (int i = 5; i < len; i++)
    {
        a->push_back(i);
        b->push_back(i);
    }
    
    // 获取当前时间点
    auto start1 = std::chrono::steady_clock::now();
    a->reverse();
    auto end1 = std::chrono::steady_clock::now();
    // 计算时间差
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
    cout << "使用成员函数颠倒长度为" << len << "的线性表的运行时间是 " << duration1.count() << "ms\n";

    // 获取当前时间点
    auto start2 = std::chrono::steady_clock::now();
    reverse(*b);
    auto end2 = std::chrono::steady_clock::now();
    // 计算时间差
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
    cout << "使用外部函数颠倒长度为" << len << "的线性表的运行时间是 " << duration2.count() << "ms\n";
    
    delete a;
    delete b;
}

void test23()
{
    auto a = new arrayList<int>(5);
    for (int i = 0; i < 5; i++)
        a->insert(i,i);
    cout << "a: " << (*a) << '\n';
    a->leftshift(2);
    cout << "左移2个位置后a: " << (*a) << '\n';
    delete a;
}

void test24()
{
    auto a = new arrayList<int>(5);
    for (int i = 0; i < 5; i++)
        a->insert(i,i);
    cout << "a: " << (*a) << '\n';
    a->circularShift(2);
    cout << "循环左移2个位置后a: " << (*a) << '\n';
    delete a;
}

void test25()
{
    auto a = new arrayList<int>(10);
    int len;
    cout << "请输入线性表长度: ";
    std::cin >> len;

    for (int i = 0; i < len; i++)
        a->insert(i,i);
    cout << "a: " << (*a) << '\n';
    cout << "size: " << a->size() << '\n';
    a->half();
    cout << "成员函数half作用后a: " << (*a) << '\n';
    cout << "size: " << a->size() << '\n';
    delete a;
}

void test26()
{
    auto a = new arrayList<int>(10);
    int len;
    cout << "请输入线性表长度: ";
    std::cin >> len;

    for (int i = 0; i < len; i++)
        a->insert(i,i);
    cout << "a: " << (*a) << '\n';
    cout << "size: " << a->size() << '\n';
    half(*a);
    cout << "外部函数half作用后a: " << (*a) << '\n';
    cout << "size: " << a->size() << '\n';
    delete a;
}

void test27()
{
    auto a = new arrayList<int>(10);
    for (int i = 0; i < 10; i++)
        a->insert(i, 9 - i);
    cout << "排序前: " << (*a) << '\n';
    sort(a->begin(), a->end());
    cout << "排序后: " << (*a) << '\n';
    delete a;
}

void test28()
{
    auto a = new arrayList<int>(5);
    for (int i = 0; i < 5; i++)     a->push_back(i);
    auto b = new arrayList<int>(3);
    for (int i = 0; i < 3; i++)     b->push_back(i);
    auto c = meld(*a, *b);
    cout << "c: " << c << '\n';
    delete a;
    delete b;
}

void test29()
{
    auto a = new arrayList<int>(5);
    for (int i = 1; i < 5; i++)     a->push_back(2 * i - 1);
    auto b = new arrayList<int>(5);
    for (int i = 0; i < 4; i++)     b->push_back(2 * i);
    auto c = new arrayList<int>(10);
    c->merge(*a, *b);
    cout << "c: " << *c << '\n';
    delete a;
    delete b;
    delete c;
}

void test30()
{
    auto a = new arrayList<int>();
    auto b = new arrayList<int>();
    auto c = new arrayList<int>(7);
    for (int i = 0; i < 7; i++)     c->push_back(i);
    c->spilt(*a, *b);

    cout << "c: " << *c << '\n';
    cout << "a: " << *a << '\n';
    cout << "b: " << *b << '\n';
    delete a;
    delete b;
    delete c;
}

int main()
{
    test30();
    return 0;
}