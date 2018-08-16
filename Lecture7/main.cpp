#include <iostream>
#include <vector>
// Syntax questions
// Access modifiers
// Const checks
// pointer reference
// Dangerous to use x++, ++x multiple times in same statement (undefined behavior)

// OOP Features
// - ADT
// - Inheritance (code re-use)
// - Encapsulation (packaged in a unit, operations and data together in one neat unit)
// - Information hiding / abstraction (what part of class should be exposed or not to client)
// - Polymorphism

// Code re-use methods
// 1) Inheritance
// 2) Composition (more flexible, less coupled since rely on interface and not implementation)

using namespace std;

class MyClass{

private:
    vector<int> vec{11,22,33};

public:

    int get(int) const;

    // Function object operator. Make object behave like a function (function call operator)
    int operator()(int) const;

    double operator()(int i, int j) const{
        return (vec[i] + vec[j])/2.0;
    }
};

int MyClass::operator()(int i) const {
    return vec[i];
}

int MyClass::get(int i) const{
    return vec[i];
}


// Purpose of function operator:
// Given a function want certain local variable to be persisted between function invocations.
// We could make the local variable static OR could use an object with function operator


void countFunction(){
    // Example of static variable in function (NOT RECOMMENDED IN C++)
    // Difficult to document, not free functions responsibility to store state
    static int count = 0;
    cout << "Count is " << ++count << endl;
}

// Alternative using classes
class CountClass{
private:
    int count = 0;
public:
    void operator()(){
        cout << "Count is " << ++count << endl;
    }
};

// ------------------------------------------
// Inheritance
// ------------------------------------------

// Inheritance Modifiers
// class D : public B
// Everything has same access modifiers in derived class
// Note that private members are never visible either way
// D                    B
// private            private
// protected   <-     protected
// public      <-     public


// class D : protected B
// protetected and public are mapped to protected in derived class
// D                    B
// private            private
// protected   <-     protected
// protected   <-     public
// public


// class D : private B
// Everything becomes private in derived class
// D                    B
// private            private
// private     <-     protected
// private     <-     public
// protected
// public

// Why define constructor as private: If members inside class want to use it (such as singleton pattern)
// Assignment: Default copy constructor and assignment operator

// C++: Base
// Java: Super class
class Base{
private:
    int x;
protected:
    int y;
public:
    int z;
};

// C++: Derived
// Java: Subclass
class Derived : Base {

};


class Person{
private:
    string name;
public:
    explicit Person(const string& name): name(name){}

    string getName(){
        return name;
    }
    void setName(const string& name){
        this->name = name;
    }
    virtual void print(){
        cout << name << endl;
    }
};

class Employee : public Person{
private:
    double salary;

public:
    // NOTE: Derived class must call base constructor first.
    // If no constructor specified then will try and call base default constructor
    // If no base defaut constructor, then error will occur
    Employee(const string& name, double salary) : Person(name), salary(salary){
    }

    double getSalary(){
        return salary;
    }
    void setSalary(double value){
        salary = value;
    }

    void print(){
        Person::print();
        cout << salary << endl;
    }

};


class B{
private:
    int x;
public:
    void f(){}
    void f(int a){}
};

class D : public B{
private:
    int x;
public:
    // NOTE: In C++, as soon as we have the same name re-defined in a derived class (even if parameters are different)
    void f(const string& str){}
    B::f;
};

// AUTO Errors
// Missing information for compiler to determine what type of auto is

//void invalid(auto x){}
//
//class AutoExample{
//private:
//    auto x;
//};
//
//auto x[10];

int fFunc(int(&f)[3]){
}


int fun(int x){
    return 1;
}

int main()
{
    D d = {};
    // d.f(10);

    MyClass c;
    cout << c.get(1) << " " << c(1) << endl;
    cout << "Average of first and second elements=" << c(0,1) << endl;

    for(int i = 0; i < 5; i++){
        countFunction();
    }

    CountClass countObj;
    for(int i = 0; i < 5; i++){
        countObj();
    }


    // ----------------------------------------------------
    // AUTO
    // ----------------------------------------------------

    int x = 10;
    auto y = 10, &z = x, *p = &x;       // auto knows that all are integers

    // int a{1.5}, b = "xxx";          // error, not both integers, and {1.5} fails to narrow down to integer because of narrowing


    {
        int w = 10;
        const int u = w;

        const int &k = w;
        int &r = w;
        int*pW = &w;
    }

    // With auto
    {

        int w = 10;
        const auto u = w;

        const auto &k = w;
        auto &r = w;
        auto*pW = &w;
    }

    // Without auto
    {
        const int w = 10;
        int k = w;
        // int& zRef = w;      // ERROR, can't assign const to reference
        const int& wRefConst = w;
    }

    // With auto
    {
        const auto w = 10;
        auto k = w;
        // int &z = w;      // ERROR, can't assign const to reference
        const auto& wRefConst = w;
    }

    vector<int> vec1;
    auto vec2 = vec1;


    {
        Base b;
        Derived d;
        Base &bRef = d;


        // cout << d.z << endl;            // Error, since z public but private inherited
        cout << bRef.z << endl;         // Ok, since base pointer

    }

    {
        int u[10];
        int * v = u;         // int (*)[10]
        auto& w = u;        // int (&)[10]
    }

    {
        auto f = fun;   // int(*)int
        auto & g = fun;  // int(&) int
    }

    {
        int i[3] = {1,2,3};
        int * iPtr = i;
        fFunc(i);
    }

    return 0;
}