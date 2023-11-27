// program 1-25
#ifndef currency_
#define currency_

#include "../illegalParameterValue/illegalParameterValue.h"
#include <ostream>

using std::ostream;

enum signType{plus, minus};

class currency
{
    // 现在大部分声明在public内
    friend ostream& operator<<(ostream&, const currency&);  

public:
    currency(signType theSign = plus,
             unsigned long theDollars = 0,
             unsigned int theCents = 0);
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
    currency operator+(const currency&) const;
    currency& operator+=(const currency& x)
        {amount += x.amount; return *this;}

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

// overload <<
ostream& operator<<(ostream& out, const currency& x)
{
    long theAmount = x.amount;
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
    return out;
}

#endif