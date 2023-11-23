// exercise 1.10~1.11
#include <iostream>
using namespace std;

int abc(int a, int b, int c)        // T1 23/11/19
{
    if (a < 0 && b < 0 && c < 0)
        throw 1;
    if (a == 0 && b == 0 && c == 0)
        throw 2;
    return a + b * c;
}

template<typename T>                // T2: 23/11/19
size_t count(const T a[], int n, const T& value)
{
    if (n < 1)
        throw "n should no less than 1";
    size_t cnt{0};
    for (int i = 0; i < n; i++)
        if (a[i] == value)
            cnt++;

    return cnt;
}

void test1()
{
    int a,b,c;
    cin >> a >> b >> c;
    try {cout << abc(a,b,c) << endl;}
    catch (const int e)               
    {
        cout << "An exception has been thrown" << endl;
        if (e == 1)
        {
            cout << "The exception value is 1" << endl;
            cout << "a, b, and c cannot be less than 0 at the same time" << endl;
        }
        else
        {
            cout << "The exception value is 2" << endl;
            cout << "a, b, and c cannot be 0 at the same time" << endl;
        }
        exit(1);
    }
}

void test2()
{
    int a[] = {0,1,2,3,4,5,4,4};
    try { cout << "数组a中值为4的个数为: " << count(a,0,4) << '\n';}
    catch (const char *e)
    {
        cout << "An exception has been thrown" << endl;
        cout << e << endl;
        exit(1);
    }    
}

int main()
{
    int i;
    cin >> i;
    switch (i)
    {
    case 1:
        test1();
        break;
    case 2:
        test2();
        break;
    default:
        break;
    }
    
    return 0;
}