#ifndef DS_LIST_H
#define DS_LIST_H
#include <iostream>
#include "Treap.h"

template<class T>
class List {
public:
    struct Node;
    Node* head;
    Node* tail;
    int length;
public:
    List();
    struct Iterator;
    Iterator begin();
    Iterator end();
    Iterator erase(Iterator);
    bool isEmpty();
    void pushBack(T, T, T);
    void pushFront(T, T, T);
    void insert(T, T, T, Iterator);
    Iterator popBack();
    Iterator popFront();
    int size();
    void clear();
    Iterator search(T);
    List<T>& operator=(List<T>& anotherList);
    T& operator[](int);
    void display();
    ~List();
};

template<class T>
struct List<T>::Node {
    Node* next;
    Node* previous;
    T username, name, email;
    friend class List<T>;
    void display()
    {
        cout << "name: " << name<<endl;
        cout << "username: " << username << endl;
        cout << "email: " << email << endl;
    }
    Treap friendTree;
};


template<class T>
struct List<T>::Iterator {
public:
    Node* pointer;
    Iterator();
    Iterator(Node* pointer);
    void operator++();
    void operator--();
    void operator ++ (int);
    void operator -- (int);
    T& operator*();
    bool operator==(const Iterator&);
    bool operator!=(const Iterator&);
    friend class List<T>;
};


// Iterator methods implementations

template<class T>
List<T>::Iterator::Iterator() {
    this->pointer = nullptr;
}

template<class T>
List<T>::Iterator::Iterator(typename List<T>::Node* pointer) {
    this->pointer = pointer;
}

template<class T>
void List<T>::Iterator::operator++() {
    if (pointer != nullptr)
        pointer = pointer->next;
}
template<class T>
void List<T>::Iterator::operator ++ (int)
{
    if (pointer->next == NULL)
    {
        throw "this is out of range no elements after";

    }
    else
    {
        pointer = pointer->next;
    }
}
template<class T>
void List<T>::Iterator::operator--() {
    if (pointer != nullptr)
        pointer = pointer->previous;
}
template<class T>
void List<T>::Iterator::operator -- (int)
{
    if (pointer->previous == NULL)
    {
        throw "this is out of range no elements before";
    }
    else
    {
        pointer = pointer->previous;
    }
}
template<class T>
T& List<T>::Iterator::operator*() {
    if (pointer != nullptr)
        return pointer->username;
    throw std::runtime_error("Invalid memory location.\n");
}

template<class T>
bool List<T>::Iterator::operator==(const Iterator& iterator) {
    return this->pointer == iterator.pointer;
}

template<class T>
bool List<T>::Iterator::operator!=(const Iterator& iterator) {
    return this->pointer != iterator.pointer;
}

// List methods implementations.

template<class T>
List<T>::List() {
    head = tail = nullptr;;
    length = 0;
}
template<class T>
typename List<T>::Iterator List<T>::begin() {
    return Iterator(head);
}

template<class T>
typename List<T>::Iterator List<T>::end() {
    return Iterator(tail == nullptr ? nullptr : tail->next);
}


template<class T>
bool List<T>::isEmpty() {
    return length == 0;
}

template<class T>
void List<T>::pushBack(T username, T name, T email) {
    Node* newNode = new Node();
    newNode->username = username;
    newNode->name = name;
    newNode->email = email;
    newNode->next = new Node();
    if (this->isEmpty()) {
        newNode->previous = nullptr;
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->previous = tail;
        tail = newNode;
        tail->next->previous = tail;
    }
    length++;
}

template<class T>
void List<T>::pushFront(T username, T name, T email) {
    if (this->isEmpty())
        pushBack(username, name, email);
    else {
        Node* newNode = new Node();
        newNode->username = username;
        newNode->name = name;
        newNode->email = email;
        newNode->previous = nullptr;
        newNode->next = head;
        head->previous = newNode;
        head = newNode;
        length++;
    }
}

template<class T>
void List<T>::insert(T username, T name, T email, Iterator position) {
    if (position == this->begin())
        pushFront(username, name, email);
    else if (position == this->end())
        pushBack(username, name, email);
    else {
        Node* newNode = new Node();
        newNode->username = username;
        newNode->name = name;
        newNode->email = email;
        newNode->next = position.pointer;
        newNode->previous = position.pointer->previous;
        position.pointer->previous->next = newNode;
        position.pointer->previous = newNode;
        length++;
    }
}

template<class T>
typename List<T>::Iterator List<T>::popBack() {
    Iterator temp(tail);
    if (this->isEmpty())
        return temp;
    if (this->size() == 1) {
        delete tail->next;
        delete tail;
        head = tail = nullptr;
        length--;
        return temp;
    }
    delete tail->next;
    tail = tail->previous;
    delete tail->next;
    tail->next = new Node();
    length--;
    return temp;
}

template<class T>
typename List<T>::Iterator List<T>::popFront() {
    Iterator temp(head);
    if (this->isEmpty())
        return temp;
    if (this->size() == 1)
        return popBack();
    head = head->next;
    delete head->previous;
    head->previous = nullptr;
    length--;
    return temp;
}

template<class T>
typename List<T>::Iterator List<T>::erase(Iterator position) {
    if (position == this->begin())
        return popFront();
    if (position.pointer == tail)
        return popBack();
    Node* returnValue = position.pointer->next;
    position.pointer->next->previous = position.pointer->previous;
    position.pointer->previous->next = position.pointer->next;
    delete position.pointer;
    length--;
    return Iterator(returnValue);
}

template<class T>
int List<T>::size() {
    return length;
}

template<class T>
void List<T>::clear() {
    for (Iterator it = this->begin(); it != this->end(); ++it)
        Iterator(popBack());
}
template<class T>
typename List<T>::Iterator List<T>::search(T username)
{
    Iterator it = this-> begin();
    for (int i = 0; i < this->size(); i++)
    {
        if (*it == username)
            return it;
        it++;
    }
    return NULL;
}
template<class T>
List<T>& List<T>::operator=(List<T>& anotherList) {
    if (this == &anotherList)
        return *this;
    this->clear();
    for (Iterator it = anotherList.begin(); it != anotherList.end(); ++it)
        this->pushBack(*it);
    return *this;
}

template<class T>
T& List<T>::operator[](int index) {
    Iterator it = this->begin();
    for (int i = 0; i < index; i++)
        ++it;
    return *it;
}

template<class T>
void List<T>::display() {
    for (Iterator it = this->begin(); it != this->end(); ++it)
        std::cout << *it << ' ';
}

template<class T>
List<T>::~List() {
    clear();
}
#endif //DS_LIST_H