#ifndef DSNODE_H
#define DSNODE_H

#include <iostream>
#include <cstring>
#include <DSString.h>
#include <DSVector.h>
#include <vector>

using namespace std;

template <class T>
class DSNode{
    template<class U> friend class DSLinkedList;
public:

    //default constructor (member initialization syntax)
    DSNode(): next(nullptr), prev(nullptr){}

    //constructor accepting value
    DSNode(const T& value): next(nullptr), prev(nullptr), data(value){}

    //copy constructor
    DSNode(const DSNode<T>& d2): next(nullptr), prev(nullptr), data(d2.data){}

    T& getData();

    void setData(T);

    DSNode<T> * getNext();

private:
    T data;
    DSNode<T>* next; //pointer to next node of type T
    DSNode<T>* prev; //pointer to prev node of type T

};

#endif // DSNODE_H
