/* program 6-17 */

#include "./studentRecord.h"
#include "../singly_linked_list/chain.h"

// sort by score
void binSort(chain<studentRecord>& theChain, int range)
{
    // Initialize bins
    chain<studentRecord> *bin;
    bin = new chain<studentRecord> [range + 1];

    // 把学生记录从链表中取出，然后分配到箱子里
    int numberOfElements = theChain.size();
    for (int i = 1; i <= numberOfElements; i++)
    {
        studentRecord x = theChain.get(0);
        theChain.erase(0);
        bin[x.score].insert(0,x);
    }

    // 从箱子中收集元素
    for (int j = range; j >= 0; j--)
        while (!bin[j].empty())
        {
            studentRecord x = bin[j].get(0);
            bin[j].erase(0);
            theChain.insert(0,x);
        }
    
    delete [] bin;
}