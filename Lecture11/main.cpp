#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <list>

using namespace std;
using namespace std::placeholders;

// Allocator = custom implementation for new and delete (overload for new and delete)
// For example if we rapidly new and delete elements, might be more efficient to allocate and delete on batch instead of 1 by 1.
// Or to re-use

// Conversion Constructor
// ----------------------------------
class Orange{

};

class Foo{

public:
    // Conversion Constructor
    Foo(Orange o){

    }
};

class Person{

public:
    Person(const string & firstName, const string& lastName){

    }

    void showPerson(){

    }

};


void f(int a, char c, double d, const string & s, bool b){
    cout << a << c << d << s << b << endl;
}

int main()
{
    std::cout << "Hello, World!" << std::endl;

    map<char,int> testMap;

    // Watch out! If item does not exist in the map, it will be initialized using the default constructor upon first access
    if(testMap['a'] == testMap['b']){
        cout << "True" << endl;
    }

    for_each(testMap.begin(), testMap.end(), [](pair<char, int> kv){cout << kv.first << " " << kv.second << endl; });

    map<Person, string> phoneBook;

    // Insert new value
    auto check = phoneBook.insert(make_pair(Person("Joe", "Jones"), "123-456-7889"));

    Person p = Person("Joe", "Jones");
    phoneBook[p] = "123-456-7889";

    // Does not work, requires make_pair
    // phoneBook.insert(Person("Joe", "Jones"), "123-456-7889");

    // Object returned by insert is a pair where pair.first = key inserted. pair.second = if insertion successful
    if(check.second){
        cout << "Inserted successully!" << endl;
    }else{
        cout << "Insertion failed!" << endl;
    }

    cout << "Key that was inserted = " << check.first << endl;

    auto iter = phoneBook.find(p);
    if(iter == phoneBook.end()){
        cout << "Not found" << endl;
    }else{
        cout << "Found" << endl;
    }

    // Set VS Map: Map is a mapping of key value pairs. Set is just a set of elements
    // Set = no duplicates
    // Multiset = allows duplicates

    // Sorting:     Note that set and multiset will sort items by default because they are imeplement as a tree

    // Easy way to sort a vector: Insert all into a multiset and then put it back into a vector
    {
        vector<int> vec{14,19,-4,6,5};
        multiset<int> s3(vec.begin(), vec.end());
        copy(s3.begin(), s3.end(), vec.begin());
    }

    // Given a vector<int> v4, write a single statement to copy v4 to an empty list

    {
        vector<int> v4{1,2,3,4,5};
        list<int> ls;

        // copy(v4.begin(), v4.end(), ls.begin());      WILL NOT WORK because list is empty.

        // Instead can use a back_inserted
        copy(v4.begin(), v4.end(), back_inserter(ls));

        // Types of inserters:
        // back_inserter<int>(ls)
        // front_inserter<int>(ls)
        // insert_inserter<int>(ls, ++ls.begin())   // Insert at an arbitrary location
    }

    {
        // Example of binding to change an function reference of 5 arguments to 2 arguments
        auto fn = bind(f, _1, 'x', _2, "ABC", true);
        // fn(10, 12.5);
    }


    // Functor = Function Object
    // TODO: Look at negate function object
    // TODO: Look at remote and replace aglorithm all versions

    {
        list<int> l;
        vector<int> v = {1,2,3,4,5};
        transform(v.begin(), v.end(), back_inserter(l), negate<int>());
        // TODO: Can't do front_inserter if container does not support push_front
        // list supports push_front but list does not support push_back
    }

    {
        istream_iterator<double> eos;
        istream_iterator<double> start(std::cin);

        double input;
        if(start != eos){
            input = *start;         // Like cin >> input
        }

        start++;
        if(start != eos){
            input = *start;         // Like cin >> input
        }

    }

    {
        auto start = istream_iterator<int>(cin);
        auto finish = istream_iterator<int>();
        copy(start, finish, [](int x){cout << x << endl; } );

        auto outputStream = ostream_iterator(std::cout, ", ");
        copy(start, finish, outputStream);
    }

    // Casting
    // ------------------------------------------------------------
    {
        // C-style casts, avoid
        int a = int(1.5);
        int b = (int)1.5;

        // C++ Named casts. 4 of them

        // 1) Static Cast
        // Static cast. Compiler already knows how to do int to double
        double d = static_cast<double>(16);

        // Static cast with object. Compiler doesn't know how to do Orange -> Foo. Will look for Conversion constructor on Foo
        // If no conversion constructor will crash
        Foo f = static_cast<Orange>(Orange());

        // 2) Const Cast
        // Removes the const
        const char* pch;
        char* qch = const_cast<char*>(pch);

        // 3) Re-interpret cast
        // Re-interprets bytes at memory location as the specified type.
        // No compile time checking or runtime checking
        // Will not throw an error if it fails
        // Will just re-interpret bits at location without checking. Very dangerous
        double d = reinterpret_cast<double>(12);

        // 4) Dynamic cast

    }



    return 0;
}