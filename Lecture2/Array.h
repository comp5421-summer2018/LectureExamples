
// Convention for define symbols is CLASSNAME_H

#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

class Array
{

private:
    int *store;
    int length;

public:

    // Can combine both default and parameterized constructor into one using default parameters
    Array(int = 10);
    Array(const Array &other);
    Array& operator=(const Array &);
    virtual ~Array();

    int getLength() const;

    int get(int index) const;

    void set(int index, int value);

    // This should be a friend function instead of a member function
    // Can't be a member function since << is invoked on the ostream, not on the Array object
    friend std::ostream &operator<<(std::ostream &os, const Array &array);

protected:

};


#endif //ARRAY_H
