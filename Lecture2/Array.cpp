#include "Array.h"
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

// Can do initialization in body of constructor
// But prefer to do it in initialization list
//Array::Array(int length)
//{
//    store = new int[length];
//    this->length = length;
//}

// Constructor with initialization list instead (preferred)
Array::Array(int length)
        : store(new int[length]), length(length)
{
}

Array::Array(const Array &other)
{
    length = other.length;
    store = new int[length];
    for(int i = 0; i < length; i++){
        store[i] = other.store[i];
    }
}

Array &Array::operator=(const Array &other)
{
    // Self assignment guard important
    if(this == &other){
        return *this;
    }

    delete [] store;

    this->length = other.length;
    (*this).length = other.length;

    store = new int[length];
    for(int k = 0; k < length; k++){
        store[k] = other.store[k];
    }

    return *this;
}


int Array::get(int index) const
{
    assert(index >= 0 && index < length);
    return store[index];
}

void Array::set(int index, int value)
{
    assert(index >= 0 && index < length);
    store[index] = value;
}

Array::~Array()
{
    delete []store;
}

ostream &operator<<(ostream &os, const Array &array)
{
    for(int i = 0; i < array.length; i++){
        cout << array.store[i] << " ";
    }
    cout << endl;
    return os;
}

int Array::getLength() const
{
    return length;
}
