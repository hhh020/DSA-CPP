// exercise 6
#include "maxHeap.h"

int main()
{
    auto h = new maxHeap<int>(1);
    auto a = new int[13]{0,3,5,6,7,20,8,2,9,12,15,30,17};
    h->initialize(a,12);
    h->printInArray();
    h->printInTree();

    h->push(15);
    h->printInTree();
    h->push(20);
    h->printInTree();
    h->push(45);
    h->printInTree();

    h->pop();
    h->printInTree();
    h->pop();
    h->printInTree();
    h->pop();
    h->printInTree();
    h->pop();
    h->printInTree();

    return 0;
}