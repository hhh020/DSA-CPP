// 11-9 
#include "binaryTree.h"
#include "binaryTreeNode.h"

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

private:
    binaryTreeNode<E> *root;
    int treeSize;
    // 声明为私有静态成员函数，这样既保证了这些函数只在类内部有效，又因为其静态属性而无需为每个对象实例创建单独的函数副本。
    static void (*visit) (binaryTreeNode<E>*);      // 访问函数
    static void preOrder(binaryTreeNode<E> *t);
    static void inOrder(binaryTreeNode<E> *t);
    static void postOrder(binaryTreeNode<E> *t);
    static void dispose(binaryTreeNode<E> *t) {delete t;}
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