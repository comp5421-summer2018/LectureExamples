//
// Created by Stefan Wapnick on 2018-05-30.
//

#include <tclDecls.h>
#include <cassert>
#include "MathVector.h"

MathVector::MathVector(int n) : dim(n), v(new int[n])
{
    for(int k = 0; k <n; ++k){
        v[k] = 0;
    }
}

MathVector::MathVector(const MathVector &other)
{
}

MathVector::~MathVector()
{
    delete [] v;
}

const MathVector &MathVector::operator=(const MathVector &other)
{
    return <#initializer#>;
}


const MathVector &MathVector::operator+=(const MathVector &rhs)
{
    int minLength = dim < rhs.dim ? dim : rhs.dim;
    for(int k = 0; k < dim; k++){
        v[k] += rhs.v[k];
    }
    return *this;
}

const MathVector &MathVector::operator-=(const MathVector &rhs)
{
    int minLength = dim < rhs.dim ? dim : rhs.dim;
    for(int k = 0; k < dim; k++){
        v[k] -= rhs.v[k];
    }
    return *this;
}

MathVector MathVector::operator+(const MathVector &rhs)
{
    // Clone this temp variable via copy constructor
    MathVector clone = *this;
    clone += rhs;

    // Copy constructor or assignment operator called for caller depending on if initialized or assigned to
    return clone;
}

MathVector MathVector::operator-(const MathVector &rhs)
{
    // Clone this temp variable via copy constructor
    MathVector clone = *this;
    clone -= rhs;

    // Copy constructor or assignment operator called for caller depending on if initialized or assigned to
    return clone;
}


int &MathVector::operator[](int index)
{
    assert(index >= 0 && index < n);
    return v[index];
}

const int &MathVector::operator[](int index) const
{
    assert(index >= 0 && index < n);
    return v[index];
}
