/* program 6-13 带有头节点的循环链表 */
#ifndef __CIRCULAR_LIST_WITH_HEADER__
#define __CIRCULAR_LIST_WITH_HEADER__

#include "../linearList.h"
#include "../singly_linked_list/chainNode.h"
#include "../../myexcption.h"
#include <sstream>

template<class T>
class circularListWithHeader : public LinearList<T>
{
    public:
        // constructor & destructor
        circularListWithHeader();
        circularListWithHeader(const circularListWithHeader<T>&);
        ~circularListWithHeader();

        // ADT
        bool empty() const override{return listSize == 0;}
        int size() const override{return listSize;}
        T& get(int theIndex) const override;
        int indexOf(const T& theElement) const override;
        void erase(int theIndex) override;
        void insert(int theIndex, const T& theElement) override;
        void output(ostream& out) const override;
    
    protected:
        void checkIndex(int theIndex) const;    // index invaild, throw exception
        chainNode<T>* headerNode;                // point to first node
        int listSize;                           // element number of linear list
};

template<class T>
circularListWithHeader<T>::circularListWithHeader()
{
    headerNode = new chainNode();
    headerNode->next = NULL;
    listSize = 0;
}

template<class T>
int circularListWithHeader<T>::indexOf(const T& theElement) const
{
    // 将元素放入头节点
    headerNode->element = theElement;

    // 在链表种搜索theElement
    chainNode<T>* currentNode = headerNode->next;
    int index = 0;
    while (currentNode->element != theElement)
    {
        currentNode = currentNode->next;
        index++;
    }

    // 确定是否找到元素theElement
    if (currentNode == headerNode)  return -1;
    else return index;
}

#endif