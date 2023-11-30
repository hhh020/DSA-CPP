#include <algorithm>    // 定义copy和next_permutation
#include <iostream>
#include <iterator>

using std::copy;
using std::next_permutation;
using std::ostream_iterator;
using std::cout;

/**
 * 原书有误, 见https://www.cise.ufl.edu/~sahni/dsaac/errata.htm
 * 生成list[0:m]的所有排列
 * 假设k <= m
 * 将排列逐个输出
*/
template<typename T>
void permutations(T list[], int m)
{
    do {
        copy(list, list+m+1, std::ostream_iterator<T>(cout, ""));
        cout << '\n';
    } while (next_permutation(list, list+m+1))
}