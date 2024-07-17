/* program 6-14 ~ 6-16 */
#ifndef __STUDENT_RECORD__
#define __STUDENT_RECORD__

#include <string>
#include <ostream>

/*
struct studentRecord
{
    int score;
    std::string* name;
    int operator!=(const studentRecord& x) const {
        return (score != x.score);
    }
};
*/

/*
struct studentRecord
{
    int score;
    std::string* name;
    
    // 从studentRecord到int的类型转换
    operator int() const {return score;}
};
*/

struct studentRecord
{
    int score;
    std::string* name;
    
    int operator!=(const studentRecord& x) const {
        return (score != x.score);
    }
    operator int() const {return score;}
};

std::ostream& operator<<(std::ostream& out, const studentRecord& x)
{
    out << x.score << ' ' << *x.name << '\n';
    return out;
}

#endif