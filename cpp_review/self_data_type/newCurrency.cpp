// program 1-20/1-21
#include <iostream>
#include "newCurrency.h"

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
    cout << cents;
}