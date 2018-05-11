
// Convention for define symbols is CLASSNAME_H

#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

class Array
{
// Default access type for class is private, default inheritance private
// Default access type for struct is public, default inheritance public
// Besides this, struct and class are more or less the same, but struct conventionally used as poco's with no behaviors
private:
    int *store;
    int length;

public:
    // TODO: Preference to include names in method declarations
    Array();

    // Explicit important: https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean
    // Only applies to single parameter constructors
    // Constructor is allowed to use a single parameter constructor when doing implicit conversions
    explicit Array(int);

    // Can combine both into one using default parameters
    // TODO: problem with default parameters?
    // Array(int = 10);

    explicit Array(const Array &other);

    // Assignment operator a = b = c = 10
    // First c = 10 evaluated
    // Then b = (c=10) evaluated
    // Then a = (b=c=10) evaluated

    // Assignment operator that disallows multiple assignments like a=b=c=10
    // void operator=(const Array &other);

    Array& operator=(const Array &);

    ~Array();

    int get(int index) const;

    int set(int index, int value);

    // This should be a friend function instead of a member function
    // Can't be a member function since << is invoked on the ostream, not on the Array object
    friend std::ostream &operator<<(std::ostream &os, const Array &array);

protected:

};


#endif //ARRAY_H
