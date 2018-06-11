//
// Created by Stefan Wapnick on 2018-05-30.
//

#include <cassert>
#include "MathVector.h"
#include <initializer_list>

MathVector::MathVector(int n) : dim(n), v(new int[n])
{
    for(int k = 0; k <n; ++k){
        v[k] = 0;
    }
}

MathVector::MathVector(const MathVector &other) : dim(other.dim), v(new int[other.dim])
{
	for (int i = 0; i < dim; i++)
	{
		v[i] = other.v[i];
	}
}

MathVector::~MathVector()
{
    delete [] v;
}

const MathVector &MathVector::operator=(const MathVector &other)
{
	if (this == &other)
	{
		return *this;
	}

	delete[] v;
	dim = other.dim;
	v = new int[dim];
	for(int i = 0; i < dim; i++)
	{
		v[i] = other.v[i];
	}
	return *this; 
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
    assert(index >= 0 && index < dim);
    return v[index];
}

const int &MathVector::operator[](int index) const
{
    assert(index >= 0 && index < dim);
    return v[index];
}


MathVector operator*(const MathVector& lhs, int rhs) {

	MathVector clone = lhs;
	for (int i = 0; i < clone.dim; i++) {
		clone.v[i] *= rhs;
	}
	return clone;
}

MathVector operator*(int lhs, const MathVector& rhs) {
	return rhs * lhs;
}