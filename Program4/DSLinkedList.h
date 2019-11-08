#ifndef LINKED_LIST
#define LINKED_LIST

#include <iostream>

template <class T>
class ListNode
{
    template <class U> friend class LinkedList;

    public:
        //constructors use member initialization syntax
        ListNode(): next(nullptr), prev(nullptr) {} //default constructor
        ListNode(const T& val): next(nullptr), prev(nullptr), data(val) {}
        ListNode(const ListNode<T>& rhs): next(nullptr), prev(nullptr), data(rhs.data) {}


        ListNode<T>* next; //pointer to next node
        ListNode<T>* prev; //pointer to previous node
        T data;
};

template<class T>
class DSLinkedList
{
    public:
        DSLinkedList(); //default constructor
        DSLinkedList(const T&); //constructor accepting a value
        DSLinkedList(const DSLinkedList<T>&); //copy constructor

        void add(const T&); //add to end
        void addToFront(const T&);
        T get(int);
        bool contains(const T&);

        int size(); //returns number of elements in linked list
        void remove(int); //removes at index
        T removeFromFront();
        T removeFromBack();

        ~DSLinkedList();

        T& operator[](int);
        DSLinkedList<T>& operator=(const DSLinkedList<T>&); //assignment operator

        void copyAll(const DSLinkedList<T>&); //copies all data into this linked list
        void clear(); //clears all data and deallocates memory for nodes
        void print();

        T getNext();
        bool hasNext();
        void reset();
        void backtrack();

    private:
        ListNode<T>* head; //points to first element of linked list
        ListNode<T>* back; //points to last element of linked list
        ListNode<T>* iter;
        int numElements;
};

//default constructor
template<class T>
DSLinkedList<T>::DSLinkedList() {
    head = nullptr;
    back = nullptr;
    iter = nullptr;
    numElements = 0;
}

//constructor that accepts a value to create a one-element linked list
template<class T>
DSLinkedList<T>::DSLinkedList(const T& val) {
    ListNode<T>* element = new ListNode<T>(val);
    head = back = iter = element; //head and back point to only node
    numElements = 1;
}

//copy constructor that sets this linked list equal to linked list parameter
template<class T>
DSLinkedList<T>::DSLinkedList(const DSLinkedList<T>& lst) {
    if (lst.numElements == 0) { //edge case: if lst is empty, then initialize as if it were default constructor
        head = back = iter = nullptr;
        numElements = 0;
    }
    else {
        copyAll(lst); //copies all elements from lst to this linked list
    }
}

//adds value as a payload of a node to the end of this linked list
template<class T>
void DSLinkedList<T>::add(const T& val) {
    ListNode<T>* newPtr = new ListNode<T>(val);
    if (numElements == 0) { //edge case: if the list is empty
        head = back = iter = newPtr; //head and back point to newly created node
    }
    else {
        //back->next = newPtr; //link new node to end of list
        //newPtr->prev = back;
        //back = newPtr; //point end pointer to new last node

        //ensures newPtr is added to end of the linkedlist
        ListNode<T>* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }

        //connects new node to last node in linkedlist
        current->next = newPtr;
        newPtr->prev = current;
        back = newPtr; //manually sets back to newly added element
    }
    numElements++;
}

//adds value as payload of node at beginning of this linked list
template<class T>
void DSLinkedList<T>::addToFront(const T& val) {
    ListNode<T>* newPtr = new ListNode<T>(val);
    if (numElements == 0) { //edge case: if list is empty
        head = back = iter = newPtr;
    }
    else {
        head->prev = newPtr; //link new node to front of list
        newPtr->next = head;
        head = newPtr; //point head pointer to new first node
    }
    numElements++;
}

//returns value of element at index parameter
template<class T>
T DSLinkedList<T>::get(int index) {
    if (index >= numElements || index < 0) { //edge case: if index is not valid (0 to numElements-1)
        throw std::out_of_range("Index is out of bounds");
    }
    ListNode<T>* current = head;
    for (int i = 0; i < index; i++) { //iterates through linked list until node with index is found
        current = current->next;
    }
    return current->data; //return data payload contained by that node
}

