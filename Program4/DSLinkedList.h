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

    void deleteFirst();
    void deleteLast();

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

    //if no head, new temp node must be head/tail and cleared
    if(head == NULL){
        head = temp;
        tail = temp;
        temp = NULL;
    }
    //else, head exists
    //set tail of list to point to temp, and be equal to temp
    else{
        tail->next = temp;
        tail = temp;
    }
}

template <typename T>
void DSLinkedList<T>::print(){
    DSNode<T> *node = new DSNode<T>();
    node = head;
    while(node != NULL){
        cout << node->data << '\t';
        node = node->next;
    }
}

template <typename T>
void DSLinkedList<T>::insertStart(T value){
    DSNode<T> *node = new DSNode<T>();
    node->data = value;

    //make the node point to head
    node->next = head;

    //make the node be the head
    head = node;
}

template <typename T>
void DSLinkedList<T>::insertEnd(T value){
    DSNode<T> *node = new DSNode<T>();
    node->data = value;

    //make the tail point to the new node
    tail->next = node;

    //make the tail the new node
    tail = node;
}

template <typename T>
void DSLinkedList<T>::insertMiddle(int pos, T value){
    DSNode<T> *prev = new DSNode<T>();
    DSNode<T> *curr = new DSNode<T>();
    DSNode<T> *temp = new DSNode<T>();

    //set current node to be equal to head
    curr = head;

    //iterate to position of insertion
    for(int i = 0; i < pos; i++){
        //make prev point to current, make curr point to next
        prev = curr;
        curr = curr->next;
    }
    temp->data = value;

    //make prev point to temp, make temp point to curr
    prev->next = temp;
    temp->next = curr;
}

template <typename T>
void DSLinkedList<T>::deleteFirst(){
    DSNode<T> *temp = new DSNode<T>();
    temp = head;
    head = head->next;
    delete temp;
}

template <typename T>
void DSLinkedList<T>::deleteLast(){
    DSNode<T> *prev = new DSNode<T>();
    DSNode<T> *curr = new DSNode<T>();
    curr = head;
    //traverses through end until NULL is reached
    while(curr->next != NULL){
        prev = curr;
        curr = curr->next;
    }
    tail = prev;
    prev->next = NULL;
    delete curr;
}


#endif // DSLINKEDLIST_H
