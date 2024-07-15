/* program 6-11 */
#ifndef __EXTENDED_LINEAR_LIST__
#define __EXTENDED_LINEAR_LIST__

#include "../linearList.h"

template<class T>
class extendedLinearList : linearList<T>
{
    public:
        virtual ~extendedLinearList() {}
        virtual void clear() = 0;
        virtual void push_back(const T& theElement) = 0;
};

#endif