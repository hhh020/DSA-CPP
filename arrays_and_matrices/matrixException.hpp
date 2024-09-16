#ifndef __MATRIX_EXCEPTION__
#define __MATRIX_EXCEPTION__

#include <exception>
#include <iostream>
#include <string>

class matrixIndexOutofBounds : public std::exception {
public:
    matrixIndexOutofBounds(const std::string& message) : message_(message) {}

    const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

class matrixSizeMismatch : public std::exception {
public:
    matrixSizeMismatch(const std::string& message) : message_(message) {}

    const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

#endif