// program 1-36
#include <iostream>
#include <cmath>

using std::cout;

// 计算和输出二次方程的根
void outputRoots(const double& a, const double& b, const double& c)
{
    double d = b * b - 4 * a * c;
    if (d > 0)  // 两个实数根
    {
        double sqrtd = sqrt(d);
        cout << "There are two real roots "
             << (-b + sqrtd) / (2 * a) << " and "
             << (-b - sqrtd) / (2 * a) << '\n';
    }
    else if (d == 0)    // 两个根相同
        cout << "There is only one distinct root "
             << -b / (2 * a)
             << '\n';
    else    // 复数共轭根
        cout << "The roots are complex\n "
             << "The real part is "
             << -b / (2 * a) << '\n'
             << "The imaginary part is "
             << sqrt(-d) / (2 * a) << '\n';
}