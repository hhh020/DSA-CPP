// exercise 2.7
#include <iostream>

using std::cout;

template<class T>
T factorial(T n)
{
    T result = n;
    while (--n) result *= n;
    return result;
}

int main()
{
    cout << factorial(5) << '\n';
    return 0;
}