#include "Stack.h"
#include <cassert>

// TODO: Can use C++11 {} initialization syntax
Stack::Stack()
        : head{nullptr}, size{0}
{
}

Stack::~Stack()
{
    while(!isEmpty()){
        pop();
    }

    // Alternative:
//    while(head != nullptr){
//        Node *temp = head;
//        head = head->next;
//        delete temp;
//    }
}

Stack::Stack(const Stack & other)
        : head(nullptr), size(other.size)
{
    // Loop from head to add. Push each element of other
    for(Node * itr = other.head; itr != nullptr; itr = itr->next){
        push(itr->data);
    }
}

void Stack::operator=(const Stack & other)
{
    // Delete existing storage
    while(!isEmpty()){
        pop();
    }

    size = other.size;

    // Loop from head to add. Push each element of other
    for(Node * itr = other.head; itr != nullptr; itr = itr->next){
        push(itr->data);
    }
}

int Stack::top()
{
    assert(!isEmpty());
    return head->data;
}


void Stack::push(int value)
{
    Node * newNode = new Node(value, head);

    size++;
    if(isEmpty()){
        head = newNode;
    }else{
        head->next = newNode;
    }
}

void Stack::pop()
{
    assert(!isEmpty());

    Node *temp = head;
    head = head->next;
    delete temp;
    size--;
}

bool Stack::isEmpty() const
{
    return size == 0;
}

/*
Stack::Node::Node(int data, Stack::Node *next)
        : data(data), next(next)
{}
*/
