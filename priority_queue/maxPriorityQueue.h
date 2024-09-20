// 程序12-1 抽象类maxPriorityQueue
#ifndef __MAX_PRIORITY_QUEUE_H__
#define __MAX_PRIORITY_QUEUE_H__

template<typename T>
class maxPriorityQueue
{
public:
    virtual ~maxPriorityQueue() {}
    virtual bool empty() const = 0;     // 当且仅当队列为空时返回true
    virtual int size() const = 0;       // 队列中元素个数
    virtual const T& top() = 0;         // 返回队列中优先级最高的元素的引用
    virtual void pop() = 0;             // 删除队列中优先级最高的元素（队首元素）
    virtual void push(const T& theElement) = 0; // 将元素插入队列中
};

#endif