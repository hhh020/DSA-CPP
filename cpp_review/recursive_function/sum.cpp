// program 1-30/1-31
template<typename T>
T sum(T a[], int n)         // 循环累加
{
    T theSum = 0;
    for (int i = 0; i < n; i++)
        theSum += a[i];
    return theSum;
}

template<typename T>
T rSum(T a[], int n)        // 递归累加
{
    if (n > 0)
        return rSum(a, n-1) + a[n-1];
    return 0;
}
