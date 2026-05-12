#pragma once
#include <iostream>
template <typename T>
struct Node
{
    T data;
    Node *next;
};

template <typename T>
class LinkedList
{
protected:
    Node<T> *head;
    Node<T> *tail;

public:
    LinkedList();
    virtual void insertAtHead(T value) = 0;
    virtual void insertAtTail(T value) = 0;
    virtual bool isEmpty() = 0;
    virtual void deleteFromHead() = 0;
    virtual void deleteFromTail() = 0;

    virtual ~LinkedList() {}
};

template <typename T>
LinkedList<T>::LinkedList() : head{nullptr}, tail{nullptr}
{
}
