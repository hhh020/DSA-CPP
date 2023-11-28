// exercise 1.17
#include "../illegalParameterValue/illegalParameterValue.h"
#include <iostream>

using std::cout;
using std::cin;

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
    signType getSign() const 
        {return (amount < 0) ? minus : plus;}
    unsigned long getDollars() const 
        {return (amount < 0) ? (-amount) / 100 : amount / 100;}
    unsigned int getCents() const 
        {return (amount < 0) ? -amount - getDollars() * 100 
                               : amount - getDollars() * 100;}
    currency add(const currency&) const;
    currency& increment(const currency& x)
        {amount += x.amount; return *this;}
    void output() const;
    void input();
    currency subtract(const currency&) const;
    currency percent(const double) const;
    currency multiply(const double) const;
    currency divide(const double) const;

private:
    long amount;
};

void currency::input()
{
    cout << "please input the amout\n";
    double theAmout;
    cin >> theAmout;
    setValue(theAmout);
}

currency currency::subtract(const currency& x) const
{
    currency y;
    y.amount = amount - x.amount;
    return y;
}

currency currency::multiply(const double x) const
{
    currency result;
    result.amount = (long) amount * x;
    return result;
}

currency currency::percent(const double x) const
{
    return multiply(x/100);
}

currency currency::divide(const double x) const
{
    currency result;
    result.amount = (long) amount / x;
    return result;
}

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
    
    amount = theDollars * 100 + theCents;
    if (theCents == minus) amount = -amount;
}

void currency::setValue(double theAmount)
{
    if (theAmount < 0)
        amount = (long) ((theAmount - 0.001) * 100);
    else
        amount = (long) ((theAmount + 0.001) * 100);
}

currency currency::add(const currency& x) const
{
    currency y;
    y.amount = amount + x.amount;
    return y;
}

void currency::output() const
{
    long theAmount = amount;
    if (theAmount < 0)
    {
        cout << '-';
        theAmount = -theAmount;
    }
    long dollars = theAmount / 100;
    cout << '$' << dollars << '.';
    int cents = theAmount - dollars * 100;
    if (cents < 10) cout << '0';
    cout << cents << '\n';
}

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

