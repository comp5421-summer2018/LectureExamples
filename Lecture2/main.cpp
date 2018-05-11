#include <iostream>
#include "Array.h"

using namespace std;

class Point{

private:
    int x;
    int y;
public:
    Point(int x, int y) : x(x), y(y)
    {}

    Point operator+(Point& b){
        Point p = Point(x+b.x, y+b.y);
        return p;
    }

    friend ostream &operator<<(ostream &os, const Point &point)
    {
        os << "x: " << point.x << " y: " << point.y;
        return os;
    }

};



int main()
{
    int x1 = 1;
    int x2 = 3;
    int result = x1+x2;

    Point a = Point(1,2);
    Point b = Point(2,3);

    Point c = a + b;
    cout << c << endl;

    cout << "Hello, World!" << endl;

    // Calls constructor automatically
    Array a1;
    Array a2(100);

    // Copy constructor (when declaring)
    Array a3 = a2;
    Array a4(a2);
    Array a5{a2};

    // If we do not provide our own copy constructor, compiler will use default version
    // Default copy constructor does shallow copy
    // If we have a pointer member or array will copy addresses
    // Would have to provide our own copy constructor


    // Copy assignment operator
    // When assigning an existing object
    a1 = a2;

    // This also uses copy assignment.
    // Don't be fooled in thinking that a6 is not initialized yet in other languages it would be null
    // But in c++ Array a6 will call default constructor and so we already have an instance
    Array a6;
    a6 = a2;



    return 0;
}