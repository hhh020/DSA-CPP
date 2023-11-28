// program 1-32
#include <algorithm>
#include <iostream>
#include <iterator>

using std::copy;
using std::swap;
using std::ostream_iterator;
using std::cout;

/**
 * 递归生成全排列
 * 前缀:list[0:k-1],后缀:list[k:n-1]
*/
template<typename T>
void permutations(T list[], int k, int m)  
{
    if (k == m) // list[k:m] 仅有一个排列，输出它
    {
        copy(list,list+m+1,ostream_iterator<T>(cout, ""))
        cout << '\n';
    }
    else        // list[k:m] 有多于一个排列，递归地生成这些排列
    {
        for (int i = k; i <= m; i++)
        {
            swap(list[k],list[i]);      
            permutations(list,k+1,m);
            swap(list[k],list[i]);    
        }
    }
}