// exercise 11.28
// 计算一棵链式二叉树结点的个数
#include "binaryTreeNode.h"

template<typename T>
int countNode(binaryTreeNode<T> *root)
{
    if (!root)
        return 0;
    return 1 + countNode(root->leftChild) + countNode(root->rightChild);
}

int main()
{
    binaryTreeNode<int> t;
    initBinaryTree(&t);
    cout << countNode(&t) << '\n';
    return 0;
}
