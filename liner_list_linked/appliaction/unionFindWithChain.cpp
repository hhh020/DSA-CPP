/**
 * program 6-20
 * 
 * equivNode是一个结构，类型为equivNode的数组node[1:n]用于描述n个元素，每个元素都有一个对应的等价类链表
 * node[e].equivClass既是find(e)的返回值，也是一个整型指针，指向等价类node[e].equivClass的链表的首节点
 * 只有e是链表的首节点，才定义node[e].size，表示从该节点开始的链表的节点个数
 * node[e].next给出了包含节点e的链表的下一个节点，0表示空指针NULL
*/

#include <algorithm>

struct equivNode
{
    int equivclass,         // 元素类标识符
        size,               // 类的元素个数
        next;               // 指向类中下一个元素的指针
};

equivNode *node;            // 节点的数组
int n;                      // 元素个数

void initialize(int numberOfElements)
{
    n = numberOfElements;
    node = new equivNode [n + 1];

    for (int i = 1; i <= n; i++)
    {
        node[i].equivclass = i;
        node[i].size = 1;
        node[i].next = 0;
    }
}

/**
 * 合并类classA 和 classB
 * classA和classB是链表首元素
*/
void unite(int classA, int classB)
{
    if (classA == classB) return;

    // 使classA成为较小的类
    if (node[classA].size > node[classB].size)
        std::swap(classA,classB);
    
    // 改变较小的类的equivClass值
    int k;
    for (k = classA; node[k].next != 0; k = node[k].next)
        node[k].equivclass = classB;
    node[k].equivclass = classB;        // 链表最后一个节点

    // 在classB的首元素之后插入链表classA
    // 修改链表大小
    node[classB].size += node[classA].size;
    node[k].next = node[classB].next;
    node[classB].next = classA;
}

/* 查找具有元素theElement的类 */
int find(int theElement)
{
    return node[theElement].equivclass;
}