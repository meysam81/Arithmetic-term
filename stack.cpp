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
ostream &operator <<(ostream &output, const stack<T> item)
{
    for (unsigned int i = 0; i < item.storage.size(); i++)
        output << item.storage[i] << setw(3);
    output << endl;
    return output;
}
