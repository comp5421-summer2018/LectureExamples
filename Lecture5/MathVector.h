//
// Created by Stefan Wapnick on 2018-05-30.
//

#ifndef LECTURE5_MATHVECTOR_H
#define LECTURE5_MATHVECTOR_H

// Rule:
// 1) When LHS operand is of class type can make member
// 2) If LHS operand is not of class type must make external function

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
    MathVector operator++(int unused){
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

	friend MathVector operator*(const MathVector & lhs, int rhs); 
	friend MathVector operator*(int lhs, const MathVector& rhs); 
};

#endif //LECTURE5_MATHVECTOR_H
