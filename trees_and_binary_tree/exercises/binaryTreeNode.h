// binary tree node for exercises in chapter 11
#ifndef _BINARY_TREE_NODE_H_
#define _BINARY_TREE_NODE_H_

#include <iostream>
#include <queue>
using std::cout;
using std::cin;
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

// 层次遍历构造二叉树
// 假设元素为int类型，根据输入序列构造二叉树
// 0 : 该结点不存在, -1 终止
template<typename T>
void initBinaryTree(binaryTreeNode<T> *t)
{
    int theElement;    cin >> theElement;
    if (theElement == 0) return;            // 根结点为空指针
    
    queue<binaryTreeNode<T>*> q;            
    t->element = theElement;
    q.push(t);

    while (!q.empty())                      // 保证树合法
    {
        t = q.front();                      // 取出队首元素
        q.pop();

        cin >> theElement;
        if (theElement == -1) break;
        else if (theElement != 0)           // 构造左孩子
        {
            t->leftChild = new binaryTreeNode<T>(theElement);
            q.push(t->leftChild);
        }
        
        cin >> theElement;
        if (theElement == -1) break;
        else if (theElement != 0)           // 构造右孩子
        {
            t->rightChild = new binaryTreeNode<T>(theElement);
            q.push(t->rightChild);
        }
    }
}

#endif