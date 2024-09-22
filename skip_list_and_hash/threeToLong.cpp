// program 10-13
// 把一个长度为3的字符串转换成一个长整型数
#include <string>
using std::string;

// 假设s.length() >= 3
long threeToLong(string s)
{
    long answer = s.at(0);
    answer = (answer << 8) + s.at(1);
    return (answer << 8) + s.at(2);
}