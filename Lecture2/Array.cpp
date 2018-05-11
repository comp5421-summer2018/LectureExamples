#include "Array.h"
#include <iostream>
#include <string>
#include <cassert>

// Can include using namespace here but NOT in header file
using namespace std;

Array::Array()
{

}

// Can do initialization in body of constructor
// But prefer to do it in initialization list
//Array::Array(int length)
//{
//    store = new int[length];
//    this->length = length;
//}

// Constructor with initialization list instead (preferred)
// TODO: Benefits of initialization lists https://stackoverflow.com/questions/1598967/benefits-of-initialization-lists
// Can initialize references, const members
// Objects will have their copy constructor called and then use assignment operator
// Initialization list will just call the copy constructor (more efficient)
// Initialization in body thus may do unneccesary assignments
Array::Array(int length) : store(new int[length]), length(length)
{
    delete [] store;

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

    // Example of using this
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
    // TODO: assert, change assignment
    assert(index < 0 || index >= length);
    return store[index];
}

int Array::set(int index, int value)
{
    assert(index < 0 || index >= length);
    store[index] = value;
}


// Efficient in this case for method to be inline
// TODO: NOTE: All contents in header file will be inlined
inline Array::~Array()
{
    delete []store;
}

ostream &operator<<(ostream &os, const Array &array)
{
    os << "store: " << array.store << " length: " << array.length;
    for(int i = 0; i < array.length; i++){
        cout << array.store[i] << " ";
    }
    cout << endl;
    return os;
}
