// program 2-10/2-14/2-15
// 把x插入有序数组a[0:n-1]
// 假设数组a的容量大于n
template<class T>
void insert(T a[], int& n, const T& x)
{
    int i;
    for (i = n-1; i >= 0 && x < a[i]; i--)
        a[i+1] = a[i];
    a[i+1] = x;
    //数组a多了一个元素
    //n++;
}

// 对数组a[0:n-1]实施插入排序
template<class T>
void insertionSort(T a[], int n)
{
    for (int i = 1; i < n; i++)
    {
        T t = a[i];
        insert(a, i, t);
    }
}

// 另一种插入排序
template<class T>
void insertionSort2(T a[], int n)
{
    for (int i = 1; i < n; i++)
    {
        T t = a[i];
        for (int j = i - 1; j >= 0 && t < a[j]; j--)
            a[j+1] = a[j];
        a[j+1] = t;
    }
}