#include <iostream>
#include <vector>
#include "ylib.h"
#include "xlib.h"
#include "MathVector.h"

using namespace std;
struct Node{
    int n;
    Node* next;
};

// First enum = 0
// Second enum = 1
enum {
    min, max
};

// This is the same as:
// const int min = 0;
// const int max = 1;

// Disadvantage of enum: They are equivalent to declaring global scope constants (compiler translates it to the same)

// Named enumeration example
// But still these are treated as globally scoped constants
// Same as const int red = 0; const int yellow = 1; const int green = 2
enum Color{
    red, yellow, green
};

Color c = red;


// This gives an error since red is already defined
//enum TrafficLight{
//    red
//};

// C++ 11 Scoped enumeration
// This makes enumerations scoped
enum class Traffic{
    red, yellow, green  // 0,1,2
};

Traffic t = Traffic::red;


// Enum Types
// By default enums are encoded as integers
// But can encode as a different value
// --------------------------------------------
enum class Letters : char {
    A = 'A',
    B = 'B',
    C = 'C',
};

Letters letter = Letters::A;


// Namespaces
// --------------------------------------------
//namespace xlib{
//    void f(int);
//    int max = 100;
//}
//
//
//namespace ylib{
//    void f(int);
//    void g();
//    const int max = 200;
//}

int main()
{
    // h -> (10) -> (20) -> (30)
    // Question 1: Swap values in nodes 20, 30
    // -------------------------------------------
    Node n1{10};
    Node n2{20};
    Node n3{30};
    Node* head = &n1;
    head->next = &n2;
    head->next->next = &n3;

    // Swap 20 and 30 contents
    int temp = head->next->n;
    head->next->n = head->next->next->n;
    head->next->next->n = temp;

    // Question 2: Copy elements 2 to 4 into a vector
    // -------------------------------------------
    int a[] = {1,2,3,4,5};
    vector<int> a_vector(a+1, a+4);

    // Question 3: Given vector b, swap first two elements
    // -------------------------------------------
    {
        vector<int> b{1,2,3,4,5};
        int temp = b[0];
        b[0] = b[1];
        b[1] = temp;
    }

    // Question 4: Swap first and 2nd element in vector using iterators
    // -------------------------------------------
    {
        vector<int> b{1,2,3,4,5};
        cout << *b.begin() << endl;
        cout << *b.end() << endl;       // NOTE that end points to one element after the last

        // NOTE: Iterators here are not pointers, just regular variables with * overload
        vector<int>::iterator it = b.begin();
        vector<int>::iterator it2 = b.begin()+1;
        int temp = *it;
        *it = *it2;
        *it2 = temp;
    }

    // Using namespaces
    // -------------------------------------------

    // Method 1: Set your default namespace to the default that you want to us
    // Method 2: Prefix everything with ylib:: and xlib::

    {
        using namespace ylib;
        // By default from ylib
        f(10);

        // To access xlib version need to prefix with namespace
        xlib::f(20);
    }

    // Can also resolve a specific element in a namespace:
    {
        using xlib::f;
        f(10);
    }

    // Recommendation:
    // In header files best to specifically reference elements
    // Example:
    using std::cout;
    using std::endl;

    // BUT don't do 'using namespace std;' because everything that header is included in will have this line.


    // Operator Overloading
    // 1) Can overload all operators except:
    // ::   ?:    .   .*
    // (? : is the ternary operator)
    // Besides this, all other operators can be overloaded
    // 2) Cannot introduce new operators
    // 3) Cannot change the 'arity' on operators
    //      If operator is binary must remain binary, etc
    //      + / - are both unary and binary
    // Recommendation: If you overload any inequality operators
    // should overload them all (=, !=, >, <, etc)
    // But if you have at least one of =, != and one from >, <, >=, <= can
    // do them all
    // -------------------------------------------


    return 0;

}