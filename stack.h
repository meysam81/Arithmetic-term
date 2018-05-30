#ifndef STACK_H
#define STACK_H
#include <vector>
using namespace std;
#include <iostream>
#include <iomanip>
template <class T>
class stack
{
private:
    vector<T> storage;
public:
    stack();
    unsigned int getSize();
    void push(T newItem);
    void pop();
    T top();
    bool isEmpty();
    friend ostream& operator << (ostream& output, const stack<T> item);
};
template <class T>
ostream& operator << (ostream& output, const stack<T> item);
#endif // STACK_H
