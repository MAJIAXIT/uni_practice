#ifndef STACK_BASE_HPP
#define STACK_BASE_HPP

#include <cstring>
#include <iostream>
#include <limits>

using namespace std;

template <class T> class StackBase {
  public:
    virtual void push(T) = 0;
    virtual T pop() = 0;
    virtual T peek() = 0;
    virtual bool isEmpty() = 0;
    virtual bool isFull() = 0;
};

#endif