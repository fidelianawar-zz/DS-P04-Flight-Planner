#ifndef DSLINKEDLIST_H
#define DSLINKEDLIST_H

#include <iostream>
#include <cstring>
#include <DSString.h>
#include <DSVector.h>
#include <vector>

template <typename T>
class Node{
public:
    Node* next;
    T data;
};

using namespace std;

template <typename T>
class DSLinkedList{
private:
    T* elements;
    int vectorSize;
    int capacity;
public:
    int length;
    Node<T>* head, tail;

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
    Node<T>* temp = new Node<T>();
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
    Node<T> *node = new Node<T>();
    node->data = value;
    node->next = head;
    head = node;
}

template <typename T>
void DSLinkedList<T>::insertEnd(T value){
    Node<T> *node = new Node<T>();
    node->data = value;
    tail->next = node;
    tail = node;
}

template <typename T>
void DSLinkedList<T>::insertMiddle(int pos, T value){
    Node<T> *node = new Node<T>();
    Node<T> *prev = new Node<T>();
    Node<T> *curr = new Node<T>();
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
