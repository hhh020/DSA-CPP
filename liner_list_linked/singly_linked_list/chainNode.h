/* program 6-1 */
#ifndef __CHAIN_NODE__
#define __CHAIN_NODE__

template <class T>
struct chainNode
{
    // data member
    T element;
    chainNode<T> *next;

    // method
    chainNode() {}
    chainNode(const T& element) {
        this->element = element;
    }
    chainNode(const T& element, chainNode<T>* next) {
        this->element = element;
        this->next = next;
    }
};

#endif