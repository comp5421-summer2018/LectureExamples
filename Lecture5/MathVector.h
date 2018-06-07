//
// Created by Stefan Wapnick on 2018-05-30.
//

#ifndef LECTURE5_MATHVECTOR_H
#define LECTURE5_MATHVECTOR_H

// Rule:
// 1) When LHS of operator overload is modified, make a member
// 2) When LHS of operator returned is the type of the class itself, make it part of the class
// Else, make it a free friend function
// 3) To be overloaded, LHS must be of class type

class MathVector
{
private:
    int dim;
    int *v;         // Our internal storage is an array

public:

    explicit MathVector(int =2);
    MathVector(const MathVector & other);
    ~MathVector();

    // Here const reference just means we can't do (a = b) = c
    // But can do a = b; a = c;
    const MathVector& operator=(const MathVector& other);
    const MathVector& operator+=(const MathVector& rhs);
    MathVector operator+(const MathVector& rhs);
    const MathVector& operator-=(const MathVector& rhs);
    MathVector operator-(const MathVector& rhs);

    // TODO:
    // ++x      -> returns a reference to x
    //          Can do (++x) + 2;
    // x++      -> just returns the operator
    //          Can't do (x++) = 2
    // y = ++x      ->  x = x + 1; y = x;
    // y = x++      ->  y = x; x = x + 1;
    // Prefix ++ operator
    MathVector& operator++(){
        for(int i = 0; i < dim; i++){
            v[i]++;
        }
        return *this;
    }

    // Postfix ++ operator
    MathVector& operator++(int unused){
        MathVector temp(*this);
        ++(*this);
        return temp;
    }

    // We define two operator overloads for the index operator [] to support const MathVector and MathVector classes
    int & operator[](int index);
    const int & operator[](int index) const;

    int getDim() const{
        return dim;
    }

    // Implement - operator overload as a free function
    // We can also remove the friend and just make it as a free function
    // Compiler will find it nonetheless.
    //
    // friend MathVector operator-(const MathVector& lhs, const MathVector& rhs);
    // friend MathVector operator-(const MathVector& v);

    // TODO: Why const & here?
    // & because want to preent copy overhead
    // const because want to prevent manipulation
    // However in general we do not pass primitives by reference,
    //  though here we could do const int & n
    // TODO: v*= 5 should be implemented as a method. Would normally implement v=* 5 first then do others in terms of this
    friend MathVector operator*(const MathVector & lhs, int n);
};


MathVector operator*(const MathVector& lhs, int n){

    MathVector clone = lhs;
    for(int i = 0; i < clone.n; i++){
        clone.v[i] *= n;
    }
    return clone;
}

MathVector operator*(int n, const MathVector& lhs){
    return lhs * n;
}

#endif //LECTURE5_MATHVECTOR_H
