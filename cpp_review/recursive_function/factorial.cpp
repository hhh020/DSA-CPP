// program 1-29 
int factorial(int n)    // 计算n的阶乘
{
    if (n <= 1) return 1;
    else return n * factorial(n - 1);
}