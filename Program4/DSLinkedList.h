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
    int elementsNum; //indicates number of elements
    DSNode<T>* head;
    DSNode<T>* tail;
    DSNode<T>* iteratorNode; //first and last elements of LL

public:
    DSLinkedList(); //default
    DSLinkedList(const T&);
    DSLinkedList(const DSNode<T>&); //copy

    ~DSLinkedList();

    void createNode(T);
    void insertStart(const T&);
    void insertMiddle(int, const T&);
    void insertEnd(const T&);
    void add(const T&);

    void removeAtIndex(int);
    void deleteFirst();
    void deleteLast();

    void print();
    void copyAll(const DSLinkedList<T>&);

    T get(int);
    bool contains(const T&);
    int getSize(); //num elements in LL
    DSLinkedList<T>& operator=(const DSLinkedList<T>&);
    void clear();
    T pop();
    T peek();
};

//default constructor
template<class T>
DSLinkedList<T>::DSLinkedList() {
    head = nullptr;
    tail = nullptr;
    iteratorNode = nullptr;
    elementsNum = 0;
}

//constructor that accepts a value to create a one-element linked list
template<class T>
DSLinkedList<T>::DSLinkedList(const T& val) {
    DSNode<T>* element = new DSNode<T>(val);
    head = tail = iteratorNode = element; //head and tail point to only node
    elementsNum = 1;
}

template <typename T>
DSLinkedList<T>::~DSLinkedList(){
    clear();
}

//releases all memory allocated to nodes and destroys nodes and their payloads
template<class T>
void DSLinkedList<T>::clear() {
    if (elementsNum != 0) { //if linked list isn't already empty
        if (elementsNum == 1) { //edge case: if only contains one element
            tail = nullptr;
            iteratorNode = nullptr;
            delete head;
        }
        else {
            tail = nullptr;
            iteratorNode = nullptr;
            while (head != nullptr) {
                DSNode<T>* current = head; //current points to element pointed to by head before head advances
                head = head->next; //head points to next element
                delete current; //deletes and deallocates pointers of node just vacated by head
            }
        }
        elementsNum = 0;
    }
}

template<class T>
DSLinkedList<T>& DSLinkedList<T>::operator=(const DSLinkedList<T>& otherList){
    if(otherList != this){
        DSNode<T> temp = head;
        while(temp.next != NULL){
            head = head->next;
            delete temp;
            temp = head;

        }
        int count = 0;
        temp = otherList.head;
        while(temp != NULL){
            insertStart(temp);
        }
    }
    return *this;
}

template <typename T>
int DSLinkedList<T>::getSize(){
    return elementsNum;
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
void DSLinkedList<T>::insertStart(const T& value){
    DSNode<T> *node = new DSNode<T>();
    node->data = value;

    //make the node point to head
    node->next = head;

    //make the node be the head
    head = node;
}

template <typename T>
void DSLinkedList<T>::insertEnd(const T& value){
    DSNode<T> *newNode = new DSNode<T>(value);
    if(elementsNum == 0){
        head = tail = iteratorNode = newNode;
    }
    else{
        DSNode<T>* current = head;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
        tail = newNode;
    }
    elementsNum++;
}

template <typename T>
void DSLinkedList<T>::insertMiddle(int pos, const T& value){
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
