#ifndef STACK
#define STACK

#include "DSLinkedList.h"

template<class T>
class DSStack
{
public:

    int size();

    bool contains(const T&);
    T get(int);
    bool isEmpty();

    void push(T);
    T pop();
    T peek();

private:
    DSLinkedList<T> data;
};

//removes element from top of the stack
template<class T>
T DSStack<T>::pop() {
    return data.removeFromBack();
}

//returns element at the top of the stack
template<class T>
T DSStack<T>::peek() {
    return data[(data.size()-1)];
}

//adds element at the top of the stack
template<class T>
void DSStack<T>::push(T element) {
    data.add(element);
}

//checks to see if there are any elements in stack
template<class T>
bool DSStack<T>::isEmpty() {
    if (data.size() == 0) {
        return true;
    }
    return false;
}

//returns number of elements in stack
template<class T>
int DSStack<T>::size() {
    return data.size();
}

//checks to see if element exists in stack
template<class T>
bool DSStack<T>::contains(const T& element) {
    return data.contains(element);
}

//returns element in stack at a specified index
template<class T>
T DSStack<T>::get(int index) {
    return data.get(index);
}

#endif
