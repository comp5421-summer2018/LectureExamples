#ifndef STACK_H
#define STACK_H

class Stack
{

private:

    // Internal struct member
    struct Node{
        int data;
        Node* next;

        // Default parameters need only be specified in the header file
        // If you have implementation in cpp file you can exclude the default parameter in signature
        Node(int data, Node *next = nullptr): data(data), next(next){}
    };

    Node *head;
    int size;

public:

    Stack();
    Stack(const Stack&);
    ~Stack();

    void operator=(const Stack &);

    void push(int value);
    void pop();
    int top();
    bool isEmpty() const;
};

#endif //STACK_H
