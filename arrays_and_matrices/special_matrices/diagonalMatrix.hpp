/* program 7.8 ~ 7.10 */

#ifndef __DIAGONAL_MATRIX__
#define __DIAGONAL_MATRIX__

#include <ostream>
#include <algorithm>
#include "../../myexcption.h"
#include "../matrixException.hpp"

using std::ostream;
using std::copy;

template<class T>
class diagonalMatrix
{
public:
    diagonalMatrix(int theN = 10);
    ~diagonalMatrix() { delete [] element };
    T get(int, int) const;
    void set(int, int, const T&);

private:
    int n;          // 维数
    T *element;     // 存储对角矩阵的一维数组
};

template<class T>
diagonalMatrix<T>::diagonalMatrix(int theN)
{
    if (theN < 1)
        throw illegalParameterValue("Matrix size must be > 0");

    n = theN;
    element = new T [n];    
}

template<class T>
T diagonalMatrix<T>::get(int i, int j) const
{
    if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutofBounds();
    
    if (i == j) return element[i-1];
    else return 0;
}

template<class T>
void diagonalMatrix<T>::set(int i, int j, const T& newValue)
{
    if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutofBounds();
    
    if (i == j) element[i-1] = newValue;
    else 
        // 非对角线元素必须是0
        if (newValue != 0)
            throw illegalParameterValue("nondiagonal elements must be zero");
}

#endif