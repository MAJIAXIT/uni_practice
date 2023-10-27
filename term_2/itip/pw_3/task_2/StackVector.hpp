#ifndef STACK_VECTOR_HPP
#define STACK_VECTOR_HPP
#include "StackBase.hpp"

#define SIZE 100

template <class T> class StackVector : public StackBase<T> {
    T *stack;
    int topIdx;
    int size;

  public:
    StackVector();
    StackVector(int size);
    StackVector(const StackVector<T> &);
    void push(T) override;
    T pop() override;
    T peek() override;
    bool isEmpty() override;
    bool isFull() override;
    ~StackVector();
    StackVector<T> operator=(StackVector<T> &ob);
};

template <class T> bool StackVector<T>::isEmpty() {
    if (topIdx == 0)
        return true;
    return false;
}

template <class T> bool StackVector<T>::isFull() {
    if (topIdx == size)
        return true;
    return false;
}

template <class T> StackVector<T>::StackVector() {
    cout << "StackVector constructor" << endl;
    size = SIZE;
    topIdx = 0;
    try {
        stack = new T[size];
    } catch (bad_alloc &xa) {
        cerr << "Error, while allocating memory. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
}

template <class T> StackVector<T>::StackVector(int size) {
    cout << "StackVector constructor" << endl;
    try {
        stack = new T[size];
    } catch (bad_alloc &xa) {
        cerr << "Error, while allocating memory. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
    size = size;
    topIdx = 0;
}

template <class T> StackVector<T>::StackVector(const StackVector<T> &ob) {
    stack = ob.stack;
    size = ob.size;
    topIdx = ob.topIdx;
}

template <class T>
StackVector<T> StackVector<T>::operator=(StackVector<T> &ob) {
    ob.stack = stack;
    ob.size = size;
    ob.topIdx = topIdx;
    return *this;
}

template <class T> void StackVector<T>::push(T ob) {
    if (topIdx < size)
        stack[topIdx++] = ob;
    else
        cout << "Stack is full" << endl;
}

template <class T> T StackVector<T>::pop() {
    if (topIdx > 0)
        return stack[--topIdx];
    else {
        return 0;
    }
}

template <class T> T StackVector<T>::peek() { return stack[topIdx - 1]; }

template <class T> StackVector<T>::~StackVector() {
    delete[] stack;
    topIdx = 0;
}

#endif
