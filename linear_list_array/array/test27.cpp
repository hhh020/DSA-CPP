#include "exercise_iterator.h"
#include "exercise_array_list.h"
#include "../../myexcption.h"

#include <algorithm>
#include <iostream>

using std::find;
using std::min;
using std::max;
using std::copy;
using std::copy_backward;
using std::ostream_iterator;
using std::cout;
using std::cerr;
using std::sort;

// 重载 <<
template<class T>
ostream& operator<<(ostream &out, const arrayList<T>& x)
{
    x.output(out);
    return out;
}

void test27()
{
    auto a = new arrayList<int>(10);
    int len;
    cout << "请输入线性表长度: ";
    std::cin >> len;

    for (int i = 0; i < len; i++)
        a->insert(i,9-i);
    cout << "a: " << (*a) << '\n';
    
    cout << "排序后a: " << (*a) << '\n';
    
    delete a;
}

int main()
{
    test27();
    return 0;
}