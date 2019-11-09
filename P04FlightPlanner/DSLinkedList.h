#ifndef DSLINKED_LIST
#define DSLINKED_LIST

#include <iostream>

template <class T>
class DSNode
{
    template <class U> friend class DSLinkedList;

    public:
        //constructors use member initialization syntax
        DSNode(): next(nullptr), prev(nullptr) {} //default constructor
        DSNode(const T& val): next(nullptr), prev(nullptr), data(val) {}
        DSNode(const DSNode<T>& rhs): next(nullptr), prev(nullptr), data(rhs.data) {}

    private:
        DSNode<T>* next; //pointer to next node
        DSNode<T>* prev; //pointer to previous node
        T data;
};

template<class T>
class DSLinkedList
{
    public:
        DSLinkedList(); //default constructor
        DSLinkedList(const T&); //constructor accepting a value
        DSLinkedList(const DSLinkedList<T>&); //copy constructor

        void insert(const T&); //add to end
        void addFront(const T&);

        int size(); //returns number of elements in linked list
        void remove(int); //removes at index
        T removeFront();
        T removeBack();

        ~DSLinkedList();

        T& operator[](int);
        DSLinkedList<T>& operator=(const DSLinkedList<T>&); //assignment operator

        void copyElements(const DSLinkedList<T>&); //copies all data into this LL
        void emptyList(); //clears data and deallocates memory of nodes
        void print();

        T getNext();
        bool hasNext();

        T get(int);
        bool contains(const T&);


        void resetIterator();
        void backtrack();

    private:
        DSNode<T>* head; //first element of LL
        DSNode<T>* tail; //last element of LL
        DSNode<T>* iterator;
        int elementsNum;
};

//default constructor
template<class T>
DSLinkedList<T>::DSLinkedList() {
    head = nullptr;
    tail = nullptr;
    iterator = nullptr;
    elementsNum = 0;
}


//destructor to release memory allocated in creating nodes
template<class T>
DSLinkedList<T>::~DSLinkedList() {
    emptyList();
}

//constructor to create a one-element LL with value
template<class T>
DSLinkedList<T>::DSLinkedList(const T& val) {
    DSNode<T>* element = new DSNode<T>(val);
    head = tail = iterator = element;
    elementsNum = 1;
}

//copy constructor setting curr LL to parameter LL
template<class T>
DSLinkedList<T>::DSLinkedList(const DSLinkedList<T>& lst) {
    if (lst.elementsNum == 0) { //initialize as default constructor if lst empty
        head = tail = iterator = nullptr;
        elementsNum = 0;
    }
    else {
        copyElements(lst); //copies all elements from parameter list to data LL
    }
}

//copies all data from parameter list into data list
template<class T>
void DSLinkedList<T>::copyElements(const DSLinkedList<T>& lst) {
    insert(lst.head->data);
    if (lst.elementsNum == 1) {
        tail = head;
    }
    else {
        DSNode<T>* current = lst.head->next;
        while (current != nullptr) {
            insert(current->data);
            tail = current;
            current = current->next;
        }
    }
    elementsNum = lst.elementsNum;
}

//clears/destroys nodes; deallocates memory
template<class T>
void DSLinkedList<T>::emptyList() {
    if (elementsNum != 0) {
        if (elementsNum == 1) {
            tail = nullptr;
            iterator = nullptr;
            delete head;
        }
        else {
            tail = nullptr;
            iterator = nullptr;
            while (head != nullptr) {
                DSNode<T>* current = head;
                head = head->next;
                delete current;
            }
        }
        elementsNum = 0;
    }
}

//inserts node with val to end of list
template<class T>
void DSLinkedList<T>::insert(const T& val) {
    DSNode<T>* newPtr = new DSNode<T>(val);
    if (elementsNum == 0) { //if the list is empty
        head = tail = iterator = newPtr;
    }
    else {

        DSNode<T>* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newPtr;
        newPtr->prev = current;
        tail = newPtr;
    }
    elementsNum++;
}

