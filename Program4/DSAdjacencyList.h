#ifndef DSADJACENCYLIST_H
#define DSADJACENCYLIST_H
#include <iostream>
#include "DSLinkedList.h"

using namespace std;

template <class T>
struct node{
    int data;
    struct node<T> *link;
};

#endif // DSADJACENCYLIST_H
