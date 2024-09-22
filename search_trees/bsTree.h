// program 14-1
// 抽象类bsTree

#ifndef __BSTREE_H__
#define __BSTREE_H__

#include "dictionary.h"

template<typename K, typename E>
class bsTree : public dictionary<K, E>
{
public:
    virtual void ascend() = 0;  // 按关键字升序输出
};

#endif