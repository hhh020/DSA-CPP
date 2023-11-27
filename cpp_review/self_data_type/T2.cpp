// exercise 1.15-1.18
#ifndef currency_
#define currency_

#include <iostream>
#include "../illegalParameterValue/illegalParameterValue.h"

using std::cout; 
using std::cin;
using std::istream;           

enum signType{plus, minus};

class currency 
{
public:
    // 构造函数
    currency(signType theSign = plus,
             unsigned long theDollars = 0,
             unsigned int theCents = 0);
    // 析构函数
    ~currency() {}
    void setValue(signType, unsigned long, unsigned int);
    void setValue(double);
    signType getSign() const {return sign;}
    unsigned long getDollars() const {return dollars;}
    unsigned int getCents() const {return cents;}
    currency add(const currency&) const;
    currency& increment(const currency&);
    void output() const;
    void input();
    currency subtract(const currency&) const;
    currency percent(const double) const;
    currency multiply(const double) const;
    currency divide(const double) const;

private:
    signType sign;          // 符号
    unsigned long dollars;  // 美元的数量
    unsigned int cents;     // 美分的数量
};

currency::currency(signType theSign, unsigned long theDollars, 
                   unsigned int theCents)
{
    setValue(theSign, theDollars, theCents);
}

void currency::setValue(signType theSign, unsigned long theDollars,
                        unsigned int theCents)
{
    if (theCents > 99)
        throw illegalParameterValue("Cents should be < 100");
    
    sign = theSign;
    dollars = theDollars;
    cents = theCents;
}

void currency::setValue(double theAmout)
{
    if (theAmout < 0) {sign = minus; theAmout = -theAmout;}
    else sign = plus;

    dollars = (unsigned long) theAmout;                             // 提取整数部分
    cents = (unsigned int) ((theAmout + 0.001 - dollars) * 100);    // 提取两位小数
}

currency currency::add(const currency& x) const         // 把x和*this相加
{
    long a1, a2, a3;
    currency result;

    // 把调用对象转化为符号整数
    a1 = dollars * 100 + cents;
    if (sign == minus) a1 = -a1;

    // 把x转化为符号整数
    a2 = x.dollars * 100 + x.cents;
    if (x.sign == minus) a2 = -a2;

    a3 = a1 + a2;

    // 转换为currency对象的表达形式
    if (a3 < 0) {result.sign = minus; a3 = -a3;}
    else result.sign = plus;
    result.dollars = a3 / 100;
    result.cents = a3 - result.dollars * 100;

    return result;
}

currency& currency::increment(const currency& x)    // 增加x
{
    *this = add(x);
    return *this;
}

void currency::output() const
{
    if (sign == minus) cout << '-';
    cout << '$' << dollars << '.';
    if (cents < 10) cout << '0';
    cout << cents << '\n';
}

void currency::input()
{
    cout << "please input the amout\n";
    double theAmout;
    cin >> theAmout;
    setValue(theAmout);
}

currency currency::subtract(const currency& x) const
{
    currency y(x);
    (y.getSign() == minus) ? y.sign = plus : y.sign = minus;
    return add(y);
}

currency currency::percent(const double x) const
{
    currency result;
    double a1,a2;
    a1 = dollars * 100 + cents;
    if (sign == minus) a1 = -a1;

    a2 = a1 * (x / 100);
    if (a2 < 0) {result.sign = minus; a2 = -a2;}
    else result.sign = plus;
    result.dollars = (unsigned long) (a2 / 100);
    result.cents = (unsigned int) (a2 - result.dollars * 100);
    return result;
}

currency currency::multiply(const double x) const
{
    currency result;
    double a1,a2;

    // 把调用对象转化为符号整数
    a1 = dollars * 100 + cents;
    if (sign == minus) a1 = -a1;    
    
    a2 = a1 * x;
    if (a2 < 0) {result.sign = minus; a2 = -a2;}
    else result.sign = plus;
    result.dollars = (unsigned long) (a2 / 100);
    result.cents = (unsigned int) (a2 - result.dollars * 100);

    return result;
}

currency currency::divide(const double x) const
{
    currency result;
    double a1,a2;

    // 把调用对象转化为符号整数
    a1 = dollars * 100 + cents;
    if (sign == minus) a1 = -a1;    
    
    a2 = a1 / x;
    if (a2 < 0) {result.sign = minus; a2 = -a2;}
    else result.sign = plus;
    result.dollars = (unsigned long) (a2 / 100);
    result.cents = (unsigned int) (a2 - result.dollars * 100);

    return result;
}
#endif

int main()
{
    currency a,b;
    a.setValue(30);
    b.input();
    b.output();
    a.subtract(b).output();
    a.percent(79).output();
    b.multiply(-2.5).output();
    b.divide(-3).output();
    return 0;
}
