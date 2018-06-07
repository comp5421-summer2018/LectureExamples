#include <iostream>
#include <list>

using namespace std;
// Exam Questions:
// Chapters 8,9,10  ->  Questions found on end of chapter, software engineering observations (optimizations, performance tips)   (pointers, classes, operator overloads)
// 10 true / false, 20 multiple choice, given following program segment give output

// 1) Operator overloading (10%)
// 2) Copy constructor, assignment operator, destructor when called. Assignment operator only called once both are defined (vec v = *this calls copy constructor)
//      Put print statements in each to see what is called when. Calling methods, local copies going out of scope
//      What is output of following given prints in constructor, copy constructor, assignment operator, destructor
//      vec a {1,2,3};          // consructor
//      vec b = a;              // copy constructor
//      {
//          vec c(a);           // copy constructor, destructor
//      }
//                              // b, c destructor      (order is based on stack)
// 3) Prefix vs postfix syntax (postfix takes a dummy argument)
//      Why return a reference for prefix, copy for postfix (want to freeze copy of state)
//      x = ++y     =       y = y + 1; x = y;
//      x = y++     =       x = y; y = y+1;

// Question: why do you need const index operator overload and non-const index operator overload
// Because if we have a const variable or are in a const method, can only call other const methods, so need const version
// NOTE: can still update an index position even with const operator? -> check notes
// ONLY pointers and references returned from functions can act as L-Values in subsequent assignment
// a[0] = 2;        [] operator must return a reference to an int
// NOTE: In notes, all simple arithmetic operators can be implemented as member or friend functions. Can be friend because
// returns object of same type
// To have member implementation LHS must be of same type as calling class
// unary/binary operator as member = no arguments, 1 argument (since this passed implicitly)
// unary/binary operator as friend = 1 argument, 2 arguments
// Can always have at most 2 operands, except for ? : (ternary operator)
// Default value need only appear on the prototype. Same with const

// Passing const reference primitives generally overkill

// Exact meanings of const return, const on method (on rhs)

// Using existing operator overloads to implement related overloads:    have v1 > v2, to implement v1 < v2, just call v1<v2 -> v2>v1

// Pointer vs reference: pointer can be changed, reference cannot be set to something else once bound

// Mistake in operator-, modifies existing instance.
// Should negatve a copy of the object, not modify the object then return a copy

// Calling operator++ explicitly:
//      ++a     ->      a.operator++();
//      a++     ->      a.operator++(0);


class Bar{

public:
    explicit Bar(int){

    }
};

class vec{



public:

    // Previously we could do vec{1,2} and it would call this constructor but with initiation list will
    // always call constructor with initialization list when using vec {...} syntax
    vec(int x, int y){

    }

    // Adding this constructor gives us support for vec{1,2,3,4,5,6} initialization
    vec(std::initializer_list<int> initializer_list){

    }
};

struct Node{
    Node *next;
    int data;
};

class Foo{
private:
    int x = 10;

public:
    ostream & operator<<(ostream& out) const{
        out << x << endl;
        return out;
    }
};

void removeFirstNode(){
    Node *first;
    Node *last;

    if(first == nullptr){
        cout << "Empty list" << endl;
        exit(1);
    }

    Node* nodeToDelete = first;
    first = first->next;
    delete nodeToDelete;

    // List is empty
    if(first == nullptr)
        last = nullptr;

    // Ensure that first and last are nullptr at the end
}

int main()
{
    Foo f;
    f << cout << "Test" << endl;

    // Or:
    f.operator<<(cout);

    vec v {1,2};

    std::cout << "Hello, World!" << std::endl;

    // CHAPTER 8 Questions - Pointer questions:
    // understand usage of const variables, const functions,  const parameter, const returns

    // calling function ->  passing arguments by (value, reference pointer)
    // Arrays + Pointers a[k] ==    *(a + k)
    // k[a] == *(k+a)

    // a[i][j] = *(*(a + i) = j)
    // given array a = {0,1,2,3,4}
    // Define pointer to index 3 element      -> int*p = a + 3;
    // Use subscript operator               int*p = &a[3]
    // Pointer arithmatic only for addition and subtraction

    // *p++     order of operations *(p++)
    // *++p                         *(++p)

    // Pointers are not the same as arrays: https://stackoverflow.com/questions/17908462/assigning-pointers-to-arrays-in-c
    // Array head is a pointer
    int x = 10;
    int *q = &x;
    int **p = &q;
    int ** r = new int*[3]();          // Array of 3 pointers to ints

    r[0] = new int(10);
    r[1] = new int(20);
    // On stack
    // p -> q -> x (10)
    // r -> [ptr][ptr][ptr]
    //      ->(10) ->(20)


    // What's wrong with this:
    Bar b1(10);
    // Bar b2 = 10;        // This is what's wrong because explicit


    // PROGRAMMING QUESTIONS
    // Given assignment 1 format:   write code to iterate through list, remove an item, insert an element at start of array
    // Or some other operation from assignment 1

    // Code to delete first code

    return 0;
}