//add value to beginning of list
template<class T>
void DSLinkedList<T>::addFront(const T& val) {
    DSNode<T>* newPtr = new DSNode<T>(val);
    if (elementsNum == 0) {
        head = tail = iterator = newPtr;
    }
    else {
        head->prev = newPtr;
        newPtr->next = head;
        head = newPtr;
    }
    elementsNum++;
}


//returns number of elements in LL
template<class T>
int DSLinkedList<T>::size() {
    return elementsNum;
}

//removes node at index
template<class T>
void DSLinkedList<T>::remove(int index) {
    if (index >= elementsNum || index < 0) {
        throw std::out_of_range("Index is out of bounds");
    }
    if(elementsNum == 0) {
        return;
    }
    else if (elementsNum == 1) {
        tail = nullptr;
        iterator = nullptr;
        delete head;
        head = nullptr;
        elementsNum = 0;
    }
    else if (index == 0) {
        DSNode<T>* temp = head;
        head = temp->next;
        delete temp;
        head->prev = nullptr;
        elementsNum--;
    }
    else if (index == elementsNum-1) {
        DSNode<T>* temp = tail;
        tail = temp->prev;
        delete temp;
        tail->next = nullptr;
        elementsNum--;
    }
    else {
        DSNode<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        current->next->prev = current->prev;
        current->prev->next = current->next;
        delete current;
        elementsNum--;
    }
}

template<class T>
T DSLinkedList<T>::removeFront() {
    if (elementsNum != 0) {
        if (elementsNum == 1) {
            T element = head->data;
            tail = nullptr;
            iterator = nullptr;
            delete head;
            elementsNum = 0;
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
T DSLinkedList<T>::removeBack() {
    if (elementsNum != 0) {
        if (elementsNum == 1) {
                T element = tail->data;
                tail = nullptr;
                iterator = nullptr;
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


//returns reference to element value at a parameter index in this linked list
template<class T>
T& DSLinkedList<T>::operator[](int index) {
    //identical code to get method
    if (index >= elementsNum || index < 0) {
        throw std::out_of_range("Index is out of bounds");
    }
    DSNode<T>* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

//overloaded equals operator that performs deep copy of nodes
template<class T>
DSLinkedList<T>& DSLinkedList<T>::operator=(const DSLinkedList<T>& lst) {
    emptyList();
    if (lst.elementsNum == 0) {
        head = tail = iterator = nullptr;
        elementsNum = 0;
    }
    else {
        copyElements(lst);
    }

    return *this;
}

//returns value of element at parameter
template<class T>
T DSLinkedList<T>::get(int index) {
    if (index >= elementsNum || index < 0) {
        throw std::out_of_range("Index is out of bounds");
    }
    DSNode<T>* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

//returns true if LL contains parameter element
template<class T>
bool DSLinkedList<T>::contains(const T& element) {
    DSNode<T>* current = head;
    while (current != nullptr) {
        if (current->data == element) {
            return true;
        }
        current = current->next;
    }
    return false;
}

//prints out elements of list
template<class T>
void DSLinkedList<T>::print() {
    if (head != nullptr) {
        DSNode<T>* current = head;
        while (current->next != nullptr) {
            std::cout << current->data << std::endl;
            current = current->next;
        }
        std::cout << current->data << std::endl;
    }
}

//returns next item in the LL
template<class T>
T DSLinkedList<T>::getNext() {
    T temp = iterator->data;
    iterator = iterator->next;
    return temp;
}

//checks if end has been reached
template<class T>
bool DSLinkedList<T>::hasNext() {
    if (iterator == nullptr) {
        return false;
    }
    return true;
}

//puts iterator at beginning
template<class T>
void DSLinkedList<T>::resetIterator() {
    iterator = head;
}

//iterator set to second element
template<class T>
void DSLinkedList<T>::backtrack() {
    iterator = head->next;
}

#endif
