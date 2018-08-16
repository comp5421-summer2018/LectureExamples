#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>

// Static advantages and disadvantages

// Avoid static function members
// Difficult to debug, not flexibile (Consider fib function. What if we wnat ot mainta multipe states. But only have one function so only single state possible)

// Advantages of OOP:
/*
 * ADT
 * Encapsulation
 * Information Hiding
 * inheritance
 * Polymorphism
 */

// UML class diagrams
// A - - - - > B            A depends or uses B in a loose sense (not as a member). May be instanciated and used in a method, but not as a field.
// A -----> B               Association: A has a reference to B through one of its data members
// A ---- B                 Association: A and B are associated. A knows of B. B knows of A
// A <>----- B              A aggregates B, but A is not made from B (B exists even after A is destroyed)
// A <solid>-----B          A is composed of Bs. B is required for A's existence. A cannot exist with B. If A is destroyed B is destroyed too.

// TODO:    For test: Template class Minus

using namespace std;

int fib(){
    static int fib0 = 0;
    static int fib1 = 1;

    int temp = fib1;
    fib1 = fib1 + fib0;
    fib0 = temp;
    cout << fib1 << " " << fib0 << endl;
}

class B{
public:
    B(){
        cout << "B" << endl;
    }

    // Important:   Base destructor should be virtual to support overriding.
    // If not virtual, then if we do B * pb = new D();
    // delete pb;       Only the destructor of B is will be called and not D -> BUG
    virtual ~B(){
        cout << "~B" << endl;
    }
};

class D : public B{
public:
    D(){
        cout << "D" << endl;
    }
    ~D(){
        cout << "~D" << endl;
    }
};


// To maintain state, it is better to use an object instead of static in a method
class Fib{

private:
    int fib0 = 0;
    int fib1 = 1;
public:
    Fib() = default;

    // Overload the function call operator so that it can be used as a function would be used.
    int operator()(){
        int sum = fib0 + fib1;
        fib0 = fib1;
        fib1 = sum;
        return fib1;
    }

};


// Method overloading can also be considered polymorphism but is **static polymorphism / static binding / compile time binding**
int someFunction(int a);
int someFunction(char* c);

class Shape{
private:
    string name;
public:
    Shape(const string & name): name(name){}
    virtual double area() = 0;
};

class Rectangle : public Shape{
private:
    double width;
    double height;

public:

    Rectangle(double width, double height): Shape("Rectangle"), width(width), height(height){}

    double area() final override {
        return width*height;
    }
};

class Circle : public Shape{

private:
    double radius;

public:
    Circle(double radius) : Shape("Circle"), radius(radius){}
    double area() final override {
        return M_PI * pow(radius,2);
    }
};


void printArea(Shape* s){
    cout << s->area() << endl;
}

// Can use pointers or references polymorphic behavior
void printArea(Shape & s){
    printArea(&s);
}

// ------------------------------------------------------------------
// Forward delcaration. Declare prototype without any definition
// ------------------------------------------------------------------

class MyClass;              // Class prototype

// MyClass a;                  // Error -  Trying to create a with default constructor but no defintion.
MyClass* aPtr = nullptr;    // Ok - Since not constructor needs to be called yet

// ------------------------------------------------------------------
// Know inheritance method keywords
// ------------------------------------------------------------------
// - virtual
// - override
// - final

// ------------------------------------------------------------------
// Requirements for polymorphism
// ------------------------------------------------------------------
// - pointer or reference
// - virtual
// - inhertiance

class Base{
public:
    // Even if Base() default constructor is provided implicitly, always best to make it explicit and mark it as default
    Base() = default;
    Base (int d) = delete;
    Base(double d) = default;
    Base& operator=() = delete;
};

class Derived : public Base{
public:
//    Derived() : Base() {}
//    Derived(double d): Base(d){}

    // Can instead write using Base::Base; to inherit all constructors and destructors from Base
    using Base::Base;
};

class A;
class B;

// Wrong, impossible to know what auto is supposed to map to at this point
// Since compiler hasn't seen A or B yet
auto perform(A a, B b);

// Working version
auto performCorrect(A a, B b) -> decltype(a*b);
// TODO: decltype(auto)

int main()
{
    cout << "In main" << endl;

    Fib f1;
    Fib f2;
    cout << 0 << endl;
    for(int i = 0; i < 10; i++){
        cout << f1() << endl;
    }

    cout << 0 << endl;
    for(int i = 0; i < 5; i++){
        cout << f2() << endl;
    }

    {
        B b1;
        D d1;
        {
            D d2;
        }

        // b1 B ctor
        // d1 B ctor
        // d1 D ctor

        // d2 B ctor
        // d2 D ctor

        // d2 D dtor
        // d2 B ctor

        // d1 D dtor
        // d1 B dtor
        // b1 B dtor
    }


    {
        B b;
        D d;

        // Ok
        b = d;      // D part of d will be sliced out when copying to b

        // Not ok
        // d = b;   // What will d part of d be assigned to
    }

    {
        B* pb = new D;
        // Dynamic binding used here for polymorphic behavior

        delete pb;          // ~D, ~B
        // delete pb;          // If not virtual: ~B

        // To use polymorphism or virtual methods must have a pointer OR reference
    }

    {
        // Every variable has a static type of a dynamic type
        // static type of s = Shape
        // Dynamic type of s = Rectangle
        Shape * s = new Rectangle(4,5);

        cout << s->area() << endl;
    }

    {
        Circle c = Circle(3);
        Rectangle* r = new Rectangle(1,2);
        printArea(r);
        printArea(c);
    }


    // TODO: Exam: Write you own template math operator function and use it
    {
        minus<int> m;
        cout << m(4,5) << endl;
        plus<int> p;
        cout << p(4,5) << endl;
    }

    {
        Derived d(10);
    }

    {
        // Base b1(10);        // Doesn't work, deleted
        Base b2(11.9);      // Works
        Base b3;            // Works
        // b3 = 10;            // Doesn't work, deleted
    }

    {
        int x;
        auto xAuto = 10;

        // ===============================================
        // Using decltype to get the type
        // ===============================================
        vector<int> d;
        decltype(d) b;
        b.push_back(100);

        decltype(2*5) someInt = 25;
        decltype(2/5) someInt2 = 25;        // still int, 2/5 results in an int
        decltype(2/1.0) someDouble2 = 25;   // Double since 1.0 promotes 2 to a double
        int x = 10;

        // NOTE: This will not actually perform the operation. X will still be 10.
        // decltype just tries to loop at the result of the expression to determine the type from it
        // BUT will not actually perform the operation
        decltype(x++) y = 20;
        cout << x << endl;      // x is still 10
    }
    return 0;
}