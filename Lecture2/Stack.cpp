#include "Stack.h"
#include <cassert>

Stack::Stack()
    : head{nullptr}, size{0}
{
}

Stack::~Stack()
{
    while(!isEmpty()){
        pop();
    }
}

Stack::Stack(const Stack & other)
        : head(nullptr), size(0)
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
    head = newNode;
    size++;
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
