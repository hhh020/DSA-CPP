// exercise 11.27
// 计算一棵链式二叉树的高度
#include "binaryTreeNode.h"
#include <utility>
#include <queue>

using std::queue;
using std::pair;
using std::make_pair;
using std::max;

/**
 * 思路一：广度搜索
 * 使用层次遍历，对每个结点做一个标记，记录其所在的层数
*/
template<typename T>
int binaryTreeHeight(binaryTreeNode<T> *t)
{
    if (t == nullptr)   return 0;

    queue<pair<int,binaryTreeNode<T>*>> q;
    int height = 1;

    q.push(make_pair(1,t));
    while (!q.empty())
    {
        height = q.front().first;
        t = q.front().second;

        if (t->leftChild != nullptr)
            q.push(make_pair(height + 1, t->leftChild));
        if (t->rightChild != nullptr)
            q.push(make_pair(height + 1, t->rightChild));

        q.pop();
    }
    return height;
}

/**
 * 思路2：分治
 * 求解左子树和右子树的高度，取较大值加一
*/
template<typename T>
int recBinaryTreeHeight(binaryTreeNode<T> *t)
{
    if (t == nullptr) return 0;
    return 1 + max(recBinaryTreeHeight(t->leftChild), recBinaryTreeHeight(t->rightChild));
}

int main()
{
    binaryTreeNode<int> t;
    initBinaryTree(&t);
    levelOrder(&t);
    cout << '\n';
    cout << binaryTreeHeight(&t) << '\n';
    cout << recBinaryTreeHeight(&t) << '\n';
}