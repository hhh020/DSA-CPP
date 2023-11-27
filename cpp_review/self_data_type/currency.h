// program 1-13~17
#ifndef currency_
#define currency_

#include <iostream>
#include "../illegalParameterValue/illegalParameterValue.h"

using std::cout;            // 存在std::plus,为防止命名冲突不能使用using namespace std

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

private:
    signType sign;          // 符号
    unsigned long dollars;  // 美元的数量
    unsigned int cents;     // 美分的数量
};

#endif