#include <iostream>
#include "currency.h"

using std::cout;

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
