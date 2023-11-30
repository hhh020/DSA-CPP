// exercise 1.19-1.26
#include <iostream>

using std::cin;
using std::cout;

long factorial(int n)    // T1
{
    long result = 1;
    while (n > 0)
        result *= n--;
    return result;
}

long Fibonacci_rec(int n)   // T2 (1)
{
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return Fibonacci_rec(n-1) + Fibonacci_rec(n-2);
}

long Fibonacci_loop(int n)  // T2(3)
{
    if (n == 0) return 0;
    else if (n == 1) return 1;

    int prev = 0, curr = 1, next;   // previous/currency/next
    for (int i = 2; i <= n; i++)
    {
        next = prev + curr;
        prev = curr;
        curr = next;
    }
    return next;
}

int formula4_rec(int n)    // T3(3)
{
    if (n % 2 == 0)
        return n / 2;
    else
        return formula4_rec(3 * n + 1);
}

int formula4_nrec(int n)    // T3(4)
{
    if (n % 2 == 0)
        return n / 2;
    else 
        return (3 * n + 1) / 2;
}

int Ackermann(int i, int j)        // T4(3)
{
    if (i == 1 && j >= 1)
        return 1 << j;
    else if (i >= 2 && j == 1)
        return Ackermann(i-1,2);
    else 
        return Ackermann(i-1,Ackermann(i,j-1));
}

int gcd(int x, int y)       // T5(3)
{
    if (y == 0)
        return x;
    else 
        return gcd(y, x % y);
}

template<typename T>
bool find(T a[], int l, int r, T key)   // T6
{
    if (l == r)
        return key == a[l];
    else
        return find(a,l,l,key) || find(a,l+1,r,key);
}

void subset_generation(int a[], int i, int n)   // T7
{
    if (i == n)                         // 输出a[1:n]
    {
        for (int j = 1; j <= n; j++)
            cout << a[j];
        cout << '\n';
    }
    else if (i < n)                     // a[i]为0表示不包含,为1表示包含
    {
        a[i+1] = 0;
        subset_generation(a,i+1,n);
        a[i+1] = 1;
        subset_generation(a,i+1,n);
    }
    return;
}

void GraySequence(int n)
{
    if (n == 1)
        cout << 1 << ',';
    else
    {
        GraySequence(n-1);
        cout << n << ',';
        GraySequence(n-1);
    }
}


void test1()    // 计算n的阶乘，当 n <= 0 时程序测试终止
{
    int n;
    while (cin >> n && n > 0)
        cout << factorial(n) << '\n';
}

void test2()    // 使用递归或循环计算斐波那契数Fn，当 n < 0 时测试终止
{
    cout << "choose recursive(0) or loop(1)\n";
    int i,n;
    cin >> i;

    if (i == 0)
    {
        while (cin >> n && n >= 0)
            cout << Fibonacci_rec(n) << '\n';
    }
    else
    {
        while (cin >> n && n >= 0)
            cout << Fibonacci_loop(n) << '\n';
    }
}

void test3()    // 使用递归或非递归计算公式1-4, 当 n <= 0 时测试终止
{
    cout << "choose recursive(0) or norecursive(1)\n";
    int i,n;
    cin >> i;

    if (i == 0)
    {
        while (cin >> n && n > 0)
            cout << formula4_rec(n) << '\n';
    }
    else
    {
        while (cin >> n && n > 0)
            cout << formula4_nrec(n) << '\n';
    }
}

void test4()    // 使用递归计算阿克曼函数, 当 i 或 j 不大于 0 时测试终止
{
    int i,j;
    while (cin >> i >> j && i > 0 && j > 0)
        cout << Ackermann(i,j) << '\n';
}

void test5()    // 使用递归计算最大公约数, 当 x 或 y 小于 0 时测试终止
{
    int x,y;
    while (cin >> x >> y && x >= 0 && y >= 0)
        cout << gcd(x,y) << '\n';
}

void test6()    // 使用递归查找数组中的元素
{
    auto a = new int[5]{1,2,3,4,5};
    cout << find(a,0,4,3) << '\n';
    cout << find(a,0,4,1) << '\n';
    cout << find(a,0,4,5) << '\n';
    cout << find(a,0,4,6) << '\n';
}

void test7()    // 测试子集生成器S
{
    int a[3];
    subset_generation(a,0,3);
    int b[4];
    subset_generation(b,0,4);
}

void test8()    // 使用递归计算格雷码位置序列, 当 n <= 0 时测试终止
{
    int n;
    while (cin >> n && n > 0)
    {
        cout << "Gray Code position sequence is:";
        GraySequence(n);
        cout << '\n';
    }
}


int main()
{
    int i;
    cout << "choose the test program:\n";
    cin >> i;
    switch (i)
    {
    case 1:
        test1();
        break;
    case 2:
        test2();
        break;
    case 3:
        test3();
        break;
    case 4:
        test4();
        break;
    case 5:
        test5();
        break;
    case 6:
        test6();
        break;
    case 7:
        test7();
        break;
    case 8:
        test8();
        break;
    default:
        break;
    }
    return 0;
}