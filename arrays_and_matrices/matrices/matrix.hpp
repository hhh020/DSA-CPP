/* program 7.2 ~ 7.7 */

#ifndef __MATRIX__
#define __MATRIX__

#include <ostream>
#include <algorithm>
#include "../../myexcption.h"
#include "../matrixException.hpp"

using std::ostream;
using std::copy;

template<class T>
class matrix
{
    friend ostream& operator<<(ostream&, const matrix<T>&);
public:
    matrix(int theRows = 0, int theColumns = 0);
    matrix(const matrix<T>&);
    ~matrix() {delete [] element};
    int rows() const {return theRows;}
    int columns() const {return theColumns;}
    T& operator() (int i, int j) const;
    matrix<T>& operator=(const matrix<T>&);
    matrix<T> operator+() const;                // unary +
    matrix<T> operator+(const matrix<T>&) const;
    matrix<T> operator-() const;                // unary -   
    matrix<T> operator-(const matrix<T>&) const;
    matrix<T> operator*(const matrix<T>&) const;
    matrix<T>& operator+=(const T&) const;

private:
    int theRows,               
        theColumns;
    T *element;
};

template<class T>
matrix<T>::matrix(int theRows, int theColumns)
{
    // check rows and columns legal
    if (theRows < 0 || theColumns < 0)
        throw illegalParameterValue("Rows and columns must be >= 0");
    if (!theRows ^ !theColumns)         // xor
        throw illegalParameterValue("Either both or neither rows and columns should be zero");

    // 创建矩阵
    this->theRows = theRows;
    this->theColumns = theColumns;
    element = new T [theRows * theColumns];    
}

template<class T>
matrix<T>::matrix(const matrix<T>& m)
{
    this->theRows = m.theRows;
    this->theColumns = m.theColumns;
    element = new T [theRows * theColumns];

    copy(m.element, m.element + theRows * theColumns, element);
}

template<class T>
matrix<T>& matrix<T>::operator=(const matrix<T>& m)
{
    if (this != m)
    {
        delete [] element;
        this->theRows = m.theRows;
        this->theColumns = m.theColumns;
        element = new T [theRows * theColumns];
        
        copy(m.element, m.element + theRows * theColumns, element);
    }
    return *this;
}

template<class T>
T& matrix<T>::operator() (int i, int j) const
{
    if (i < 1 || i > theRows || j < 1 || j > theColumns)
        throw matrixIndexOutofBounds();
    
    return element[(i - 1) * theColumns + j - 1];
}

template<class T>
matrix<T> matrix<T>::operator+(const matrix<T>& m) const
{
    if (theRows != m.theRows || theColumns != m.theColumns)
        throw matrixSizeMismatch();

    // 生成结果矩阵
    matrix<T> w(theRows, theColumns);
    for (auto i = 0; i < theRows * theColumns; i++)
        w.element[i] = element[i] + m.element[i];

    return w;
}

template<class T>
matrix<T> matrix<T>::operator*(const matrix<T>& m) const
{
    if (theColumns != m.theRows)
        throw matrixSizeMismatch();
    
    matrix<T> w(theRows, m.theColumns);     // result
    int ct = 0, cm = 0, cw = 0;

    for (int i = 1; i <= theRows; i++) {
        for (int j = 1; j <= m.theColumns; j++)
        {
            T sum = element[ct] * m.element[cm];
            for (int k = 2; k <= theColumns; k++)
            {
                ct++;
                cm += m.theColumns;
                sum += element[ct] * m.element[cm];
            }
            
            w.element[cw++] = sum; 

            ct -= theColumns - 1;
            cm = j;
        }

        ct += theColumns;
        cm = 0;
    }

    return w;
}

#endif