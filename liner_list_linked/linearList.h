// copy from program 5-1
#ifndef __LinearList__
#define __LinearList__

#include <ostream>

using std::ostream;

template<class T>
class LinearList
{
public:
    virtual ~LinearList() {};
    virtual bool empty() const = 0;
                // 返回 true，当且仅当线性表为空
    virtual int size() const = 0;
                // 返回线性表元素个数
    virtual T& get(int theIndex) const = 0;
                // 返回索引为 theIndex 的元素
    virtual int indexOf(const T& theElement) const = 0;
                // 返回元素 theElement 第一次出现时的索引
    virtual void erase(int theIndex) = 0;
                // 删除索引为 theIndex 的元素
    virtual void insert(int theIndex, const T& theElement) = 0;
                // 把 theElement 插入线性表中索引为 theIndex 的位置上
    virtual void output(ostream& out) const = 0;
                // 把线性表插入输出流 out
};

#endif