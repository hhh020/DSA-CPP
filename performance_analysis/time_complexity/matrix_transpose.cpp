#include <algorithm>

using std::swap;

template<class T>
void transpose(T **a, int rows)
{
    for (int i = 0; i < rows; i++)
        for (int j = i + 1; j < rows; j++)
            swap(a[i][j], a[j][i]);
}