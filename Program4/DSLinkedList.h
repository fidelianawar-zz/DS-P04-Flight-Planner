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
    void addToFront(const T& val);
    void insertMiddle(int, const T&);
    void insertEnd(const T&);
    void add(const T&);

    void removeAtIndex(int);
    void deleteFirst();
    void deleteLast();
    void remove(int index);
    T removeFromBack();

    void print();
    void copyElements(const DSLinkedList<T>&);

    T get(int);
    bool contains(const T&);
    int getSize(); //num elements in LL

    DSLinkedList<T>& operator=(const DSLinkedList<T>&);
    T& operator[](int);

    void emptyList();
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
    emptyList();
}

//releases all memory allocated to nodes and destroys nodes and their payloads
template<class T>
void DSLinkedList<T>::emptyList() {
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
    emptyList(); //deallocates all memory and destroys nodes

       if (otherList.elementsNum == 0) {
           head = tail = iteratorNode = nullptr;
           elementsNum = 0;
       }
       else {
           copyElements(otherList); //copies all elements to otherList
       }

       return *this;
}

//copies all data from parameter lst into this linked list
template<class T>
void DSLinkedList<T>::copyElements(const DSLinkedList<T>& lst) {
    insertEnd(lst.head->data);
    if (lst.elementsNum == 1) {
        tail = head;
    }
    else {
        DSNode<T>* current = lst.head->next;
        while (current != nullptr) {
            insertEnd(current->data);
            tail = current;
            current = current->next;
        }
    }
    elementsNum = lst.elementsNum;
}

//returns reference to element value at designated index
template<class T>
T& DSLinkedList<T>::operator[](int index) {
    if (index >= elementsNum || index < 0) {
        throw std::out_of_range("Index is out of bounds");
    }
    DSNode<T>* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

template <typename T>
int DSLinkedList<T>::getSize(){
    return elementsNum;
}

//returns value of element at index parameter
template<class T>
T DSLinkedList<T>::get(int index) {
    if (index >= elementsNum || index < 0) { //edge case: if index is not valid (0 to numElements-1)
        throw std::out_of_range("Index is out of bounds");
    }
    DSNode<T>* current = head;
    for (int i = 0; i < index; i++) { //iterates through linked list until node with index is found
        current = current->next;
    }
    return current->data; //return data payload contained by that node
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


//adds value as payload of node at beginning of this linked list
template<class T>
void DSLinkedList<T>::addToFront(const T& val) {
    DSNode<T>* newPtr = new DSNode<T>(val);
    if (elementsNum == 0) { //edge case: if list is empty
        head = tail = iteratorNode = newPtr;
    }
    else {
        head->prev = newPtr; //link new node to front of list
        newPtr->next = head;
        head = newPtr; //point head pointer to new first node
    }
    elementsNum++;
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

//removes node at a parameter index
template<class T>
void DSLinkedList<T>::remove(int index) {
    if (index >= elementsNum || index < 0) {
        throw std::out_of_range("Index is out of bounds");
    }

    if(elementsNum == 0) { //empty list
        return;
    }
    else if (elementsNum == 1) { //one element list
        tail = nullptr;
        iteratorNode = nullptr;
        delete head; //deletes and releases memory allocated to first and only element
        head = nullptr;
        elementsNum = 0;
    }
    else if (index == 0) { //remove first elemnt
        DSNode<T>* temp = head;
        head = temp->next; //move pointer to first node to second element
        delete temp; //delete first element
        head->prev = nullptr; //set new first element backward looking pointer to null
        elementsNum--;
    }
    else if (index == elementsNum-1) { //remove last element
        DSNode<T>* temp = tail;
        tail = temp->prev; //move pointer to last node to second to last element
        delete temp; //delete last element
        tail->next = nullptr; //set new last element forward looking pointer to null
        elementsNum--;
    }
    else {
        DSNode<T>* current = head;
        for (int i = 0; i < index; i++) { //iterates to element to be deleted
            current = current->next;
        }
        //reassigns forward pointer of previous node and backward pointer of next node to connect previous and next nodes to each other
        current->next->prev = current->prev;
        current->prev->next = current->next;
        delete current;
        elementsNum--;
    }
}


template<class T>
T DSLinkedList<T>::removeFromBack() {
    if (elementsNum != 0) {
        if (elementsNum == 1) {
                T element = tail->data;
                tail = nullptr;
                iteratorNode = nullptr;
                delete head;
                elementsNum = 0;
                return element;
        }
        else {
            T element = tail->data;
            remove(elementsNum-1);
            return element;
        }
    }
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
