# exercise 1.15~1.18

## 1.15

1) max: 4294967295.99 (2的32次方-1 + 0.99) min: -4294967295.99 
2) max: 2147483647.99 (2的31次方-1 + 0.99) min: -2147483647.99
3) 这里假设long占四个字节, 则a1,a2不超过2147483647

## 1.16

```c++
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

    a1 = dollars * 100 + cents;
    if (sign == minus) a1 = -a1;    
    
    a2 = a1 / x;
    if (a2 < 0) {result.sign = minus; a2 = -a2;}
    else result.sign = plus;
    result.dollars = (unsigned long) (a2 / 100);
    result.cents = (unsigned int) (a2 - result.dollars * 100);

    return result;
}
```

## 1.17

```c++
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
```

## 1.18


(1)
```c++
istream& operator>>(istream& in, currency& x)
{
    double amount;
    in >> amount;
    x.amount = amount * 100;
    return in;
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
```

(2)

```c++
void currency::operator=(const int& x)
{
    amount = (long) (x * 100);
}

void currency::operator=(const double& theAmount)
{
    if (theAmount < 0)
        amount = (long) ((theAmount - 0.001) * 100);
    else
        amount = (long) ((theAmount + 0.001) * 100);
}
```

