// program 10-1
#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include <utility>

using std::pair;

template<typename K, typename E>
class dictionary
{
public:
    virtual ~dictionary() {}
    virtual bool empty() const = 0;     // 当且仅当字典为空时返回true
    virtual int size() const = 0;       // 返回字典中数对的数目
    virtual pair<const K, E>* find(const K&) const = 0;
                                        // 返回匹配数对的指针
    virtual void erase(const K&) = 0;   // 删除匹配数对
    virtual void insert(const pair<const K, E>&) = 0;
                                        // 插入一个数对
};

#endif