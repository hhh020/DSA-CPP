// program 10-16
// hashTable
#include <utility>
#include <functional>
using std::pair;
using std::hash;

template<typename K, typename E>
class hashTable
{
public:
    hashTable(int theDivisor);
    int search(const K& theKey) const;
    pair<const K, E>* find(const K& theKey) const;
    void insert(const pair<const K, E>& thePair);

private:
// 散列表的数据成员
    pair<const K, E>** table;   // 散列表
    hash<K> hash;               // 把类型K映射到一个非整数
    int dSize;
    int divisor;
};

template<typename K, typename E>
hashTable<K,E>::hashTable(int theDivisor)
{
    divisor = theDivisor;
    dSize = 0;

    // 分配和初始化散列表
    table = new pair<const K, E>* {divisor};
    for (int i = 0; i < divisor; i++)
        table[i] = NULL;
}

// 搜索一个散列表，查找关键字为theKey的数对
// 如果匹配的数对存在，返回它的位置，否则如果散列表不满
// 则返回关键字为theKey的数对可以插入的位置
template<typename K, typename E>
int hashTable<K,E>::search(const K& theKey) const
{
    int i = (int) hash(theKey) % divisor;   // 起始桶
    int j = i;                      // 从起始桶开始
    do 
    {
        if (table[j] == NULL || table[j]->first == theKey)
            return j;
        j = (j + 1) % divisor;      // 下一个桶
    } while (j != i);               // 是否返回起始桶
}

// 返回匹配数对的指针
// 如果没有匹配的数对，则返回NULL
template<typename K, typename E>
pair<const K, E>* hashTable<K,E>::find(const K& theKey) const
{
    int b = search(theKey);
    if (table[b] == NULL || table[b]->first != theKey)
        return NULL;

    return table[b];
}

// 把数对thePair插入字典，若存在关键字相同的数对，则覆盖
// 若表满，则抛出异常
template<typename K, typename E>
void hashTable<K,E>::insert(const pair<const K, E>& thePair)
{
    // 搜索散列表查找匹配的数对
    int b = search(thePair.first);

    // 检查匹配的数对是否存在  
    if (table[b] == NULL)
    {
        table[b] = new pair<const K, E>(thePair);
        dSize++;
    }
    else if (table[b]->first == thePair.first)      // 有重复的关键字数对
        table[b]->second = thePair.second;
    else                                            // 表满
        throw hashTableFull();
}   