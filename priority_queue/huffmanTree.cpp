// program 12-10 构造一棵霍夫曼树
// 使用11.8节定义的类LinkedBinartyTree<int>作为二叉树
// 用小根堆存储二叉树的集合, 每个元素包括一个二叉树和它的权

#include "../trees_and_binary_tree/linkedBinaryTree.h"
#include "minHeap.h"

template <typename T>
struct huffmanNode
{
    linkedBinaryTree<int> *tree;
    T weight;
};

// 用权weight[1:n]生成霍夫曼树，n >= 1
template <typename T>
linkedBinaryTree<int>* huffmanTree(T weight[], int n)
{
    // 创建一棵单节点树
    huffmanNode<T> *hNode = new huffmanNode<T> [n + 1];
    linkedBinaryTree<int> emptyTree;
    for (int i = 1; i <= n; i++)
    {
        hNode[i].weight = weight[i];
        hNode[i].tree = new linkedBinaryTree<int>;
        hNode[i].tree->makeTree(i, emptyTree, emptyTree);
    }

    // 使一组单节点树构成小根堆
    minHeap<huffmanNode<T>> heap(1);
    heap.initialize(hNode, n);

    // 不断从小根堆中提取两棵树并合并，直到只剩下一棵树
    huffmanNode<T> w, x, y;
    linkedBinaryTree<int> *z;
    for (int i = 1; i < n; i++)
    {
        // 从小根堆中挑出最轻的两棵树
        x = heap.top(); heap.pop();
        y = heap.top(); heap.pop();

        // 合并成一棵树
        z = new linkedBinaryTree<int>;
        z->makeTree(0, *x.tree, *y.tree);
        w.weight = x.weight + y.weight;
        w.tree = z;
        heap.push(w);
        delete x.tree;
        delete y.tree;
    }

    return heap.top().tree;
}