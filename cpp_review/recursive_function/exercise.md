# exercise 1.19-1.26

## 1.19

```c++
long factorial(int n)    // T1
{
    long result = 1;
    while (n > 0)
        result *= n--;
    return result;
}
```

## 1.20

1) 

```c++
long Fibonacci_rec(int n)   // T2 (1)
{
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return Fibonacci_rec(n-1) + Fibonacci_rec(n-2);
}
```
2) 基础部分: n = 3 时, $F_3$ = $F_2$ + $F_1$ = $F_1$ + $F_0$ + $F_1$ 计算次数多于一次.
   
   归纳部分: 假设$F_{n}$计算次数大于一次，则$F_{n+1}$ = $F_{n}$ + $F_{n-1}$, 计算次数大于$F_{n}$的计算次数, 故$F_{n+1}$的计算次数也大于一次.

   综上所述，对于(1)中的代码，n > 2 时计算次数大于1次.

3) 

```c++
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
```

## 1.21

1) f(5) = f(16) = 8 = 4 = 2 = 1

   f(7) = f(22) = 11

2) 基础部分: n 为偶数时 f(n) = n / 2.
   
   递归部分: n 为奇数时 f(n) = f(3n+1). 因为 n 为偶数时, f(3n+1)是偶数
            所以可以转化为基础部分.

3) 

```c++
int formula4_rec(int n)    // T3(3)
{
    if (n % 2 == 0)
        return n / 2;
    else
        return formula4_rec(3 * n + 1);
}
```

4) 

```c++
int formula4_nrec(int n)    // T3(4)
{
    if (n % 2 == 0)
        return n / 2;
    else 
        return (3 * n + 1) / 2;
}
```

## 1.22

1) A(1,2) = $2^2$ = 4

   A(2,1) = A(1,2) = 4

   A(2,2) = A(1,A(2,1)) = A(1,4) = $2^4$ = 16

2) 基础部分: i = 1, j >= 1, A(i,j) = $2^j$
   
   递归部分: i >= 2 and j = 1, A(i,j) = A(i-1,2)
            i,j >= 2, A(i,j) = A(i-1,A(i,j-1))

3) 

```c++
int Ackermann(int i, int j)        // T4(3)
{
    if (i == 1 && j >= 1)
        return 1 << j;
    else if (i >= 2 && j == 1)
        return Ackermann(i-1,2);
    else 
        return Ackermann(i-1,Ackermann(i,j-1));
}
```

## 1.23

1) gcd(20,30) = gcd(20,10) = gcd(10,0) = 10

   gcd(112,42) = gcd(42,28) = gcd(28,14) = gcd(14,0) = 14

2) 基础部分: y = 0, gcd(x,0) = x;

   递归部分: y > 0, gcd(x,y) = gcd(y,x mod y)

   若 x mod y = 0 即 gcd(x,y) = gcd(y,0) = y, xy的最大公约数是y.

   若 x mod y != 0 则反复应用递归部分，直到找到一个整除xy的至少为1的数，这个数一定存在，这是因为 x mod 1 = y mod 1 = 0, 即gcd(x,1) = gcd (1,0) = 0.
   
3) 

```c++
int gcd(int x, int y)       // T5(3)
{
    if (y == 0)
        return x;
    else 
        return gcd(y, x % y);
}
```

## 1.24 

```c++
template<typename T>
bool find(T a[], int l, int r, T key)
{
    if (l == r)
        return key == a[l];
    else
        return find(a,l,l,key) || find(a,l+1,r,key);
}
```

## 1.25

```c++
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
```

## 1.26

1) g(4) = g(3),4,g(3) = g(2),3,g(2),4,g(2),3,g(2)
        = g(1),2,g(1),3,g(1),2,g(1),4,g(1),2,g(1),3,g(1),2,g(1)
        = 1,2,1,3,1,2,1,4,1,2,1,3,1,2,1

2) 基础部分: n = 1, g(1) = 1

   递归部分: n > 1, g(n) = g(n-1),n,g(n-1) 

   假设g(n)反复应用递归部分可以转化为基础部分, 则g(n+1) = **g(n)** ,n+1, **g(n)** 可以转化为基础部分

3) 