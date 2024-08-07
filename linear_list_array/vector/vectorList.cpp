// program 5-13/5-14
#include "vectorList.h"
#include "../../cpp_review/illegalParameterValue/illegalParameterValue.h"

#include <algorithm>
#include <ostream>
#include <iterator>

using std::ostringstream;
using std::cout;
using std::find;
using std::copy;
using std::ostream_iterator;

// 构造函数
template<class T>
vectorList<T>::vectorList(int initialCapacity)
{
    if (initialCapacity < 1)
    {
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << "Must be > 0";
        throw illegalParameterValue(s.str());
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
        throw illegalParameterValue(s.str());
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
        throw illegalParameterValue(s.str());
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

// 重载<<
template<class T>
ostream& operator<<(ostream& out, const vectorList<T>& v)
{
    v.output(out);
    return out;
}