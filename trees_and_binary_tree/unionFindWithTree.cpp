// 程序11-14 基于树结构的并查集问题解决方案

int *parent;

// 初始化numberOfElements棵树，每棵树一个元素
void initialize(int numberOfElements)
{
    parent = new int[numberOfElements + 1];
    for (int e = 1; e <= numberOfElements; e++)
        parent[e] = 0;
}

// 返回元素theElement所在的根
int find(int theElement)
{
    while (parent[theElement] != 0)
        theElement = parent[theElement];    // 向上移动一层
    return theElement;
}

// 合并两棵根节点不同的树
void unite(int rootA, int rootB)
{
    parent[rootA] = rootB;
}