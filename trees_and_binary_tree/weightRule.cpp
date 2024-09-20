// 程序11-15 ~ 11-17

// 实现重量规则时使用的结构
struct unionFindNode
{
    int parent;         // 如果是根，表示树的重量；否则，指向父节点
    bool root;          // 当且仅当是根时，值为ture

    unionFindNode()
    {
        parent = 1;
        root = true;
    }
};

struct unionFindNode *node;
// 使用重量规则进行合并
void initialize(int numberOfElements)
{
    node = new unionFindNode[numberOfElements + 1];
}

// 返回元素所在的根
int find(int theElement)
{
    while (!node[theElement].root)
        theElement = node[theElement].parent;
    return theElement;
}

// 使用重量规则，合并其根不同的树
void unite(int rootA, int rootB)
{
    if (node[rootA].parent < node[rootB].parent)
    {
        node[rootB].parent += node[rootA].parent;
        node[rootA].parent = rootB;
        node[rootA].root = false;
    }
    else
    {
        node[rootA].parent += node[rootB].parent;
        node[rootB].parent = rootA;
        node[rootB].root = false;
    }
}

// 利用路径紧缩来查找一个元素
int find(int theElement)
{
    int theRoot = theElement;
    while (!node[theRoot].root)
        theRoot = node[theRoot].parent;
    
    // 紧缩从theElement到theRoot的路径
    int currentRoot = theElement;
    while (currentRoot != theRoot)
    {
        int parentNode = node[currentRoot].parent;
        node[currentRoot].parent = theRoot;
        currentRoot = parentNode;
    }

    return theRoot;
}