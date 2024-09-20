// program 12-9 
// 基于a[1:n]台机器的LPT（最长处理时间）调度

#include "maxHeap.h"
#include "minHeap.h"
#include "heapSort.cpp"
#include <iostream>

using std::cout;

struct jobNode {
    int id;         // 作业唯一标识符
    int time;       // 作业处理时间

    operator int() const {return time;}
};

struct machineNode {
    int id;         // 机器编号
    int avail;      // 表示何时空闲

    machineNode(int i, int t) : id(i), avail(t) {}
    operator int() const {return avail;}
};

// 输出一个基于n个作业a[1:n]的m台机器的LPT调度
void makeSchedule(jobNode a[], int n, int m)
{
    if (n <= m)
    {
        cout << "Schedule each job on a different machine.\n";
        return;
    }

    heapSort(a, n);     // 按照递增顺序排序作业

    // 初始化m台机器，建立小根堆
    minHeap<machineNode> machineHeap(m);
    for (int i = 1; i <= m; i++)
        machineHeap.push(machineNode(i, 0));
    
    // 生成调度计划
    for (int i = n; i >= 1; i--)
    {
        machineNode x = machineHeap.top();
        machineHeap.pop();
        cout << "Schedule job " << a[i].id 
             << " on machine " << x.id << " from " << x.avail 
             << " to " << (x.avail + a[i].time) << "\n";
        x.avail += a[i].time;
        machineHeap.push(x);
    }
}
