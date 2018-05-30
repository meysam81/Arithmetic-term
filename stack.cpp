#include "stack.h"

template <class T>
stack<T>::stack()
{
}

template <class T>
unsigned int stack<T>::getSize()
{
    return storage.size();
}

template <class T>
void stack<T>::push(T newItem)
{
    storage.push_back(newItem);
}

template <class T>
void stack<T>::pop()
{
    storage.pop_back();
}

template <class T>
T stack<T>::top()
{
    return *(storage.end() - 1);
}

template <class T>
bool stack<T>::isEmpty()
{
    return storage.size() == 0;
}
template <class T>
void stack<T>::printStack()
{
    for (unsigned int i = 0; i < storage.size(); i++)
        cout << storage[i] << setw(3);
    cout << endl;

}
