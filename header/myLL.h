#pragma once
#include "LinkedList.h"

template <typename T>
class myLL : public LinkedList<T>
{
public:
    void insertAtTail(T value);
    void insertAtHead(T value);
    bool isEmpty();
    void deleteFromHead();
    void deleteFromTail();

    ~myLL();
};

template <typename T>
myLL<T>::~myLL()
{

    while (myLL<T>::isEmpty() == false)
    {
        deleteFromHead();
    }
}

template <typename T>
void myLL<T>::deleteFromTail()
{
    if (myLL<T>::isEmpty())
    {
        std::cout << "Error: linked list is empty, can't remove more items\n";
        return;
    }

    else if (LinkedList<T>::head == LinkedList<T>::tail) // single node<T> case
    {
        delete LinkedList<T>::head;
        LinkedList<T>::head = nullptr;
        LinkedList<T>::tail = nullptr;
    }

    else
    {
        Node<T> *t = LinkedList<T>::head;
        while (true)
        {
            if (t->next == LinkedList<T>::tail)
                break;

            t = t->next;
        }

        delete LinkedList<T>::tail;
        t->next = nullptr;
        LinkedList<T>::tail = t;
    }
}

template <typename T>
void myLL<T>::deleteFromHead()
{
    if (myLL<T>::isEmpty())
    {
        std::cout << "Error: linked list is empty, can't remove more items\n";
        return;
    }

    else if (LinkedList<T>::head == LinkedList<T>::tail) // single node<T> case
    {
        delete LinkedList<T>::head;
        LinkedList<T>::head = nullptr;
        LinkedList<T>::tail = nullptr;
    }

    else
    {
        Node<T> *t = LinkedList<T>::head;
        LinkedList<T>::head = LinkedList<T>::head->next;
        delete t;
        t = nullptr;
    }
}

template <typename T>
bool myLL<T>::isEmpty()
{
    if (LinkedList<T>::head == nullptr && LinkedList<T>::tail == nullptr)
    {
        return true;
    }

    return false;
}

template <typename T>
void myLL<T>::insertAtTail(T value)
{
    Node<T> *nn = new Node<T>;
    nn->next = nullptr;
    nn->data = value;

    if (LinkedList<T>::head == nullptr && LinkedList<T>::tail == nullptr) // empty LL (first Node<T> to be added)
    {
        LinkedList<T>::head = nn;
        LinkedList<T>::tail = nn;
    }
    else // all the rest values (Nodes)
    {
        LinkedList<T>::tail->next = nn;
        LinkedList<T>::tail = nn;
    }
}

template <typename T>
void myLL<T>::insertAtHead(T value)
{
    Node<T> *nn = new Node<T>;
    nn->next = nullptr;
    nn->data = value;

    if (LinkedList<T>::head == nullptr && LinkedList<T>::tail == nullptr) // empty LL
    {
        LinkedList<T>::head = nn;
        LinkedList<T>::tail = nn;
    }
    else
    {
        nn->next = LinkedList<T>::head;
        LinkedList<T>::head = nn;
    }
}