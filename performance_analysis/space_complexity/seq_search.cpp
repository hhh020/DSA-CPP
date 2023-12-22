// program 2-1

/**
 * 在数组 a[0:n-1] 中查找元素x
 * 如果找到，则返回元素的位置，否则返回-1
*/
template<class T>
int sequentialSearch(T a[], int n, const T& x)
{
    int i;
    for (i = 0; i < n && a[i] != x; i++);
    if (i == n) return -1;
    else return i;
}