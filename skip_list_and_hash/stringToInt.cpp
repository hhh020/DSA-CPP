// program 10-14
#include <string>
using std::string;

// 把s转换成一个非负整数，这样的转换依赖于s的所有字符
int stringToInt(string s)
{
    int length = s.length();
    int answer = 0;
    // 长度为奇数
    if (length % 2 == 1)
    {
        answer = s.at(length-1);
        length--;
    }

    // 同时转换两个字符
    for (int i = 0; i < length; i += 2)
    {
        answer += s.at(i);
        answer += ((int) s.at(i+1)) << 8;
    }
}