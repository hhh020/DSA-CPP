// program 2-4
// 利用 Horner 法则计算n阶多项式在点x处的值，系数为coeff[0:n]
template<class T>
T horner(T coeff[], int n, const T& x)
{
    T value = coeff[n];
    for (int i = 1; i <= n; i++)
        value = value * x + coeff[n -  i];
    return value;
}