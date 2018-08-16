#include <iostream>
#include <list>
#include <vector>
#include <deque>
#include <forward_list>

// Process of instantiating template classes
// Instantiation like filling in the blanks when creating a class
// Stack<int, 10> s1            # instantiation 1
// Stack<int, 20> s2            # instantiation 2
// Stack<double, 30> s3         # instantiation 3
// Stack<int, 10> s4            # No instantiation needed

// Note that each instance of Stack<T, int> is a completely seperate class, not related to eachother in any other way
// Compiler will often mangle the names of templated classes that are instantiated such as Stack<int, 10> -> ST1intint
// REVIEW ITERATOR DOCS FOR TEST: http://www.cplusplus.com/reference/iterator/
// Note on iterator hierarchy, larger classes of iterator (such as random access) have everything smallest classes have
//                  For example, random access can input and output

// Test Question: How many iterators exist (5)
// forward, bidirectional, random access, output and input operation

// ITERATOR DEFINITION:     Tour guide to go through a container. May be random access, sequential etc

// Member Types
// Types that exist inside another class

class Foo{

public:
    class Iterator;
    using FooIterator = Iterator;
};


class Base{
public:
    Base(Base & other){
        // b stuff
    }
    Base& operator==(Base & other){

        if(this == &other){
            return *this;
        }

        return *this;
    }

    // VIRTUAL TABLES
    // When you make a new instance of Base, it maintains a table of virtual methods
    // Every object of B has a pointer called a VIRTUAL POINTER that points to the VIRTUAL TABLE
    // 1 virtual pointer per object
    // 1 virtual table per class
    virtual void f();
    virtual int g();
    char h();

};

// TODO: Using statement in derived class will bring down constructors (and destructor?)
// BUT will not bring down assignment operator
class Derived : public Base {
public:
    Derived(Derived& other) : Base(other){
        // d stuff
    }

    Derived& operator= (Derived& other){

        Base::operator==(other);

        if(this == &other){
            return *this;
        }

        // d stuff

        return *this;
    }

    void f() override;

    // VIRTUAL TABLE OF D
    // In virtual table of D:
    // D::f
    // B::g
};

// TODO Inheritance
// D : private B
// C : private D
// D gets the public and protected members of B and they become private in D. NEVER inherits private fields
// C will get nothing from D, because all members in D from B are private

// TODO: Lookup container member types
// Important to use size_t if you want code to be portable when working with containers on different machines

using namespace std;

int main()
{

    list<int> l = {1,2,3};

    // Iterator is NOT a pointer, just has overload for dereference operation
    list<int>::iterator it = l.begin();

    auto it2(it);
    *it = 10;


    // stl container classes
    // Linear               vector, array, forward list (single direction linked list), list (double direction linked list), dequeu (array that can push and pop from both head and rear)
    // Associative          map, multimap, set, multiset        map, multimap -> tree       set, multiset -> hashtable/map
    //                              Multimap and multiset allow for duplicate keys

    // Want to insert only at rear  -> vector or deque, array
    // Efficient push/pop front and back -> dequeu
    // Insert in middle:    Use forwardList, list, vector or array


    // size_type is actually member type on its container class
    vector<int>::size_type i = 1;
    // CAREFUL not to use auto since
    auto j = 1;
    // will make it an int


    // Example, copy the middle 3 elements of vector of size 5
    list<int> l = {1,2,3,4,5};
    vector<int> v(l.begin()+1, l.end()-1);

    vector<int> v2(10);     // vector of 10 ints
    vector<Foo> v3(10);     // vector of 10 foo objects, DEFAULT Constructed
    vector<int> v4(5,99);   // 99 made 5 times          99 99 99 99 99
    v4.resize(7, 77);       // resized to 7 elements, and new spaces are filled with 77         99 99 99 99 99 77 77
    v4.resize(3);           // Resized to 3 elements:       99 99 99
    // TODO: Is 10 value ignored since not growing
    v4.resize(2, 10);

    vector<string> v = {"Hi", "Hello"};
    v.insert(v.end(), "Bye");

    // Same as:
    v.push_back("Bye");

    // NOTE that insertion always occurs before the iterator point

    vector<int> vec = {1,2,3,4,5,6,7,8,9,10};


    auto it3 = vec.begin();
    while(it3 != vec.end()){
        if(*it3 %3 == 0){
            // Note that erase will return a pointer to the next element
            // In this case there is no need to increment the iterator
            it3 = vec.erase(it3);
        }else{
            ++it3;
        }
    }


    {

        list<int> l(vec.begin(), vec.end());
        // remove elements divisible by 5 else insert twice the element at the current location
        auto it = l.begin();
        while(it != l.end()){
            if(*it %5 == 0){
                it = l.erase(it);
            }else{
                l.insert(it, *it*2);
                it += 2;        // need to jump 2 locations to go to the next element
            }
        }

    }

    // Forward list:
    // No insert, no emplace, no erase

    // In forward_list have a special iterator called before_begin() that is before very first element
    forward_list<int> flist = {1,2,3,4,5,6,7,8,9,10};
    // Remove elements that are divisible by 3

    auto prev = flist.before_begin();
    auto curr = flist.begin();
    while(curr != flist.end()){
        if(*curr %3 == 0){
            curr = flist.erase_after(prev);
        }
        else{
           ++prev; ++curr;
        }

    }


    // ALGORITHMS
    // operate on containers. Algorithm knows nothing about containers and vice-versa
    // Work together using iterators
    // TODO: For test know how to interpret algorithm function signatures
    // http://www.cplusplus.com/reference/algorithm/copy/
    // Every algorithm has source range = [start, end)
    // Note that in source range the end iterator IS NEVER included
    // NOTE: When doing copies with algorithms, watch out for size of destination container. Must be >= than source range
    // NOTE: Compiler converts lambda expression to a class
    // TODO: Review http://www.cplusplus.com/reference/numeric/accumulate/ Note that std::minus<int>() is making an object, not calling a function


    return 0;
}