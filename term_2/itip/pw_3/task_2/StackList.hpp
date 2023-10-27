#ifndef STACK_LIST_HPP
#define STACK_LIST_HPP
#include "StackBase.hpp"

template <class T> struct Node {
    T data;
    Node *next;
};

template <class T> class StackList : public StackBase<T> {
    Node<T> *head;

  public:
    StackList();
    StackList(const StackList<T> &);
    void push(T) override;
    T pop() override;
    T peek() override;
    bool isEmpty() override;
    bool isFull() override;
    StackList<T> operator=(StackList<T> &ob);
    ~StackList();
};

template <class T> bool StackList<T>::isEmpty() {
    if (head->next == head)
        return true;
    return false;
}

template <class T> bool StackList<T>::isFull() {
    Node<T> *n;
    try {
        n = new Node<T>;
    } catch (bad_alloc &xa) {
        return true;
    }
    return false;
}

template <class T> StackList<T>::StackList() {
    cout << "StackList constructor" << endl;
    try {
        head = new Node<T>;
    } catch (bad_alloc &xa) {
        cerr << "Error while allocating memory. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
    head->next = head;
}

template <class T> StackList<T>::StackList(const StackList &ob) {
    head = ob.head;
}

template <class T> StackList<T> StackList<T>::operator=(StackList<T> &ob) {
    ob.head = head;
    return *this;
}

template <class T> void StackList<T>::push(T ob) {
    Node<T> *node;
    try {
        node = new Node<T>;
    } catch (bad_alloc &xa) {
        cerr << "Error while allocating memory. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
    node->data = ob;
    node->next = head;
    head = node;
}

template <class T> T StackList<T>::pop() {
    T ans = head->data;
    if (head->next == nullptr) {
        cout << "Stack is empty." << endl;
        head->data = 0;
    } else {
        Node<T> *tmp = head->next;
        delete head;
        head = tmp;
    }
    return ans;
}

template <class T> T StackList<T>::peek() { return head->data; }

template <class T> StackList<T>::~StackList() {
    Node<T> *tmp;
    for (tmp = head; tmp != nullptr; tmp = tmp->next)
        delete tmp;
}

#endif
