#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

class Shape{
public:
    virtual void print(ostream& out) const = 0;
};

class Triangle : public Shape{
public:
    void print(ostream& out) const override{

    }
};

class RightTriangle : public Triangle{
public:
    void print(ostream& out) const override{

    }
};

// Recommendation: Can just write operator<< free function once
// Then call a public virtual polymorphic function on the class
ostream& operator<<(ostream& out, const Shape & s){
    s.print(out);
    return out;
}



class Animal{
public:
    void speak() const {

    }
};

class Dog : private Animal{

};

void doSomething(const Animal& animal){

}


void makeAnimalTalk(const Animal& animal){
    animal.speak();
}


class Foo{
    vector<int> v;
public:
    Foo() = default;
    Foo(const Foo &) = default;
    Foo(initializer_list<int> list){

        for(const auto & item : list){
            v.push_back(item);
        }
    }

};

// Default inheritance type
// Class has default inheritance of PRIVATE
// Struct has default inheritance of PUBLIC


class Base{
public:
    virtual void someMethod() const{
        cout << "Some method" << endl;
    }
};

// TODO: NOTE: Stuff that is private is never inherited
// Everything protected and above in Base becomes private in D2
class D1 : protected Base{

};

// Everything above private in base becomes private in D2
class D2 : private Base{

};

int twice(int number){
    return 2*number;
}

// TODO: NOTE: Non-templated versions take precedence
// TODO: NOTE: Can't have two templated versions that conflict
bool compare(const int & x, const int & y){
    return x < y;
}

bool compare(const double& x, const double& y){
    return x < y;
}

template <typename T1, typename T2>
bool compare(const T1 & x, const T2 & y){
    return x < y;
}

// May be run time error since conflicts with bool compare(const T1 & x, const T2 & y)???
// TODO: Can also be template<class T> instead of template<typename T>
template <class T>
bool compare(const T & x, const T & y){
    return x < y;
}

// Template Specialization:
// template <class T>
// bool compare(const T & x, const T & y)
template<>
bool compare<char*>(const char* & x, const char * & y){
    return strcmp(x, y) < 0;
}

void fun(){

    compare(1,2);

    int x = 10, c = 100;
    auto f = [x]{return x;};
    x = 100;
    cout << f() << endl;        // 10

    auto g = [&x]{return x;};
    x = 200;
    cout << g() << endl;

    // Capture everything in scope by reference
    auto f1 = [&]{return x;};

    // Capture everything in scope by value
    auto f2 = [=]{return x;};

    // Capture everything in scope by reference
    auto f3 = [&, c]{return x;};

    // Capture everything in scope by reference except for c which is by value
    auto f4 = [&, c]{return c*x;};

    // Capture everything by value exception for x and c by reference
    auto f5 = [=, &x, &c]{return x*c; };
}

// Type Minimization
// Want template to be as flexible as possible
template<typename T>
int compare(const T & x, const T & y){
    if(x < y){
        return -1;
    }

    if(y < x){
        return 1;
    }

    return 0;
}

// Template function instanciation
// Compiler will instanciate one version of template function per type
// compare(1,2)                 -> instanciate compare<int>
// compare(1.0, 2.0)            -> instanciate compare<double>
// compare("Hi", "Hello")       -> instanciate compare<char*>
// compare(3,4)                 -> compare<int> already exists, no need to instanciate new version, re-use
// compare(3.0, 4.0)            -> compare<double> already exists, no need to instanciate new version, re-use


// Type Aliases
// -----------------------------------------------------
typedef int myInt;      // C++ 98
using myInt2 = int;     // C++ 11

// Can even make aliases for generic types
// template<typename T1, typename T2>
// typedef template<int, T> intT;       Doesn't work in C++98

template<typename T1, typename T2>
using intT2 = template<int, T2>;           // Does work in C++11


// Template Classes
// TODO: All templating is compile time
// ------------------------------------------------------------------
// using T = int;
template<typename T>
class Stack{

private:
    T* store;
    int size;

public:
    explicit Stack(int capacity = 10): size(0), store(new T[capacity]){
    }

