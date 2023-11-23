// program 1-9
#include <iostream>
using namespace std;

int abc(int a, int b, int c)
{
    if (a <= 0 || b <= 0 || c <= 0)
        throw "All parameters should be > 0";
    return a + b * c;
}

int main()
{
    try {cout << abc(2,0,4) << endl;}
    catch (const char *e)               // diff: add "const"
    {
        cout << "The parameters to abc were 2,0, and 4" << endl;
        cout << "An exception has been thrown" << endl;
        cout << e << endl;
        return 1;
    }
    return 0;
}
