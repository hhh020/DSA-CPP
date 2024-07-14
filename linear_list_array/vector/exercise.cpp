#include "exercise_vectorList.h"
#include <iostream>

using std::cout;

void test37()
{
    auto a = new vectorList<int>();
    for (int i = 0; i <= 9; i++)   a[i] = i;
    cout << (*a);
    a->half();
    cout << (*a);
}

int main()
{
    test37();
    return 0;
}