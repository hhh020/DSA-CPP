// program 2-3
// 计算n阶多项式在点x处的值，系数为coeff[0:n]
template<class T>
T polyEval(T coeff[], int n, const T& x)
{
    T y = 1, value = coeff[0];
    for (int i = 0; i <= n; i++)
    {
        y *= x;
        value += y * coeff[i];
    }
    return value;
}