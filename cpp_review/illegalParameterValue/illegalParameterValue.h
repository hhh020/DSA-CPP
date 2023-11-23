// program 1-26
#include <string>
#include <iostream>

#ifndef _illegalPV_H
#define _illegalPV_H

class illegalParameterValue
{
public:
    illegalParameterValue(): message("Illegal parameter value") {}
    illegalParameterValue(char *theMessage) {message = theMessage;}
    void outputMessage() {std::cout << message << '\n';}
private:
    std::string message;
};

#endif