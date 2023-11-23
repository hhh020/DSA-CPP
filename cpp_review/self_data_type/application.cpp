// program 1-18
#include <iostream>
#include "currency.h"

using std::cout;

int main()
{
    currency g, h(plus, 3, 50), i, j;
    
    // Use two types of setValue to assign
    g.setValue(minus,2,25);
    i.setValue(-6.45);

    // Call member function add and output
    j = h.add(g);
    h.output();
    cout << " + ";
    g.output();
    cout << " = ";
    j.output();
    cout << '\n';

    // Call the member function add twice in a row
    j = i.add(g).add(h);
    
    // Call increment and add
    j = i.increment(g).add(h);

    cout << "Attempting to initialize with cents = 152" << '\n';
    try {i.setValue(plus,3,152);}
    catch (illegalParameterValue e)
    {
        cout << "Caught thrown exception" << '\n';
        e.outputMessage();
    }
    return 0;
}