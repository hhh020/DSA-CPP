// program 5-12
#ifndef __VECTOR_LIST__
#define __VECTOR_LIST__

#include "../data_structure/linear_list.h"
#include <vector>

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
        bool empty() const override {return element->empty()};
        int size() const override {return (int) element->size();}
        T& get(int theIndex) const override;
        int indexOf(const T& theElement) const override;
        void erase(int theIndex) override;
        void insert(int theIndex, const T& theElement) override;
        void output(ostream& out) const override;

        // 增加的方法
        int capacity() const {return (int) element->capacity();}

        // 线性表的起始和结束位置的迭代器
        typedef typename vector<T>::iterator iterator;
        iterator begin() {return element->begin();}
        iterator end() {return element->end();}

    protected:
        void checkIndex(int theIndex)   const;
        vector<T>* element; 
};

#endif