//Returns true if linked list contains specified element
template<class T>
bool DSLinkedList<T>::contains(const T& element) {
    ListNode<T>* current = head;
    while (current != nullptr) {
        if (current->data == element) {
            return true;
        }
        current = current->next; //moves to next node
    }
    return false;
}

//returns number of elements in this linked list
template<class T>
int DSLinkedList<T>::size() {
    return numElements;
}

//removes node at a parameter index
template<class T>
void DSLinkedList<T>::remove(int index) {
    if (index >= numElements || index < 0) { //edge case: if index is not valid (0 to numElements-1)
        throw std::out_of_range("Index is out of bounds");
    }

    if(numElements == 0) { //edge case: if list is empty already
        return;
    }
    else if (numElements == 1) { //edge case: if list has only one element
        back = nullptr;
        iter = nullptr;
        delete head; //deletes and releases memory allocated to first and only element
        head = nullptr;
        numElements = 0;
    }
    else if (index == 0) { //edge case: if first element is the one to be removed
        ListNode<T>* temp = head;
        head = temp->next; //move pointer to first node to second element
        delete temp; //delete first element
        head->prev = nullptr; //set new first element backward looking pointer to null
        numElements--;
    }
    else if (index == numElements-1) { //edge case: if last element is the one to be deleted
        ListNode<T>* temp = back;
        back = temp->prev; //move pointer to last node to second to last element
        delete temp; //delete last element
        back->next = nullptr; //set new last element forward looking pointer to null
        numElements--;
    }
    else {
        ListNode<T>* current = head;
        for (int i = 0; i < index; i++) { //iterates to element to be deleted
            current = current->next;
        }
        //reassigns forward pointer of previous node and backward pointer of next node to connect previous and next nodes to each other
        current->next->prev = current->prev;
        current->prev->next = current->next;
        delete current;
        numElements--;
    }
}

template<class T>
T DSLinkedList<T>::removeFromFront() {
    if (numElements != 0) {
        if (numElements == 1) {
            T element = head->data;
            back = nullptr;
            iter = nullptr;
            delete head;
            numElements = 0;
            return element;
        }
        else {
            T element = head->data;
            remove(0);
            return element;
        }
    }
}

template<class T>
T DSLinkedList<T>::removeFromBack() {
    if (numElements != 0) {
        if (numElements == 1) {
                T element = back->data;
                back = nullptr;
                iter = nullptr;
                delete head;
                numElements = 0;
                return element;
        }
        else {
            T element = back->data;
            remove(numElements-1);
            return element;
        }
    }
}

//destructor to release memory allocated in creating nodes
template<class T>
DSLinkedList<T>::~DSLinkedList() {
    clear();
}

