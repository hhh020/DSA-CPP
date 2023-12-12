// exercise 1.27-1.44
#include <iostream>
#include <functional>
#include <iterator>
#include <algorithm>
#include <numeric>

using std::ostream_iterator;
using std::cout;
using std::next_permutation;
using std::prev_permutation;
using std::sort;
using std::copy;
using std::equal;
using std::count;
using std::fill;
using std::inner_product;
using std::iota;
using std::is_sorted;
using std::mismatch;

// T1
template<typename T>                        
T accumulate(T* first, T* last, T init)
{
    for (; first != last; first++)
        init += *first;
    return init;
}

// T2
template<typename T, typename Operation>                
T accumulate(T* first, T* last, T init, Operation op)
{
    for(; first != last; first++)
        init = op(init, *first);
    return init;
}

/**
 * T3
 * 这里仅实现:
 * template< class InputIt, class OutputIt >
 * OutputIt copy( InputIt first, InputIt last, OutputIt d_first )
 * 说明: Copies the elements in the range, defined by [first, last)
 * 参见https://en.cppreference.com/w/cpp/algorithm/copy
*/
template< class InputIt, class OutputIt >
OutputIt mycopy(InputIt first, InputIt last, OutputIt d_first)
{
    OutputIt temp = d_first;
    for (; first != last; first++, d_first++)
        *d_first = *first;
    
    return temp;
}

// T4
template<typename T>                
void permutations(T list[], int m)
{
    sort(list, list+m);

    do {
        copy(list, list+m, std::ostream_iterator<T>(cout, ""));
        cout << '\n';
    } while (next_permutation(list, list+m));
}

// T5
template<typename T>
void permutations_2(T list[], int m)    
{
    auto list2 = new int[m];            // 创建副本
    copy(list, list+3, list2);

    do {
        copy(list, list+m, std::ostream_iterator<T>(cout, ""));
        cout << '\n';
    } while (next_permutation(list, list+m));

    while (prev_permutation(list2, list2+m))
    {
        copy(list2, list2+m, std::ostream_iterator<T>(cout, ""));
        cout << '\n';
    } 
}

// T6
template<typename T>
void permutations_3(T list[], int m)    
{
    auto list2 = new int[m];            // 创建副本
    copy(list, list+3, list2);

    do {
        copy(list, list+m, std::ostream_iterator<T>(cout, ""));
        cout << '\n';
    } while (next_permutation(list, list+m));
    

    while (!equal(list,list+m,list2)){  // stl的equal函数    
        copy(list, list+m, std::ostream_iterator<T>(cout, ""));
        cout << '\n';
        next_permutation(list, list+m);
    }
}

// T7
template<typename T>                    
int stl_count(T list[], int m, const T& value)
{
    return count(list, list+m, value);
}

// T8
template<typename T>
void stl_fill(T list[], int start, int end, const T& value)
{
    fill(list+start, list+end, value);
}

// T9
template<typename T>
int stl_inner_product(T list1[], int m, T list2[], const T& iv)
{
    return inner_product(list1, list1+m, list2, iv);
}

// T10
template<typename T>
void stl_iota(T list[], int m, const T& value)
{
    iota(list, list+m, value);
}

// T11
template<typename T>
bool stl_is_sorted(T list[], int m)
{
    return is_sorted(list, list+m);
}

// T12
template<typename T>
int stl_mismatch(T list1[], T list2[], int m)
{
    return (mismatch(list1, list1+m, list2).first) - list1; // 返回下标
}

void test1()
{
    int a[]{0,1,2,3,4,5,6};
    double b[]{2.1,3.2,3.4,5.6,2.7};
    cout << "the result is: " << accumulate(a,a+7,0) << '\n';
    cout << "the result is: " << accumulate(b,b+5,0.0) << '\n';
}

void test2()
{
    int a[]{1,2,3,4,5,6,7};
    cout << "the result(sum) is: " 
         << accumulate(a,a+7,0,std::plus<>()) << '\n';

    cout << "the result(multiplies) is: " 
         << accumulate(a,a+7,1,std::multiplies<>()) << '\n'; 
}

void test3()
{
    auto a = new int[5]{4,3,2,1,5};
    auto b = new int[5]();
    mycopy(a,a+5,b);
    for (int i = 0; i < 5; i++)
        cout << b[i] << ' ';
    cout << '\n';
}

void test4()
{
    auto a = new int[3]{3,2,1};
    permutations(a,3);
}

void test5()
{
    auto a = new int[3]{2,1,3};
    permutations_2(a,3);
}

void test6()
{
    auto a = new int[3]{2,1,3};
    permutations_3(a,3);
}

void test7()
{
    int a[] = {0,1,2,3,4,5,4,4};
    double b[] = {1.0,3.0,4.0,1.5,3.4,1.5};
    cout << "数组a中值为4的个数为: " << stl_count(a,8,4) << '\n';
    cout << "数组b中值为1.5的个数为: " << stl_count(b,6,1.5) << '\n';
}

void test8()
{
    int a[10] = {0};
    stl_fill(a,2,5,2);      // 对下标为2~4的元素赋值为2
    for (auto &e : a)
        cout << e << ' ';
    cout << '\n';
}

void test9()
{
    int a[5] = {2,4,6,8,0};
    int b[5] = {1,2,3,4,5};
    cout << stl_inner_product(a,5,b,0) << '\n';
}

void test10()
{
    auto a = new double[10];
    auto value{5.3};
    stl_iota(a,10,value);           // 从5.3开始产生连续的值
    for (int i = 0; i < 10; i++)
        cout << a[i] << '\n';
}

void test11()
{
    int a[]{0,1,2,3,4,5,6};
    int b[]{1,2,3,4,3,2,1};
    int c[]{1,0};
    int d[]{6,5,4,3,2,1,0};
    cout << stl_is_sorted(a,7) << '\n';
    cout << stl_is_sorted(b,7) << '\n';
    cout << stl_is_sorted(c,0) << '\n';
    cout << stl_is_sorted(d,7) << '\n';
}

void test12()
{
    int a[]{0,1,2,3,4,5,6,7};
    int b[]{0,1,2,4,5,6,7,8};
    int c[]{0,1,2,3,4,5,7,7};

    cout << stl_mismatch(a,b,8) << '\n';
    cout << stl_mismatch(a,c,8) << '\n';
}

// 练习 1.39-1.44 参考 https://en.cppreference.com/w/

int main()
{
    int i;
    cout << "input the test programm: " << '\n';
    std::cin >> i;
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
    case 10:
        test10();
        break;
    case 11:
        test11();
        break;
    case 12:
        test12();
        break;
    default:
        break;
    }

    return 0;
}

