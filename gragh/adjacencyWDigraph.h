// program 16-2 

#ifndef __ADJACENCY_W_DI_GRAPH_H__
#define __ADJACENCY_W_DI_GRAPH_H__

#include "gragh.h"
#include "../myexcption.h"

#include <algorithm>
#include <sstream>

using std::fill;
using std::ostringstream;

// program 1-11/1-12
template <class T>
void make2dArray(T ** &x, int rows, int cols)   // 创建一个二维数组
{
    // 创建行指针
    x = new T * [rows];

    // 为每一行分配空间
    for (int i = 0; i < rows; i++)
        x[i] = new T [cols];
}

template <class T>
void delete2dArray(T ** &x, int rows)           // 删除二维数组
{
    // 删除行数组空间
    for (int i = 0; i < rows; i++)
        delete [] x[i];
    
    // 删除行指针
    delete [] x;
    x = nullptr;
}

// 加权有向图的成本邻接矩阵
template<typename T>
class adjacencyWDigraph : public Digraph<T>
{
protected:
    int n;      // 顶点数
    int e;      // 边数
    T **a;      // 邻接数组
    T noEdge;   // 表示不存的边

public:
    adjacencyWDigraph(int numberOfVertices = 0, T theNoEdge = 0)
    {
        if (numberOfVertices < 0)
            throw illegalParameterValue("The number of vertices must be >= 0");
        n = numberOfVertices;
        e = 0;
        noEdge = theNoEdge;
        make2dArray(a, n + 1, n + 1);
        for (int i = 1; i <= n; i++)    // 初始化邻接矩阵
            fill(a[i], a[i] + n + 1, noEdge);
    }

    ~adjacencyWDigraph() { delete2dArray(a, n + 1); }
    int numberOfVertices() const override {return n;}
    int numberOfEdges() const override {return e;}
    bool directed() const override {return true;}
    bool existEdge(int i, int j) const override
    {
        if (i < 1 || i > n || j < 1 || j > n || a[i][j] == noEdge)
            return false;
        else
            return true;
    }

    // 插入边，如果该边已经存在，则用theEdge->weight()修改边的权
    void insertEdge(edge<T> *theEdge)
    {
        int v1 = theEdge->vertex1();
        int v2 = theEdge->vertex2();
        if (v1 < 1 || v1 > n || v2 < 1 || v2 > n || v1 == v2)
            throw illegalIndex("vertex index is not permissible");
        
        if (a[v1][v2] == noEdge)    // 新的边
            e++;
        a[v1][v2] = theEdge->weight();
    }
    
    // 删除边(i,j)
    void eraseEdge(int i, int j)
    {
        if (i >= 1 && j >= 1 && i <= n && j <= n && a[i][j] != noEdge)
        {
            a[i][j] = noEdge;
            e--;
        }
    }

    // 确定是有效顶点
    void checkVertex(int theVertex) const
    {
        if (theVertex < 1 || theVertex > n)
            throw illegalIndex("no vertex");
    }

    int degree(int theVertex) const override
        {throw undefinedMethod("degree undefined");}
    
    // 返回定点theVertex的出度
    int outDegree(int theVertex) const override
    {
        checkVertex(theVertex);

        // 计数关联于顶点theVertex的边数
        int sum = 0;
        for (int i = 1; i <= n; i++)
            if (a[theVertex][i] != noEdge)
                sum++;
        
        return sum;
    }

    // 返回定点theVertex的入度
    int inDegree(int theVertex) const override
    {
        checkVertex(theVertex);

        // 计数关联至顶点theVertex的边数
        int sum = 0;
        for (int i = 1; i <= n; i++)
            if (a[i][theVertex] != noEdge)
                sum++;
        
        return sum;
    }
};

#endif