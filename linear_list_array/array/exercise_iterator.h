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