//returns reference to element value at a parameter index in this linked list
template<class T>
T& DSLinkedList<T>::operator[](int index) {
    //identical code to get method
    if (index >= numElements || index < 0) {
        throw std::out_of_range("Index is out of bounds");
    }
    ListNode<T>* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

//assignment operator that performs deep copy of nodes and payload
template<class T>
DSLinkedList<T>& DSLinkedList<T>::operator=(const DSLinkedList<T>& lst) {
    clear(); //deallocates all memory and destroys nodes/payloads

    if (lst.numElements == 0) {
        head = back = iter = nullptr; //default constructor-like code
        numElements = 0;
    }
    else {
        copyAll(lst); //calls method to copy all elements in parameter lst
    }

    return *this;
}

//copies all data from parameter lst into this linked list
template<class T>
void DSLinkedList<T>::copyAll(const DSLinkedList<T>& lst) {
    add(lst.head->data); //head points to newly created first node based on first value of lst
    if (lst.numElements == 1) {
        back = head;
    }
    else {
        ListNode<T>* current = lst.head->next; //sets current pointer at second node of lst
        while (current != nullptr) { //iterates until end of the parameter list
            add(current->data); //calls add function to properly allocate memory for new node
            back = current;
            current = current->next; //advances to next node with data to be copied
        }
    }
    numElements = lst.numElements;
}

//releases all memory allocated to nodes and destroys nodes and their payloads
template<class T>
void DSLinkedList<T>::clear() {
    if (numElements != 0) { //if linked list isn't already empty
        if (numElements == 1) { //edge case: if only contains one element
            back = nullptr;
            iter = nullptr;
            delete head;
        }
        else {
            back = nullptr;
            iter = nullptr;
            while (head != nullptr) {
                ListNode<T>* current = head; //current points to element pointed to by head before head advances
                head = head->next; //head points to next element
                delete current; //deletes and deallocates pointers of node just vacated by head
            }
        }
        numElements = 0;
    }
}

//prints out all payloads of this linked list
template<class T>
void DSLinkedList<T>::print() {
    if (head != nullptr) { //if list is not empty
        ListNode<T>* current = head;
        while (current->next != nullptr) { //while there is a valid next element
            std::cout << current->data << std::endl; //print current payload
            current = current->next; //advance pointer to next element
        }
        std::cout << current->data << std::endl; //print last node's payload (which did not print through while loop)
    }
}

//returns next item in the linked list
template<class T>
T DSLinkedList<T>::getNext() {
    T temp = iter->data;
    iter = iter->next;
    return temp;
}

//checks to see if end of linked list has been reached
template<class T>
bool DSLinkedList<T>::hasNext() {
    if (iter == nullptr) {
        return false;
    }
    return true;
}

//puts iterator through linked list back at beginning
template<class T>
void DSLinkedList<T>::reset() {
    iter = head;
}

//for flight plan project: sets iterator at second element
template<class T>
void DSLinkedList<T>::backtrack() {
    iter = head->next;
}

#endif


//#ifndef DSLINKEDLIST_H
//#define DSLINKEDLIST_H

//#include <iostream>
//#include <cstring>
//#include <DSString.h>
//#include <DSVector.h>
//#include <DSNode.h>

//using namespace std;

//template <class T>
//class DSLinkedList{
//private:
//    int elementsNum; //indicates number of elements
//    DSNode<T>* head;
//    DSNode<T>* tail;
//    DSNode<T>* iteratorNode; //first and last elements of LL

//public:
//    DSLinkedList(); //default
//    DSLinkedList(const T&);
//    DSLinkedList(const DSLinkedList<T>&); //copy

//    ~DSLinkedList();

//    void createNode(T);
//    void insertFront(const T& val);
//    void insertMiddle(int, const T&);
//    void insertEnd(const T&);
//    void add(const T&);

//    void removeAtIndex(int);
//    void deleteFirst();
//    void deleteLast();

//    void remove(int index);

//    T removeFromFront();
//    T removeFromBack();

//    void print();
//    void copyElements(const DSLinkedList<T>&);
//    T getNextElement();
//    bool hasNext();
//    void resetIterator();
//    void backtrack();

//    T get(int);
//    bool contains(const T&);
//    int getSize(); //num elements in LL

//    DSLinkedList<T>& operator=(const DSLinkedList<T>&);
//    T& operator[](int);

//    void emptyList();
//};

//default constructor
//template<class T>
//DSLinkedList<T>::DSLinkedList() {
//    head = nullptr;
//    tail = nullptr;
//    iteratorNode = nullptr;
//    elementsNum = 0;
//}

//constructor that accepts a value to create a one-element linked list
//template<class T>
//DSLinkedList<T>::DSLinkedList(const DSLinkedList<T>& list) {
//    if(list.elementsNum == 0){
//        head = tail = iteratorNode = nullptr;
//        elementsNum = 0;
//    }
//    else{
//        copyElements(list);
//    }
//}

//template<class T>
//DSLinkedList<T>::DSLinkedList(const T& val) {
//    DSNode<T>* element = new DSNode<T>(val);
//    head = tail = iteratorNode = element; //head and tail point to only node
//    elementsNum = 1;
//}


//template <typename T>
//DSLinkedList<T>::~DSLinkedList(){
//    emptyList();
//}

//releases all memory allocated to nodes and destroys nodes
//template<class T>
//void DSLinkedList<T>::emptyList() {
//    if (elementsNum != 0) { //if linked list isn't already empty
//        if (elementsNum == 1) { //edge case: if only contains one element
//            tail = nullptr;
//            iteratorNode = nullptr;
//            delete head;
//        }
//        else {
//            tail = nullptr;
//            iteratorNode = nullptr;
//            while (head != nullptr) {
//                DSNode<T>* current = head; //current points to element pointed to by head before head advances
//                head = head->next; //head points to next element
//                delete current; //deletes and deallocates pointers of node just vacated by head
//            }
//        }
//        elementsNum = 0;
//    }
//}

//template<class T>
//DSLinkedList<T>& DSLinkedList<T>::operator=(const DSLinkedList<T>& otherList){
//    emptyList(); //deallocates all memory and destroys nodes

//    if (otherList.elementsNum == 0) {
//        head = tail = iteratorNode = nullptr;
//        elementsNum = 0;
//    }
//    else {
//        copyElements(otherList); //copies all elements to otherList
//    }

//    return *this;
//}

//copies all data from parameter lst into this linked list
//template<class T>
//void DSLinkedList<T>::copyElements(const DSLinkedList<T>& list) {
//    insertEnd(list.head->data);//head points to newly created first node based on first value of lst
//    if (list.elementsNum == 1) {
//        tail = head;
//    }
//    else {
//        DSNode<T>* current = list.head->next;
//        while (current != nullptr) {
//            insertEnd(current->data);
//            tail = current;
//            current = current->next;
//        }
//    }
//    elementsNum = list.elementsNum;
//}

//returns reference to element value at designated index
//template<class T>
//T& DSLinkedList<T>::operator[](int index) {
//    if (index >= elementsNum || index < 0) {
//        throw std::out_of_range("Index is out of bounds");
//    }
//    DSNode<T>* current = head;
//    for (int i = 0; i < index; i++) {
//        current = current->next;
//    }
//    return current->data;
//}

//template <typename T>
//int DSLinkedList<T>::getSize(){
//    return elementsNum;
//}

//returns value of element at index parameter
//template<class T>
//T DSLinkedList<T>::get(int index) {
//    if (index >= elementsNum || index < 0) { //edge case: if index is not valid (0 to numElements-1)
//        throw std::out_of_range("Index is out of bounds");
//    }
//    DSNode<T>* current = head;
//    for (int i = 0; i < index; i++) { //iterates through linked list until node with index is found
//        current = current->next;
//    }
//    return current->data; //return data payload contained by that node
//}

//template <typename T>
//void DSLinkedList<T>::createNode(T val){

//    //creates new node, stores next value as NULL
//    DSNode<T>* temp = new DSNode<T>();
//    temp->data = val;
//    temp->next = NULL;

//    //if no head, new temp node must be head/tail and cleared
//    if(head == NULL){
//        head = temp;
//        tail = temp;
//        temp = NULL;
//    }
//    //else, head exists
//    //set tail of list to point to temp, and be equal to temp
//    else{
//        tail->next = temp;
//        tail = temp;
//    }
//}

//template <typename T>
//void DSLinkedList<T>::print(){
//    DSNode<T> *node = new DSNode<T>();
//    node = head;
//    while(node != NULL){
//        cout << node->data << '\t';
//        node = node->next;
//    }
//}


//adds value as payload of node at beginning of this linked list
//template<class T>
//void DSLinkedList<T>::insertFront(const T& val) {
//    DSNode<T>* newPtr = new DSNode<T>(val);
//    if (elementsNum == 0) { //edge case: if list is empty
//        head = tail = iteratorNode = newPtr;
//    }
//    else {
//        head->prev = newPtr; //link new node to front of list
//        newPtr->next = head;
//        head = newPtr; //point head pointer to new first node
//    }
//    elementsNum++;
//}

//template <typename T>
//void DSLinkedList<T>::insertEnd(const T& value){
//    DSNode<T> *newNode = new DSNode<T>(value);
//    if(elementsNum == 0){
//        head = tail = iteratorNode = newNode;
//    }
//    else{
//        DSNode<T>* current = head;
//        while(current->next != NULL){
//            current = current->next;
//        }
//        current->next = newNode;
//        newNode->prev = current;
//        tail = newNode;
//    }
//    elementsNum++;
//}

//template <typename T>
//void DSLinkedList<T>::insertMiddle(int pos, const T& value){
//    DSNode<T> *prev = new DSNode<T>();
//    DSNode<T> *curr = new DSNode<T>();
//    DSNode<T> *temp = new DSNode<T>(value);

//    //set current node to be equal to head
//    curr = head;

//    //iterate to position of insertion
//    for(int i = 0; i < pos; i++){
//        //make prev point to current, make curr point to next
//        prev = curr;
//        curr = curr->next;
//    }
//    //temp->data = value;

//    //make prev point to temp, make temp point to curr
//    prev->next = temp;
//    temp->next = curr;
//}

//removes node at a parameter index
//template<class T>
//void DSLinkedList<T>::remove(int index) {
//    if (index >= elementsNum || index < 0) {
//        throw std::out_of_range("Index is out of bounds");
//    }

//    if(elementsNum == 0) { //empty list
//        return;
//    }
//    else if (elementsNum == 1) { //one element list
//        tail = nullptr;
//        iteratorNode = nullptr;
//        delete head; //deletes and releases memory allocated to first and only element
//        head = nullptr;
//        elementsNum = 0;
//    }
//    else if (index == 0) { //remove first elemnt
//        DSNode<T>* temp = head;
//        head = temp->next; //move pointer to first node to second element
//        delete temp; //delete first element
//        head->prev = nullptr; //set new first element backward looking pointer to null
//        elementsNum--;
//    }
//    else if (index == elementsNum-1) { //remove last element
//        DSNode<T>* temp = tail;
//        tail = temp->prev; //move pointer to last node to second to last element
//        delete temp; //delete last element
//        tail->next = nullptr; //set new last element forward looking pointer to null
//        elementsNum--;
//    }
//    else {
//        DSNode<T>* current = head;
//        for (int i = 0; i < index; i++) { //iterates to element to be deleted
//            current = current->next;
//        }
//        //reassigns forward pointer of previous node and backward pointer of next node to connect previous and next nodes to each other
//        current->next->prev = current->prev;
//        current->prev->next = current->next;
//        delete current;
//        elementsNum--;
//    }
//}


//template<class T>
//T DSLinkedList<T>::removeFromBack() {
//    if (elementsNum != 0) {
//        if (elementsNum == 1) {
//            T element = tail->data;
//            tail = nullptr;
//            iteratorNode = nullptr;
//            delete head;
//            elementsNum = 0;
//            return element;
//        }
//        else {
//            T element = tail->data;
//            remove(elementsNum-1);
//            return element;
//        }
//    }
//}

//template<class T>
//T DSLinkedList<T>::removeFromFront() {
//    if (elementsNum != 0) {
//        if (elementsNum == 1) {
//            T element = head->data;
//            tail = nullptr;
//            iteratorNode = nullptr;
//            delete head;
//            elementsNum = 0;
//            return element;
//        }
//        else {
//            T element = head->data;
//            remove(0);
//            return element;
//        }
//    }
//}

//template <typename T>
//bool DSLinkedList<T>::contains(const T& elem){
//    DSNode<T>* curr = head;
//    while(curr != nullptr){
//        if(curr->data == elem){
//            return true;
//        }
//        curr = curr->next;
//    }
//    return false;
//}

//returns next item in LL
//template <typename T>
//T DSLinkedList<T>::getNextElement(){
//    T temp = iteratorNode->data;
//    iteratorNode = iteratorNode->next;
//    return temp;
//}

//checks if end of LL has been reached
//template <typename T>
//bool DSLinkedList<T>::hasNext(){
//    if(iteratorNode == nullptr){
//        return false;
//    }
//    return true;
//}

//template <typename T>
//void DSLinkedList<T>::resetIterator(){
//    iteratorNode = head; //iterator set back to head
//}

//template <typename T>
//void DSLinkedList<T>::backtrack(){
//    iteratorNode = head->next; //iterator set at second element
//}

//template <typename T>
//void DSLinkedList<T>::deleteFirst(){
//    DSNode<T> *temp = new DSNode<T>();
//    temp = head;
//    head = head->next;
//    delete temp;
//}

//template <typename T>
//void DSLinkedList<T>::deleteLast(){
//    DSNode<T> *prev = new DSNode<T>();
//    DSNode<T> *curr = new DSNode<T>();
//    curr = head;
//    //traverses through end until NULL is reached
//    while(curr->next != NULL){
//        prev = curr;
//        curr = curr->next;
//    }
//    tail = prev;
//    prev->next = NULL;
//    delete curr;
//}


//#endif // DSLINKEDLIST_H
