// program 1-24
#include <ostream>
#include "currencyOverload.h"

using std::cout;

int main()
{
    currency g, h(plus, 3, 50), i, j;
    
    // Use two types of setValue to assign
    g.setValue(minus,2,25);
    i.setValue(-6.45);

    // Call member function add and output
    j = h + g;
    cout << h << " + " << g << " = " << '\n';

    // Call the member function add twice in a row
    j = i + g + h;
    cout << i << " + " << g << " + " << h << " = " << j << '\n';

    // Call increment and add
    cout << "Increment " << i << " by " << g << "and then add " << h << '\n';
    j = (i += g) + h;
    cout << "Result is " << j << '\n';
    cout << "Incremented object is " << i << '\n';

    cout << "Attempting to initialize with cents = 152" << '\n';
    try {i.setValue(plus,3,152);}
    catch (illegalParameterValue e)
    {
        cout << "Caught thrown exception" << '\n';
        e.outputMessage();
    }
    return 0;
}