/**
 *  program 6-12 
 *  and provide complete code
*/
#ifndef __EXTENDED_CHAIN__
#define __EXTENDED_CHAIN__

#include "extendedLinearList.h"
#include "chainNode.h"
#include "../../myexcption.h"
#include <sstream>

template<class T>
class extendedChain : public extendedLinearList
{
    public:
        // constructor & destructor
        extendedChain(int initialCapacity = 10);
        extendedChain(const extendedChain<T>&);
        ~extendedChain();

        // ADT
        bool empty() const override{return listSize == 0;}
        int size() const override{return listSize;}
        T& get(int theIndex) const override;
        int indexOf(const T& theElement) const override;
        void erase(int theIndex) override;
        void insert(int theIndex, const T& theElement) override;
        void output(ostream& out) const override;
        void clear() override;
        void push_back(const T& theElement) override;

    protected:
        void checkIndex(int theIndex) const;    // index invaild, throw exception
        chainNode<T>* firstNode;                // point to first node
        chainNode<T>* lastNode;                 // point to last node
        int listSize;                           // element number of linear list
};

// no change
template<class T>
extendedChain<T>::extendedChain(int initialCapacity)
{
    if (initialCapacity < 1)
    {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalIndex(s.str());
    }
}

// mainly replace targetNode to lastNode
template<class T>
extendedChain<T>::extendedChain(const extendedChain<T>& theList)
{
    listSize = theList.listSize;

    if (listSize == 0) // theList is empty
    {
        firstNode == NULL;
        lastNode == NULL;
        return;
    }

    chainNode<T>* sourceNode = theList.firstNode;       // 复制theList的节点
    firstNode = new chainNode<T>(sourceNode->element);  // 复制theList的首元素
    sourceNode = sourceNode->next;
    lastNode = firstNode;                               // 当前链表*this的最后一个节点
    while (sourceNode != NULL)                          // 复制剩余元素
    {
        lastNode->next = new chainNode<T>(sourceNode->element);
        lastNode = lastNode->next;
        sourceNode = sourceNode->next;
    }

    lastNode->next = NULL;                              // 链表结束
}

// add lastNode
template<class T>
extendedChain<T>::~extendedChain()
{
    while (firstNode != lastNode)
    {
        chainNode<T>* nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
    delete lastNode;
}

// no change
template<class T>
void extendedChain<T>::checkIndex(int theIndex) const
{
    if (theIndex < 0 || theIndex > listSize - 1)
    {
        std::ostringstream s;
        s << "Index = " << theIndex << " Must be non-negative and less than listSize";
        throw illegalIndex(s.str());
    }
}

// no change
template<class T>
T& extendedChain<T>::get(int theIndex) const
{
    checkIndex(theIndex);

    chainNode<T> *currentNode = firstNode;
    for (int i = 0; i < theIndex; i++)
        currentNode = currentNode->next;
    return currentNode->element;
}

// no change
template<class T>
int extendedChain<T>::indexOf(const T& theElement) const
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
 * 删除的元素是*lastNode时要改变lastNode
*/
template<class T>
void extendedChain<T>::erase(int theIndex)
{
    checkIndex(theIndex);

    chainNode<T> *deleteNode;
    if (theIndex = 0)
    {
        if (firstNode == lastNode)
            lastNode = lastNode->next;
        deleteNode = firstNode;
        firstNode = firstNode->next;
    }
    else
    {
        chainNode<T> *p = firstNode;
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next;
        
        deleteNode = p->next;
        if (deleteNode == lastNode)
            lastNode = p;
        p->next = p->next->next;
    }

    listSize--;
    delete deleteNode;
}

/**
 * 在表头和表尾插入需要改动lastNode
*/
template<class T>
void extendedChain<T>::insert(int theIndex, const T& theElement)
{
    if (theIndex < 0 || theIndex > listSize)
    {
        std::ostringstream s;
        s << "Index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }

    if (theIndex == 0)
        // 在链表头插入
        firstNode = lastNode = new chainNode<T>(theElement, firstNode);
    else if (theIndex == listSize)
        // 在链表尾插入
        push_back(theElement);
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

/**
 * 删除链表所有节点
*/
template<class T>
void extendedChain<T>::clear()
{
    while (firstNode != NULL)
    {
        chainNode<T>* nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
    listSize = 0;
}

/**
 * 在链表尾端插入元素theElement的节点
*/
template<class T>
void extendedChain<T>::push_back(const T& theElement)
{
    chainNode<T>* newNode = new chainNode(theElement, NULL);
    if (firstNode == NULL)
    {
        firstNode = lastNode = newNode;
    }
    else
    {
        lastNode->next = newNode;
        lastNode = newNode;
    }
    listSize++;
}

#endif