// 异常
#ifndef __PRIORITY_QUEUE_EXCEPTION__
#define __PRIORITY_QUEUE_EXCEPTION__

#include <exception>
#include <iostream>
#include <string>

class queueEmpty : public std::exception {
public:
    queueEmpty() {
        std::cout << "heap is empty" << std::endl;
    }
};

#endif