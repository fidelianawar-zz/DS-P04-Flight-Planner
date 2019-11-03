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


template <class T>
struct vertex{
    int data;
    struct node<T> *vertexHead;
};

template <class T>
struct AdjacencyList{
    int v;
    struct vertex<T> *vertexPointer;
};

template <class T>
struct AdjacencyList<T>* createAdjList(int x){
    int i;
    struct AdjacencyList<T> *vertexList = new AdjacencyList<T>;
    vertexList->v = i;

    vertexList->vertexPointer = new vertex<T>[i+1];
    for(int i = 0; i < x +1; i++){
        vertexList->vertexPointer[i].vertexHead = nullptr;
    }
    return vertexList;
};

template <class T>
struct node<T>* newNode(int val){
    struct node<T> *newNode = new node<T>;
    newNode->data = val;
    newNode->link = nullptr;
    return newNode;
}



#endif // DSADJACENCYLIST_H
