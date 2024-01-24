// program 5-11
#ifndef __Iterator__
#define __Iterator__

#include <iterator>

using std::bidirectional_iterator_tag;

template<typename T>
class iterator
{
public:
    typedef bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;

    // 构造函数
    iterator(T* thePosition = 0) {position = thePosition;}

    // 解引用操作符
    T& operator*() const {return *position;}
    T* operator->() const {return &*position;}

    // 迭代器的值增加
    // 前加
    iterator& operator++() 
                {++position; return *this;}
    // 后加
    iterator operator++(int)
    {
        iterator old = *this;
        ++position;
        return old;
    }

    // 迭代器的值减少
    // 前减
    iterator& operator++()
                {--position; return *this;}
    // 后减
    iterator operator--(int)
    {
        iterator old = *this;
        --position;
        return old;
    }

    // 测试是否相等
    bool operator!=(const iterator right) const
            {return position != right.position;}
    bool operator==(const iterator right) const
            {return position == right.position;}
            
protected:
    T* position;
};

#endif