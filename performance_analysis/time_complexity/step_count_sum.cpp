// program 2-16/2-17/2-18
int stepCount1 = 0;
int stepCount2 = 0;
int stepCount3 = 0;

// 返回数值数组元素a[0:n-1]的和
template<class T>
T sum(T a[], int n)
{
    T theSum = 0;                // theSum = 0 是一个程序步  
    stepCount1++;
    for (int i = 0; i < n; i++)
    {
        stepCount1++;            // for循环的每一次条件判断是一个程序步
        theSum += a[i];
        stepCount1++;            // theSum += a[i] 是一个程序步
    }
    stepCount1++;                // for循环的最后一次条件判断是一个程序步
    stepCount1++;                // return theSum是一个程序步
    return theSum;
}

// 返回数值数组元素a[0:n-1]的和
template<class T>
T simple_sum(T a[], int n)
{
    for (int i = 0; i < n; i++)
        stepCount2 += 2;
    stepCount2 += 3;
    return 0;
}

// 返回数值数组元素a[0:n-1]的和
template<class T>
T rSum(T a[], int n)
{
    stepCount3++;               // if 语句是一个程序步
    if (n > 0)
    {
        stepCount3++;           // return 语句和调用语句是一个程序步
        return rSum(a, n-1) + a[n-1];
    }
    stepCount3++;               // return 语句是一个程序步
    return 0;
}