#include <iostream>
using namespace std;

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

int main()
{
    int ** x;
    try {make2dArray(x,3,5);}
    catch (const bad_alloc& e)
    {
        cerr << "could not create x" << endl;
        exit(1);
    }
    delete2dArray(x,3);
    return 0;
}