/* program 6-2 ~ 6-9 */
#ifndef __CHAIN__
#define __CHAIN__

#include "../linearList.h"
#include "chainNode.h"
#include "../../myexcption.h"
#include <sstream>

template<class T>
class chain : public LinearList<T>
{
    public:
        // constructor & destructor
        chain(int initialCapacity = 10);
        chain(const chain<T>&);
        ~chain();

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
        chainNode<T>* firstNode;                // point to first node
        int listSize;                           // element number of linear list
};

template<class T>
chain<T>::chain(int initialCapacity)
{
    if (initialCapacity < 1)
    {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalIndex(s.str());
    }
}

template<class T>
chain<T>::chain(const chain<T>& theList)
{
    listSize = theList.listSize;

    if (listSize == 0) // theList is empty
    {
        firstNode == NULL;
        return;
    }

    chainNode<T>* sourceNode = theList.firstNode;       // 复制theList的节点
    firstNode = new chainNode<T>(sourceNode->element);  // 复制theList的首元素
    sourceNode = sourceNode->next;
    chainNode<T>* targetNode = firstNode;               // 当前链表*this的最后一个节点
    while (sourceNode != NULL)                          // 复制剩余元素
    {
        targetNode->next = new chainNode<T>(sourceNode->element);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }
    targetNode->next = NULL;                            // 链表结束
}

template<class T>
chain<T>::~chain()
{
    while (firstNode != NULL)
    {
        chainNode<T>* nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template<class T>
void chain<T>::checkIndex(int theIndex) const
{
    if (theIndex < 0 || theIndex > listSize - 1)
    {
        std::ostringstream s;
        s << "Index = " << theIndex << " Must be non-negative and less than listSize";
        throw illegalIndex(s.str());
    }
}

/**
 * 返回索引为theIndex的元素
 * 若该元素不存在，则抛出异常
*/
template<class T>
T& chain<T>::get(int theIndex) const
{
    checkIndex(theIndex);

    chainNode<T> *currentNode = firstNode;
    for (int i = 0; i < theIndex; i++)
        currentNode = currentNode->next;
    return currentNode->element;
}

/**
 * 返回元素theElement首次出现的索引
 * 若该元素不存在，则返回-1
*/
template<class T>
int chain<T>::indexOf(const T& theElement) const
{
    chainNode<T> *currentNode = firstNode;
    int index = 0;          
    while (currentNode != NULL && currentNode->element != theElement)
    {
        currentNode = currentNode->next;
        index++;
    }

    if (currentNode == NULL)
        return -1;
    else
        return index;
}

/**
 * 删除索引为theIndex的元素
 * 若该元素不存在，则抛出异常
*/
template<class T>
void chain<T>::erase(int theIndex)
{
    checkIndex(theIndex);

    chainNode<T> *deleteNode;
    if (theIndex = 0)
    {
        deleteNode = firstNode;
        firstNode = firstNode->next;
    }
    else
    {
        chainNode<T> *p = firstNode;
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next;
        
        deleteNode = p->next;
        p->next = p->next->next;
    }

    listSize--;
    delete deleteNode;
}

/**
 * 在索引为theIndex的位置上插入元素theElement
*/
template<class T>
void chain<T>::insert(int theIndex, const T& theElement)
{
    if (theIndex < 0 || theIndex > listSize)
    {
        std::ostringstream s;
        s << "Index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }

    if (theIndex == 0)
        // 在链表头插入
        firstNode = new chainNode<T>(theElement, firstNode);
    else
    {
        // 寻找插入位置的前驱
        chainNode<T> *p = firstNode;
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next;
        
        p->next = new chainNode<T>(theElement, p->next);
    }
    listSize++;
}

/* 把链表放入输出流 */
template<class T>
void chain<T>::output(ostream& out) const
{
    for (chainNode<T> *currentNode = firstNode; currentNode != NULL; currentNode = currentNode->next)
        out << currentNode->element << " ";
}

/* 重载<< */
template<class T>
ostream& operator<<(ostream& out, const chain<T>& x)
{
    x.output(out);
    return out;
}

#endif