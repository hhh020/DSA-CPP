#ifndef __ARRAY_LIST__
#define __ARRAY_LIST__

#include "../data_structure/linear_list.h"

template<class T>
class arrayList : public LinearList<T>
{
public:
    // 构造函数，复制构造函数和析构函数
    arrayList(int initialCapacity = 10, int coefficient = 2);
    arrayList(const arrayList<T>&);
    ~arrayList() { delete [] element; }

    // ADT 方法
    bool empty() const override { return listSize == 0; }
    int size() const override { return listSize; }
    T& get(int theIndex) const override;
    int indexOf(const T& theElement) const override;
    void erase(int theIndex) override;
    void insert(int theIndex, const T& theElement) override;
    void output(ostream& out) const override;

    // 其他方法
    int capacity() const { return arrayLength; }
    void trimToSize();
    void setSize(int);
    T& operator[](int i);
    
protected:
    void checkIndex(int theIndex) const;
            // 若索引 theIndex 无效，则抛出异常
    T* element;             // 存储线性表元素的一维数组
    int arrayLength;        // 一维数组的容量
    int listSize;           // 线性表的元素个数
    int coefficient;        // 数组长度改变的系数
};

#endif