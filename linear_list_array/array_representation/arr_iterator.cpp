// program 5-9
#include <iostream>

using std::cout;

int main()
{
    int x[3] = {0, 1, 2};
    // 用指针y遍历数组x
    for (int *y = x; y != x + 3; y++)
        cout << *y << " ";
    cout << '\n';
    return 0;
}