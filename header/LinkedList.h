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
    
    virtual void insertAtHead(T value);
    virtual void insertAtTail(T value);
    virtual bool isEmpty();
    virtual void deleteFromHead();
    virtual void deleteFromTail();

    LinkedList();
    ~LinkedList();
};

template <typename T>
LinkedList<T>::LinkedList() : head{nullptr}, tail{nullptr}
{
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    while (isEmpty() == false)
    {
        deleteFromHead();
    }
}

template <typename T>
void LinkedList<T>::deleteFromTail()
{
    if (isEmpty())
    {
        std::cout << "Error: linked list is empty, can't remove more items\n";
        return;
    }

    else if (head == tail) // single node<T> case
    {
        delete head;
        head = nullptr;
        tail = nullptr;
    }

    else
    {
        Node<T> *t = head;
        while (true)
        {
            if (t->next == tail)
                break;

            t = t->next;
        }

        delete tail;
        t->next = nullptr;
        tail = t;
    }
}

template <typename T>
void LinkedList<T>::deleteFromHead()
{
    if (isEmpty())
    {
        std::cout << "Error: linked list is empty, can't remove more items\n";
        return;
    }

    else if (head == tail) // single node<T> case
    {
        delete head;
        head = nullptr;
        tail = nullptr;
    }

    else
    {
        Node<T> *t = head;
        head = head->next;
        delete t;
        t = nullptr;
    }
}

template <typename T>
bool LinkedList<T>::isEmpty()
{
    if (head == nullptr && tail == nullptr)
    {
        return true;
    }

    return false;
}

template <typename T>
void LinkedList<T>::insertAtTail(T value)
{
    Node<T> *nn = new Node<T>;
    nn->next = nullptr;
    nn->data = value;

    if (head == nullptr && tail == nullptr) // empty LL (first Node<T> to be added)
    {
        head = nn;
        tail = nn;
    }
    else // all the rest values (Nodes)
    {
        tail->next = nn;
        tail = nn;
    }
}

template <typename T>
void LinkedList<T>::insertAtHead(T value)
{
    Node<T> *nn = new Node<T>;
    nn->next = nullptr;
    nn->data = value;

    if (head == nullptr && tail == nullptr) // empty LL
    {
        head = nn;
        tail = nn;
    }
    else
    {
        nn->next = head;
        head = nn;
    }
}