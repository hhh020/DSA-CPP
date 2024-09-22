// program 10-15
// 专业版hash<string>
#include <string>

namespace std {
    template<>
    class hash<string>
    {
    public:
        size_t operator() (const string theKey) const
        {
            unsigned long hashValue = 0;
            for (auto ch : theKey)
                hashValue = 5 * hashValue + ch;
            return size_t(hashValue);
        }
    };
}