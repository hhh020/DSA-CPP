// 16-1 抽象类gragh
#ifndef __GRAPH_H__
#define __GRAPH_H__

// 模板类edge
template<typename T>
struct edge
{
    int v1;
    int v2;
    T w;

    edge(int _v1, int _v2, T _w)
    {
        v1 = _v1;
        v2 = _v2;
        w = _w;
    }

    int vertex1() const { return v1; }
    int vertex2() const { return v2; }
    int weight() const { return w; }
};

// 模板类vertexIterator
template<typename T>
class vertexIterator
{
public:
    virtual ~vertexIterator() {}
    virtual int next() = 0;
    virtual int next(T&) = 0;   // 用于加权图
};

template<typename T>
class graph
{
public:
    virtual ~graph() {}

    // ADT 方法
    virtual int numberOfVertices() const = 0;
    virtual int numberOfEdges() const = 0;
    virtual bool existEdge(int, int) const = 0;
    virtual void insertEdge(edge<T>*) = 0;
    virtual void eraseEdge(int, int) = 0;
    virtual int degree(int) const = 0;
    virtual int inDegree(int) const = 0;
    virtual int outDegree(int) const = 0;

    // 其他方法
    virtual bool directed() const = 0;  // 是否是有向图
    virtual bool weighted() const = 0;  // 是否是加权图
    virtual vertexIterator<T>* iterator(int) = 0;   // 返回指定定点的相邻顶点
};

#endif