    void push(const T& item){
        store[size++] = item;
    }

    T pop(){
        T item = store[size];
        size--;
        return item;
    }

    ~Stack(){
        delete store;
    }
};

// Pasing arguments as non-type parameters
// Non-type parameters MUST be an integral type int, char, long (not float or double)
// Can also give a default value
// Must be at trailing end of template because can have defaulted value
// TODO: Creates a seperate type
// TODO: Compilation process
// Does first pass to check basic syntax
// When it arrives at instanciation of object, then compiles version of template for type at compile time
template<typename T, int size = 10>
class StackV2{

private:
    // T* store;
    array<T, size> store;   // Example of using an array first
    // int size;  Don't need this now
    int top = 0;
public:
    StackV2() = default;
    ~StackV2() = default;
    StackV2(const StackV2 other) = delete;
    StackV2 & operator=(const StackV2 &other) = delete;

    void push(const T& item);
    void pop();
    const T getTop() const;

    ~Stack(){
        delete store;
    }
};

template<typename T, int size = 10>
void StackV2<T>::push(const T & item){
    store[top++] = item;
}

template<typename T, int size = 10>
void StackV2<T>::pop(){
    if(top == 0){
        throw "stack underflow";
    }

    --top;
}

template<typename T, int size = 10>
const T &StackV2<T>::getTop() const{
    return store[top];
}

int main()
{

    int size = 100;

    StackV2<double, 100> s1;
    StackV2<double> s2;

    // Doesn't work. All templating must be compile time
    // StackV2<double size> s3;

    // Calls non-templated version
    cout << compare(1,2) << endl;
    // Calls templated version
    cout << compare("Hello", "World") << endl;

    // Call templated version with explicit types
    cout << compare<int, double>(1,2) << endl;


    int number = 100;

    fun();
    cout << "Hello world" << endl;
    Foo f = {1,2,3,4};

    // Base* b = new D2(); Doesn't work since private inheritnance, can't cast to base class
    // b->someMethod();
    D2* b = new D2();

    // NOTE: If doSomething was doSomething(Animal* a)
    // Would not work. Needs a const reference for inline objects
    doSomething(Animal());
    // doSomething(Dog());      // Doesn't work can't cast to base class because private inheritance

    {
        const Shape& a = Triangle();
        const Shape& b = RightTriangle();

        cout << a << endl;
        cout << b << endl;
    }

    vector<int> vec = {1,2,3,4,5};

    // Multiple ways to use function delegates (with and without lambdas)
    // HOW TO USE DELEGATES:
    // 1) Explicitly defined Functions
    // 2) Lambdas
    // 3) Function objects (make a class that overloads operator())
    transform(vec.begin(), vec.end(), vec.begin(), [](const int & item) {return item*2;});
    // With explicit return type
    transform(vec.begin(), vec.end(), vec.begin(), [](const int & item) -> int {return item*2;});
    transform(vec.begin(), vec.end(), vec.begin(), twice);

    // Example of how transform is implemented
    vector<int>::iterator destination = vec.begin();
    int (*functionRef)(int) = twice;
    for(vector<int>::iterator it = vec.begin(); it != vec.end(); it++){
        *destination = functionRef(*it);
        destination++;
    }

    // NOTE: Lambda must always exist inside a scope {}
    // Capturing clause / introducer is defined as the scope {} that the lambda exists in
    {
        int a = 0,b = 0;
        // Immediate call
        [a,b](int x) {return (a+b)*x;}(10);

        // Assign to variable
        // 1) Auto
        auto lambda = [a,b](int x){return (a+b)*x;};
        // 2) Function template class
        function<int(int)> lambda2 = [a,b](int x){return (a+b)*x;};
        // 3) Function pointer Doesn't work
        // int (*lambda3)(int) = [a,b](int x){return (a+b)*x;};


        // LIMITATIONS:
        // Lambdas can't have default values
        // Lambdas can't have unnamed or untyped parameters

    }


    return 0;
}