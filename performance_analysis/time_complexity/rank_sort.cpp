// program 2-5/2-6/2-11
#include <algorithm>

using std::swap;

template<class T>
void rank(T a[], int n, int r[])
{
    for (int i = 0; i < n; i++)
        r[i] = 0;                   // 初始化

    // 比较所有元素对  
    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++)
            if (a[j] <= a[i]) r[i]++;
            else r[j]++;
}

template<class T>
void rearrange(T a[], int n, int r[])
{
    T *u = new T [n];       // 创建附加数组
    
    // 把a中的元素移动到u中正确位置
    for (int i = 0; i < n; i++)
        u[r[i]] = a[i];
    
    // 把u中元素移回a
    for (int i = 0; i < n; i++)
        a[i] = u[i];
    
    delete [] u;
}

// 原地重排数组元素使之有序
template<class T>
void rearrange_swap(T a[], int n, int r[])
{
    for (int i = 0; i < n; i++)
    {
        while (r[i] != i)
        {
            int t = r[i];
            swap(a[i],a[t]);
            swap(r[i],r[t]);
        }
    }
}