// program 1-37
#include "../illegalParameterValue/illegalParameterValue.h"

// 查找数组a[0:n-1]的最大元素
template<class T>
int indexOfMax(T a[], int n)
{
    if (n <= 0)
        throw illegalParameterValue("n must be > 0");
    
    int indexOfMax = 0;
    for (int i = 1; i < n; i++)
        if (a[indexOfMax] < a[i])
            indexOfMax = i;
    return indexOfMax;
}