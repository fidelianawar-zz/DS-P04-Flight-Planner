#ifndef DSLINKEDLIST_H
#define DSLINKEDLIST_H

#include <iostream>
#include <cstring>
#include <DSString.h>
#include <DSVector.h>
#include <vector>

using namespace std;

template <typename T>
class DSLinkedList{
private:
    T* elements;
    int vectorSize;
    int capacity;
}

#endif // DSLINKEDLIST_H
