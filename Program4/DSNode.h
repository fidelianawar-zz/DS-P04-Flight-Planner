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
    //default
    DSNode(): next(nullptr), prev(nullptr){}
    //literal
    DSNode(T  value): next(nullptr), prev(nullptr), data(value){}
    //copy constructor
    DSNode(const DSNode<T>& d2): next(nullptr), prev(nullptr), data(d2.data){}
    ~DSNode();
    T& getData();
    void setData(T);
    DSNode<T> * getNext();
private:
    T data;
    DSNode* next;
    DSNode* prev;

};

#endif // DSNODE_H
