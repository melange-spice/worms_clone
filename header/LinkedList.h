#pragma once
#include <iostream>
template <typename T>
struct Node
{
    T data;
    Node *next;
    Node *prev;     //doubly linked list
};

template <typename T>
class LinkedList 
{
public: //TODO: protected public only for now
    Node<T> *head;
    Node<T> *tail;

public:
    
    virtual void insertAtHead(T value);
    virtual void insertAtTail(T value);
    virtual bool isEmpty();
    virtual void deleteFromHead();
    virtual void deleteFromTail();
    virtual void delete_node(Node<T>* node);

    LinkedList();
    ~LinkedList();
};

//delete an aribitarty node from the linked list
template <typename T>
void LinkedList<T>::delete_node(Node<T>* node){

    if (node == nullptr)
    {
        std::cout<<"Error: delete_node(T* node) where node = nullptr\n";
        return;
    }
    else if (node == head)
    {
        deleteFromHead();
    }
    else if (node == tail)
    {
        deleteFromTail();
    }
    else{
        //we are in the middle of the linked list
        node->prev->next = node->next;
        node->next->prev = node->prev;

        delete node;
        node = nullptr;
        
    }
    
}

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
        Node<T> *t = tail;
        tail = tail->prev;
        tail->next = nullptr;
       
        delete t;
        t = nullptr;
    }
}

template <typename T>
void LinkedList<T>::deleteFromHead()
{
    if (isEmpty()==true)
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
        head->prev = nullptr;
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
    Node<T> *nn = new Node<T>{value,nullptr,nullptr};
    

    if (head == nullptr && tail == nullptr) // empty LL (first Node<T> to be added)
    {
        head = nn;
        tail = nn;
    }
    else // all the rest values (Nodes)
    {
        tail->next = nn;
        nn->prev = tail;
        tail = nn;
    }
}

template <typename T>
void LinkedList<T>::insertAtHead(T value)
{
    Node<T> *nn = new Node<T>{value,nullptr,nullptr};
    
    if (head == nullptr && tail == nullptr) // empty LL
    {
        head = nn;
        tail = nn;
    }
    else
    {
        nn->next = head;
        head->prev = nn;

        head = nn;
    }
}