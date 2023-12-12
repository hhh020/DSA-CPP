// exercise 1.1~1.9
#include <iostream>
#include <vector>

using std::cout;
using std::cin;

void swap(int& x,int& y)    // T1: 23/11/8
{
    int temp = x;
    x = y;
    y = temp;
}

template<typename T>        // T2: 23/11/9
size_t count(const T a[], int n, const T& value)
{
    size_t cnt{0};
    for (int i = 0; i < n; i++)
        if (a[i] == value)
            cnt++;

    return cnt;
}

template<typename T>        // T3: 23/11/9
void fill(T a[], int start, int end, const T& value)
{
    for(int i = start; i < end; i++)
        a[i] = value;
}

template<typename T>        // T4: 23/11/10
T inner_product(T a[], T b[], unsigned n)   
{
    T sum = 0;              
    for (int i = 0; i < n; i++)
        sum += a[i] * b[i];
    return sum;
}

template<typename T>        // T5: 23/11/12
void iota(T a[], unsigned n, T value)
{
    for (int i = 0; i < n; i++)
        a[i] = value + i;
}

template<typename T>        // T6: 23/11/11
bool is_sorted(T a[], unsigned n)
{
    if (n <= 2) return true;
    bool flag = true;   
    int i = 1;
    while (i < n && a[i] == a[i-1]) // 找到第一个不相等的相邻元素
        i++;

    if (a[i] > a[i-1])      // 判断是否递减
    {
        for (int j = i + 1; j < n; j++)
        {
            if (a[j] < a[j-1])
            {
                flag = false;
                break;
            }
            j++;
        }
    }
    else                    // 判断是否递增
    {
        for (int j = i + 1; j < n; j++) 
        {
            if (a[j] > a[j-1]) 
            {
                flag = false;
                break;
            }
            j++;
        }
    }
    return flag;
}

template<typename T>        // T7: 23/11/12
unsigned mismatch(unsigned n, T a[], T b[]) // 注意c++ stl中存在mismatch
{
    unsigned i = 0;
    while (i < n && a[i] == b[i])
        i++;
    return i;
}

void test1()
{
    int x{1},y{2};
    swap(x,y);
    std::cout << "x=" << x << ", y=" << y << '\n';
}

void test2()
{
    int a[] = {0,1,2,3,4,5,4,4};
    double b[] = {1.0,3.0,4.0,1.5,3.4,1.5};
    cout << "数组a中值为4的个数为: " << count(a,8,4) << '\n';
    cout << "数组b中值为1.5的个数为: " << count(b,6,1.5) << '\n';
}

void test3()
{
    int a[10] = {0};
    fill(a,2,5,2);      // 对下标为2~4的元素赋值为2
    for (auto &e : a)
        cout << e << ' ';
    cout << '\n';
}

void test4()
{
    int a[5] = {2,4,6,8,0};
    int b[5] = {1,2,3,4,5};
    cout << inner_product(a,b,5) << '\n';
}

void test5()
{
    auto a = new double[10];
    auto value{5.3};
    iota(a,10,value);
    for (int i = 0; i < 10; i++)
        cout << a[i] << '\n';
}

void test6()    // 这里给了几个例子，也可以改写成从终端输入的方式
{
    int a[]{0,1,2,3,4,5,6};
    int b[]{1,2,3,4,3,2,1};
    int c[]{1,0};
    int d[]{6,5,4,3,2,1,0};
    cout << is_sorted(a,7) << '\n';
    cout << is_sorted(b,7) << '\n';
    cout << is_sorted(c,0) << '\n';
    cout << is_sorted(d,7) << '\n';
}

void test7()
{
    int a[]{0,1,2,3,4,5,6,7};
    int b[]{0,1,2,4,5,6,7,8};
    int c[]{0,1,2,3,4,5,7,7};

    cout << mismatch(8,a,b) << '\n';    // 3
    cout << mismatch(8,a,c) << '\n';    // 6
}

void test8()    // T8 23/11/13
{
    cout << "no, cannot overload functions distinguished"
            "by return type alone\n";
}

void test9()    // T9 23/11/13
{
    cout << "3) because argument(signature) not match(int,int,float)\n";
    cout << "4) argument(signature) not match(double,double,double)\n";
}
int main()
{
    cout << "please choose the task from 1 to 9\n";
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
    case 9:
        test9();
        break;
    default:
        cout << "input error\n";
        break;
    }
    
    return 0;
}