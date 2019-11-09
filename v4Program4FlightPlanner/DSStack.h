#ifndef STACK
#define STACK

#include "DSLinkedList.h"

template<class T>
class DSStack
{
public:
    void push(T);
    T pop();
    T peek();

    T get(int);
    int size();
    bool contains(const T&);
    bool isEmpty();


private:
    DSLinkedList<T> data;
};


//pushes element to top
template<class T>
void DSStack<T>::push(T element) {
    data.insert(element);
}

//returns element at top of stack
template<class T>
T DSStack<T>::peek() {
    return data[(data.size()-1)];
}

//removes element from top of stack
template<class T>
T DSStack<T>::pop() {
    return data.removeBack();
}

//returns element at specific index of stack
template<class T>
T DSStack<T>::get(int index) {
    return data.get(index);
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

//checks to see if stack is empty
template<class T>
bool DSStack<T>::isEmpty() {
    if (data.size() == 0) {
        return true;
    }
    return false;
}

#endif
