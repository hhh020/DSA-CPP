// program 5-10
// 从 [start,end) 复制到 [to,to+end-start)
template<class iterator>
void copy(iterator start, iterator end, iterator to)
{
    while (start != end)
    {
        *to = *start;
        start++;
        to++;
    }
}