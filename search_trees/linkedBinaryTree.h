// base class for binary search tree 
#ifndef __LINKED_BINARY_TREE__
#define __LINKED_BINARY_TREE__

#include <iostream>

// program 11-8 
// binary tree ADT
#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

template<typename T>
class binaryTree
{
public:
    virtual ~binaryTree() {}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual void preOrder(void (*) (T *)) = 0;
    virtual void inOrder(void (*) (T *)) = 0;
    virtual void postOrder(void (*) (T *)) = 0;
    virtual void levelOrder(void (*) (T *)) = 0;
};

#endif

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

/*
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
*/

#endif

// members and method of class linkedBinaryTree
template<typename E>
class linkedBinaryTree : public binaryTree<binaryTreeNode<E>>
{
public:
    linkedBinaryTree() {root = nullptr; treeSize = 0};
    ~linkedBinaryTree() override {erase();}
    bool empty() const override {return treeSize == 0;}
    int size() const override {return treeSize;}
    void preOrder(void (*theVisit) (binaryTreeNode<E>*)) override
        {visit = theVisit; preOrder(root);}
    void inOrder(void (*theVisit) (binaryTreeNode<E>*)) override
        {visit = theVisit; inOrder(root);}
    void postOrder(void (*theVisit) (binaryTreeNode<E>*)) override
        {visit = theVisit; postOrder(root);}
    void levelOrder(void (*theVisit) (binaryTreeNode<E>*)) override;

    void erase() 
        {
            postOrder(dispose);
            root = nullptr;
            treeSize = 0;
        }
    void preOrderOutput() {preOrder(output); cout << '\n';}
    void inOrderOutput() {inOrder(output); cout << '\n';}
    void postOrderOutput() {postOrder(output); cout << '\n';}
    int height() const {return height(root);}

private:
    binaryTreeNode<E> *root;
    int treeSize;
    // 声明为私有静态成员函数，这样既保证了这些函数只在类内部有效，又因为其静态属性而无需为每个对象实例创建单独的函数副本。
    static void (*visit) (binaryTreeNode<E>*);      // 访问函数
    static void preOrder(binaryTreeNode<E> *t);
    static void inOrder(binaryTreeNode<E> *t);
    static void postOrder(binaryTreeNode<E> *t);
    static void dispose(binaryTreeNode<E> *t) {delete t;}
    static void output(binaryTreeNode<E> *t) {cout << t->element << ' ';}
    static int height(binaryTreeNode<E> *t);
};

// 类的私有前序遍历方法
template<typename E>
void linkedBinaryTree<E>::preOrder(binaryTreeNode<E> *t)
{
    if (t != nullptr)
    {
        linkedBinaryTree<E>::visit(t);
        preOrder(t->leftChild);
        preOrder(t->rightChild);
    }
}

// 类的私有中序遍历方法
template<typename E>
void linkedBinaryTree<E>::inOrder(binaryTreeNode<E> *t)
{
    if (t != nullptr)
    {
        inOrder(t->leftChild);
        linkedBinaryTree<E>::visit(t);
        inOrder(t->rightChild);
    }
}

// 类的私有后序遍历方法
template<typename E>
void linkedBinaryTree<E>::postOrder(binaryTreeNode<E> *t)
{
    if (t != nullptr)
    {
        postOrder(t->leftChild);
        postOrder(t->rightChild);
        linkedBinaryTree<E>::visit(t);
    }
}

// 确定二叉树高度
template<typename E>
int linkedBinaryTree<E>::height(binaryTreeNode<E> *t)
{
    if (t == nullptr)
        return 0;
    int hl = height(t->leftChild);
    int hr = height(t->rightChild);
    if (hl > hr) return ++hl;
    else return ++hr;
}

#endif