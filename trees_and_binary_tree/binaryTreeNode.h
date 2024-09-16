// program 11-1
#ifndef _BINARY_TREE_NODE_H_
#define _BINARY_TREE_NODE_H_

#include <iostream>
#include <queue>
using std::cout;
using std::queue;

// node structure of binary tree bases on linked list
template<typename T>
struct binaryTreeNode
{
    T element;
    binaryTreeNode<T> *leftChild,
                      *rightChild;

    binaryTreeNode() {leftChild = rightChild = nullptr; }
    binaryTreeNode(const T& theElement)
    {
        element = theElement;
        leftChild = rightChild = nullptr;
    }
    binaryTreeNode(const T& theElement,
                   binaryTreeNode *theLeftChild,
                   binaryTreeNode *theRightChild)
    {
        element = theElement;
        leftChild = theLeftChild;
        rightChild = theRightChild;
    }
};

// 访问节点
template<typename T>
void visit(binaryTreeNode<T> *x)
{
    cout << x->element << ' ';
}

// 前序遍历二叉树
template<typename T>
void preOrder(binaryTreeNode<T> *t)
{
    if (t != nullptr)
    {
        visit(t);                   // 访问树根
        preOrder(t->leftChild);     // 前序遍历左子树
        preOrder(t->rightChild);    // 前序遍历右子树
    }
}

// 中序遍历二叉树
template<typename T>
void inOrder(binaryTreeNode<T> *t)
{
    if (t != nullptr)
    {
        inOrder(t->leftChild);
        visit(t);
        inOrder(t->rightChild);
    }
}

// 后序遍历二叉树
template<typename T>
void postOrder(binaryTreeNode<T> *t)
{
    if (t != nullptr)
    {
        postOrder(t->leftChild);
        postOrder(t->rightChild);
        visit(t);
    }
}

// 层次遍历
template<typename T>
void levelOrder(binaryTreeNode<T> *t)
{
    queue<binaryTreeNode<T>*> q;
    while (t != nullptr)
    {
        visit(t);

        if (t->leftChild != nullptr)
            q.push(t->leftChild);
        if (t->rightChild != nullptr)
            q.push(t->rightChild);
        
        if (!q.empty())
        {
            t = q.front();
            q.pop();
        }
        else return;
    }
}

#endif