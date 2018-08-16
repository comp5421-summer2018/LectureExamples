#include <iostream>
#include "Array.h"
#include "Stack.h"

using namespace std;

class Point{

private:
    int x;
    int y;
public:
    Point(int x, int y) : x(x), y(y)
    {}

	Point& operator+=(const Point& other)
    {
		x += other.x;
		y += other.y;
		return *this; 
    }

    Point operator+(const Point& b) const{
        Point p = Point(x+b.x, y+b.y);
        return p;
    }

    friend ostream &operator<<(ostream &os, const Point &point)
    {
        os << "(" << point.x << "," << point.y << ")";
        return os;
    }

};



int main()
{

    /* --------------------------------------
     * Simple point class
     * --------------------------------------*/
    Point a = Point(1,2);
    Point b = Point(2,3);

    Point c = a + b;
    cout << a << "+" << b << "=" << c << endl;


    /* --------------------------------------
     * Which constructors are called
     * --------------------------------------*/

    // If we do not provide our own copy constructor, compiler will use default version
    // Default copy constructor does shallow copy

    // Calls default (no parameters) constructor
    Array a11;
    Array a12{};            // alternative
    Array a13 = Array();    // alternative

    // Calls parameterized constructor
    Array a21(100);
    Array a22 = Array(100); // alternative

    // Calls copy constructor (when declaring)
    Array a3 = a21;
    Array a4(a21);
    Array a5{a21};

    // Calls copy assignment operator
    a11 = a21;

    Array a6;       // default constructor
    a6 = a21;        // copy assignment operator


    /* --------------------------------------
     * Testing Array functionality
     * --------------------------------------*/

    Array testArray(10);

    cout << "Printing array: ";
    for(int i = 0; i < testArray.getLength(); i++){
        testArray.set(i, i);
        cout << testArray.get(i) << " ";
    }
    cout << endl;

    cout << "Using << overload: " << testArray << endl;


    /* --------------------------------------
     * Testing Stack functionality
     * --------------------------------------*/

    Stack s1;
    cout << "s1 is empty: " << s1.isEmpty() << endl;

    s1.push(10);
    s1.push(12);
    s1.push(13);

    cout << "s1 top: " <<  s1.top() << endl;
    cout << "s1 is empty: " << s1.isEmpty() << endl;

    Stack s2(s1);

    while(!s1.isEmpty()){
        cout << s1.top() << " ";
        s1.pop();
    }
    cout << endl;

    cout << "s1 is empty: " << s1.isEmpty() << endl;
    cout << "s2 is empty: " << s2.isEmpty() << endl;

	// system("pause"); 

    return 0;
}