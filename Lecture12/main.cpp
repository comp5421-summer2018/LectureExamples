#include <iostream>
using namespace std;

class Lambda{
private:
    int x;
public:

    explicit Lambda(int x): x(x){
    }

    void operator()(double a) {
        cout << a << endl;
    }

};


class B{
public:
    virtual ~B(){
    }
    virtual void f1(){
    }
    virtual char f2(int){
    }
    virtual void f3(){
    }
    void f4(){
    }
};

class D : public B{
public:
    // virtual is not required here
    // override is also not required, but should always include it to ensure that we are actually overriding
    void f1() override{
    }
    void g(){
    }
    void f3() override{
    }
};

// B virtual table
// -----------------
// B::f1
// B::f2
// B::f3
// B::~B

// D virtual table
// -----------------
// D::f1
// B::f2
// D::g
// D::f3

// Dynamic Casts
// -------------------------------------------------------------------
void dynamicCastExample(B & b){

    try{
        D d = dynamic_cast<D&>(b);
    }catch (std::bad_cast & e){

    }
}

void dynamicCastPointerExample(B * b){

    // No exception will be thrown here.
    // Instead will return null or non null
    if(D* d = dynamic_cast<D*>(b)){
        cout << "Cast successful" << endl;
    }else{
        cout << "Could not cast" << endl;
    }
}

// noexcept indicates to the developer that method throws no exception
// However it is not checked by the compiler
// Will still build and run even if we do actually throw an exception
void h() noexcept {
    int *p = new int(10);
    // Throws divide by 0 exception

    int d = 0;
    if(d == 0){
        // Avoid throwing a pointer. Use by reference instead
        throw runtime_error("Division by 0");
    }

    // int y = 1/0;
    delete p;
}

void g(){
    int x = 10;
    h();
}

void f(){
    try{

        int a = 10, b = 20;
        g();

    }catch (B& b){
        // Can modify and rethrow
        b.f2(10);
        throw;
    }catch (const int& e) {


        // Exception is base class for exception classes
        // However note that in c++ can throw anything, so catching exception does not cover everything
        // Common exceptions that inherit from exception
        // - runtime_error
        // - logic_error
        // - out_of_range
        // - invalid_argument
        // - bad_cast
        // - overflow_error
    }catch(const exception & e){

        cout << e.what() << endl;


        // Catch all block
    }catch (...){

        // re-throw exception
        throw;
    }

}

// UNIQUE POINTER:  Exclusive ownership
// Any assignment of pass by value will call move on object to transfer all resources to new object
// Old object will be unusable afterwards
// NOTE: Move does not do a copy. Just transfers resources to new location in address, leaving old location empty

// SHARED POINTER:  Allows shared ownership
// Shared pointers maintain a control block that is shared among all instances that point to the same address
// When one shared pointer goes out of scope or is set to null, Reference Count decreases by 1
// When reference count is 0, raw pointer will be deleted.

// WEAK POINTER:    Act as a shared pointer but DO NOT contribute to the reference count
// Use Case:        Use when you have a cycle

// NOTE: No copy is made here because unique pointer uses move semantics when assigning
// The resources of unique_ptr are simply copied to its new variable location
unique_ptr<double> makePointer(double d){
    return unique_ptr<double>(new double(d));
}

// FINAL TOPICS
// ------------------------------------------------------------------------
// - A3, A4, A5
// - All lectures after midterm
// - Multiple choice questions
// - Inheritance, ctor, dtor (order of ctor and dtor), polymorphism (virtual tables, functions), friend members
// - Overloading, container classes, stl algorithms, iterators (5 kinds)
// - auto
// - exceptions
// - smart pointers
// - move semantics, rvalue and lvalue
// - code tracing question (what does following output)
// - Write a program: object oriented practices

void problemExample(){
    // NOTE: In order to properly shared a pointer, we must use the assignment operator or copy constructor
    // when creating new shared pointers
    int * p = new int(10);
    shared_ptr<int> sp1(p);         // Ref count = 1
    shared_ptr<int> sp2(p);         // Ref count = 1
    // PROBLEM:     sp2 goes out of scope, reference count 0, deletes p
    //              when sp1 goes out of scope, will call delete p again, and cause program to crash
}

class Rectangle{

private:

public:
    int getHeight() const;
    int getWidth() const;
    int getArea() const;

};

class RectLand : public Rectangle{
private:
    double costPerSquareMeter;
public:
    double getCost(){
        // NOT return costPerSquareMeter * getHeight() * getWidth();
        return costPerSquareMeter * getArea();
    }
};


int main()
{
    cout << "Hello, World!" << endl;

    // Closure simply refer to the environment lambda itself
    int x = 10;
    auto f = [x](double a){cout << a << endl; };

    // Compiler will transform the lambda into a class and object instance (see Lambda class above)

    // TODO: Never call desctructor explicitly. It is done automatically
    // If we call it ourselves, possible that cleanup will be done twice
    B b;
    // b.~B();         // Avoid, done automatically

    // R-value, anything where we cannot immediately get the address of
    {
        int x;      // not an R value
        int b = 3;  // &b not allowed, R value
        int y = x + 10;     // &(x+10) & cannot be applied. it is an R-value
    }

    // Move semantics:  Simply turns the variable into an R value

    return 0;
}