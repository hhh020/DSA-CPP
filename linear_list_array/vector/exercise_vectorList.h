#ifndef __VECTOR_LIST__
#define __VECTOR_LIST__

#include "../data_structure/linear_list.h"
#include "../../myexcption.h"
#include <vector>

#include <algorithm>
#include <sstream>
#include <iterator>

using std::ostringstream;
using std::cout;
using std::find;
using std::copy;
using std::ostream_iterator;
using std::vector;

template<class T>
class vectorList : public LinearList<T>
{
    public:
        // 构造函数, 复制构造函数和析构函数
        vectorList(int initialCapacity = 10);
        vectorList(const vectorList<T>&);
        ~vectorList()   {delete element;};
    
        // ADT 方法
        bool empty() const override {return element->empty();}
        int size() const override {return (int) element->size();}
        T& get(int theIndex) const override;
        int indexOf(const T& theElement) const override;
        void erase(int theIndex) override;
        void insert(int theIndex, const T& theElement) override;
        void output(ostream& out) const override;

        // 增加的方法
        int capacity() const {return (int) element->capacity();}
        void half();
        
        // 线性表的起始和结束位置的迭代器
        typedef typename vector<T>::iterator iterator;
        iterator begin() {return element->begin();}
        iterator end() {return element->end();}

    protected:
        void checkIndex(int theIndex)   const;
        vector<T>* element; 
};

// 构造函数
template<class T>
vectorList<T>::vectorList(int initialCapacity)
{
    if (initialCapacity < 1)
    {
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalIndex(s.str());
    }

    element = new vector<T>;            // 创建空向量
    element->reserve(initialCapacity);  // vector向量从0增加到initialCapacity
}

// 复制构造函数
template<class T>
vectorList<T>::vectorList(const vectorList<T>& theList)
{
    element = new vector<T>(*theList.element);
}

// 确定索引在 0 ~ listSize - 1 之间
template<class T>
void vectorList<T>::checkIndex(int theIndex) const
{
    if (theIndex < 0 || theIndex >= size())
    {
        ostringstream s;
        s << "index = " << theIndex << " size = " << size();
        throw illegalIndex(s.str());
    }
}

// 删除索引为theIndex的元素
// 如果没有这个元素, 则抛出异常
template<class T>
void vectorList<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    element->erase(begin() + theIndex);
}

// 在索引为theIndex处插入元素theElement
template<class T>
void vectorList<T>::insert(int theIndex, const T& theElement)
{
    if (theIndex < 0 || theIndex > size())
    {
        ostringstream s;
        s << "index = " << theIndex << " size = " << size();
        throw illegalIndex(s.str());
    }

    element->insert(element->begin() + theIndex, theElement);
}

template<class T>
T& vectorList<T>::get(int theIndex) const
{
    checkIndex(theIndex);
    return (*element)[theIndex];
}

template<class T>
int vectorList<T>::indexOf(const T& theElement) const
{
    int theIndex = (int) (find(element->begin(), element->end(), theElement) - element->begin());
    return (theIndex == element->size()) ? -1 : theIndex;
}

// 把线性表插入输出流
template<class T>
void vectorList<T>::output(ostream& out) const
{
    copy(element->begin(), element->end(), ostream_iterator<T>(cout, " "));
}

// half: 将线性表元素隔一个删除一个
template<class T>
void vectorList<T>::half()
{
    size_t len = element->size();
    if (len < 2) return;
    if (len < 3) element->pop_back();

    auto slow = element->begin() + 1;   // slow pointer
    auto fast = element->begin() + 2;   // fast pointer
    while (fast < element->end())
    {
        *slow = *fast;
        slow++;
        fast += 2;
    }
    
    if (len & 0x1)  element->resize(len / 2 + 1);
    else element->resize(len / 2);
}

// 重载<<
template<class T>
ostream& operator<<(ostream& out, const vectorList<T>& v)
{
    v.output(out);
    return out;
}

#endif