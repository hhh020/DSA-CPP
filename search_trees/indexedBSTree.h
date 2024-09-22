// program 14-2 
// 抽象类 indexedBSTree

#ifndef __INDEXED_BSTREE_H__
#define __INDEXED_BSTREE_H__

#include "dictionary.h"

template<typename K, typename E>
class indexedBSTree : public Dictionary<K, E>
{
public:
    virtual pair<const K, E>* get(int) const = 0;
        // 根据给定的索引返回其数对的指针
    virtual void delete(int) = 0;
        // 根据给定的索引删除数对
};

#endif