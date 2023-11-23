#include "../illegalParameterValue/illegalParameterValue.h"

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

private:
    long amount;
};

