// program 1-33/1-34
#include <numeric>      // 定义了accumulate
#include <functional>   // 定义了multiplies
#include <iostream>

using std::accumulate;
using std::multiplies;

template<typename T>
T sum(T a[], int n)
{
    T theSum = 0;
    return accumulate(a, a+n, theSum);
}

template<typename T>
T product(T a[], int n)     // 计算数组元素a[0:n-1]的乘积
{
    T theProduct = 1;
    return accumulate(a, a+n, theProduct, multiplies<T>());
}

int main()      // a simple test
{
    int a[]{1,2,3,4};
    std::cout << sum(a,4) << ' ' << product(a,4) << '\n';
    return 0;
}