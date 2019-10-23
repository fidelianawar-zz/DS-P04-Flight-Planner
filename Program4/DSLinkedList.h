#ifndef DSLINKEDLIST_H
#define DSLINKEDLIST_H

#include <iostream>
#include <cstring>
#include <DSString.h>
#include <DSVector.h>
#include <DSNode.h>

using namespace std;

template <class T>
class DSLinkedList{
private:
    T* elements;
    int vectorSize;
    int capacity;
public:
    int length;
    DSNode<T>* head, tail;

    DSLinkedList();
    ~DSLinkedList();
    void createNode(T);
    void insertStart(T);
    void insertMiddle(int, T);
    void insertEnd(T);
    void print();
    T pop();
    T peek();
};


template <typename T>
DSLinkedList<T>::DSLinkedList(){
    this->length = 0;
    this->head = NULL;
    this->tail = NULL;
}

template <typename T>
DSLinkedList<T>::~DSLinkedList(){
    std::cout << "LIST DELETED";
}

template <typename T>
void DSLinkedList<T>::createNode(T val){

    //creates new node, stores next value as NULL
    DSNode<T>* temp = new DSNode<T>();
    temp->data = val;
    temp->next = NULL;

    //new node must be head and tail and then cleared
    if(head == NULL){
        head = temp;
        tail = temp;
        temp = NULL;
    }
    //else, head already exists
    else{
        tail->next = temp;
        tail = temp;
    }
}

template <typename T>
void DSLinkedList<T>::insertStart(T value){
    DSNode<T> *node = new DSNode<T>();
    node->data = value;
    node->next = head;
    head = node;
}

template <typename T>
void DSLinkedList<T>::insertEnd(T value){
    DSNode<T> *node = new DSNode<T>();
    node->data = value;
    tail->next = node;
    tail = node;
}

template <typename T>
void DSLinkedList<T>::insertMiddle(int pos, T value){
    DSNode<T> *node = new DSNode<T>();
    DSNode<T> *prev = new DSNode<T>();
    DSNode<T> *curr = new DSNode<T>();
    curr = head;
    for(int i = 0; i < pos; i++){
        prev = curr;
        curr = curr->next;
    }
    /*
     *T storeNext = curr->next;
     * curr->next = node;
     * node->next= storeNext;
     */
    node->data = value;
    prev->next = node;
    node->next = curr;
}

#endif // DSLINKEDLIST_H
