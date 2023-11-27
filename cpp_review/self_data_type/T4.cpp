#ifndef currency_
#define currency_

#include "../illegalParameterValue/illegalParameterValue.h"
#include <iostream>

using std::ostream;
using std::istream;
using std::cin;
using std::cout;

enum signType{plus, minus};

class currency
{
    friend istream& operator>>(istream&, currency&);
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
    void operator=(const int&);
    void operator=(const double&);
    currency operator+(const currency&) const;
    currency& operator+=(const currency& x)
        {amount += x.amount; return *this;}
    currency operator-(const currency&) const;
    currency operator%(const double&) const;
    currency operator*(const double&) const;
    currency operator/(const double&) const;
    void output(ostream&) const;

private:
    long amount;
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

currency currency::operator+(const currency& x) const
{
    currency result;
    result.amount = amount + x.amount;
    return result;
}

void currency::output(ostream& out) const
{
    long theAmount = amount;
    if (theAmount < 0) 
    {
        out << '-'; 
        theAmount = -theAmount;
    }
    long dollars = theAmount / 100;
    out << '$' << dollars << '.';
    int cents = theAmount - dollars * 100;
    if (cents < 10) out << '0';
    out << cents;
}

// overload <<
ostream& operator<<(ostream& out, const currency& x)
{
    x.output(out); 
    return out;
}

// overload >>
istream& operator>>(istream& in, currency& x)
{
    double amount;
    in >> amount;
    x.amount = amount * 100;
    return in;
}

void currency::operator=(const int& theAmount)
{
    amount = (long) (theAmount * 100);
}

void currency::operator=(const double& theAmount)
{
    if (theAmount < 0)
        amount = (long) ((theAmount - 0.001) * 100);
    else
        amount = (long) ((theAmount + 0.001) * 100);
}
currency currency::operator-(const currency& x) const
{
    currency result;
    result.amount = amount - x.amount;
    return result;
}

currency currency::operator*(const double& x) const
{
    currency result;
    result.amount = (long) amount * x;
    return result;
}

currency currency::operator%(const double& x) const
{
    return (*this) * (x / 100);
}

currency currency::operator/(const double& x) const
{
    currency result;
    result.amount = (long) amount / x;
    return result;
}
#endif

int main()
{
    currency a,b;
    a.setValue(30);
    cin >> b;
    cout << b << '\n';
    cout << a - b << '\n';
    cout << a % 79 << '\n';
    cout << b * -2.5 << '\n';
    cout << b / -3 << '\n';
    b = 48;
    cout << b << '\n';
    b = -5.29;
    cout << b << '\n';
    return 0;
}