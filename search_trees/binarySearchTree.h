// program 14-3 ~ 14-6
// 类 binarySearchTree 的实现

#ifndef __binary_Search_Tree__
#define __binary_Search_Tree__

#include "bsTree.h"
#include "linkedBinaryTree.h"

template<typename K, typename E>
class binarySearchTree : public bsTree<K, E>, public linkedBinaryTree<pair<const K, E>>
{
    void ascend() override {inOrderOutput();}
    void insert(const pair<const K, E>&) override;
    void erase(const K& theKey) override;
    pair<const K, E>* find(const K& theKey) const override;

private:
    binaryTreeNode<pair<const K, E>> *root;
    int treeSize;
};

template<typename K, typename E>
pair<const K, E>* binarySearchTree<K, E>::find(const K& theKey) const
{
    binaryTreeNode<pair<const K, E>> *p = root;
    while (p != nullptr)
    {
        if (theKey < p->element.first)
            p = p->leftChild;
        else if (theKey > p->element.first)
            p = p->rightChild;
        else                        // 找到匹配的元素
            return &p->element;
    }

    return nullptr;
}

template<typename K, typename E>
void binarySearchTree<K, E>::insert(const pair<const K, E>& thePair)
{
    binaryTreeNode<pair<const K, E>> *p = root, *parent = nullptr;
    while (p != nullptr)
    {
        parent = p;
        if (thePair.first < p->element.first)
            p = p->leftChild;
        else if (thePair.first > p->element.first)
            p = p->rightChild;
        else
        {
            p->element.second = thePair.second;
            return;
        }
    }

    // 为thePair建立一个节点， 然后与parent连接
    p = new binaryTreeNode<pair<const K, E>>(thePair);
    if (root != nullptr)    // 树不空
    {
        if (thePair.first < parent->element.first)
            parent->leftChild = p;
        else
            parent->rightChild = p;
    }
    else
        root = p;           // 插入空树
    treeSize++;
}

// 删除关键字等于theKey的数对
template<typename K, typename E>
void binarySearchTree<K, E>::erase(const K& theKey)
{
    // 查找关键字为theKey的节点
    binaryTreeNode<pair<const K, E>> *p = root, *parent = nullptr;
    while (p != nullptr && p->element.first != theKey)
    {
        parent = p;
        if (theKey < p->element.first)
            p = p->leftChild;
        else
            p = p->rightChild;
    }

    if (p == nullptr)
        return;
    
    // 重新组织树结构
    // 当p有两个孩子时的处理
    // 转化为空或只有一个孩子
    // 在p的左子树中寻找一个最大节点， 用这个节点替换p
    if (p->leftChild != nullptr && p->rightChild != nullptr)
    {
        binaryTreeNode<pair<const K, E>> *s = p->leftChild,
                                        *ps = p;    // s的双亲
        while (s->rightChild != nullptr)
        {
            ps = s;
            s = s->rightChild;
        }

        // 将最大元素s移到p但不是简单的移动
        // p->element = s->element, 因为key是常量
        binaryTreeNode<pair<const K, E>> *q = 
            new binaryTreeNode<pair<const K, E>>(s->element, p->rightChild, p->rightChild);
        
        if (parent == nullptr)  // p是根节点
            root = q;
        else if (p = parent->leftChild)
            parent->leftChild = q;
        else
            parent->rightChild = q;
        
        if (ps == p) parent = q;    // 防止删除p导致ps为空
        else parent = ps;
        delete p;
        p = s;
    }

    // p(s)最多有一个孩子
    // 把孩子指针放在c
    binaryTreeNode<pair<const K, E>> *c = nullptr;
    if (p->leftChild != nullptr)
        c = p->leftChild;
    else 
        c = p->rightChild;
    
    // 删除p
    if (p == root)
        root = c;
    else
    {
        // p 是parent的左或右孩子
        if (p == parent->leftChild)
            parent->leftChild = c;
        else
            parent->rightChild = c;
    }
    treeSize--;
    delete p;
}

#endif