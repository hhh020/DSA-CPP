#ifndef __myexcption__
#define __myexcption__

#include <exception>
#include <iostream>
#include <string>

class illegalIndex : public std::exception {
public:
    illegalIndex(const std::string& message) : message_(message) {}

    const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

#endif
