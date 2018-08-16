#include <iostream>
#include <string>

using namespace std;

class FooBar{

public:
    FooBar(int x){

    }

    FooBar(){}

    FooBar(char* str){

    }

};

class Bar{
    int x;
public:
    Bar(int x = 20) : x(x){}

    int get() const{
        return x;
    }

    void set(int x){
        this->x = x;
    }

    Bar clone(){
        return Bar();
    }
    const Bar cloneAsConst(){
        return Bar();
    }
};

ostream & operator<<(ostream & out, const Bar & b){
    out << b.get() << endl;
    return out;
}

class Foo{

    // If we had default constructor, would not work because of const int and reference must be initialized by us
    int x;
    const int y;            // Must be initialized here or in initialization list
    int &z;                 // Can only be initialized in initialization list
    string name;

public:

    // Put &zz if you want it to be passed by reference, else reference will be a reference to a local variable
    Foo(int xx, int yy, int &zz, const string &name)
        : x(xx), y(yy), z(zz), name(name) {      // copy constructor called for these in initialization, not assignment

        // Copy assignment would be called for those initialized here
        cout << "ctor " << name << endl;
    }

    Foo(const Foo & other)
    : x(other.x), y(other.y), z(other.z), name(other.name){
        cout << "copy constructor " << name << endl;
    }

    ~Foo(){
        cout << "dtor " << name << endl;
    }
};


class MyClass{
private:
    int f1;

public:

    // either return void or return ostream &
    // But if we have void can't chain
    // Must be friend function since << operator invoked on cout not on object
    friend std::ostream &operator<<(std::ostream &os, const MyClass &aClass)
    {
        os << "f1: " << aClass.f1;
        return os;
    }

    // <<       insertion operator (inserting into stream)
    // >>       extraction operator (extracting from stream)

};

// a and b are passed by value, thus will have no effect in caller context
void swapByValue(int a, int b){
    int temp = a;
    a = b;
    b = temp;
}

// p and q are pointers, pointing to arguments from the caller context
// In this case changes will be reflected in caller context
// Passed by value
void swap(int *p, int*q){
    int temp = *p;
    *p = *q;
    *q = temp;
}

// p and q are references (aliases) to pointers
void swap(int *&p, int *&q){
    int *temp = p;
    p = q;
    q = temp;
}

// x and y are reference (aliases) to variables in the caller context
// In this case changes will be reflected in caller context
void swap(int &x, int &y){
    int temp = x;
    x = y;
    y = temp;
}

int &f(int &a){
    return a;
}

int &g(){
    int a = 2;      // Declared on stack
    return a;       // BUG: a goes out of scope, does not exist after return
}

int &h(int a){      // Passed by value, so local copy created on stack
    return a;       // BUG: a goes out of scope, does not exist after return
}

void uRef(int & x){

}

void uConstRef(const int & x){

}

// Mimic str_cpy
char * copy(char* dest, const char* source){

    int i;
    for(i = 0; source[i] != '\0'; i++){
        dest[i] = source[i];
    }
    dest[i] = '\0';
    return dest;
}

char * copyEfficient(char* dest, const char* source){

    char* dest_itr = dest;

    // Unary operator has precedence over dereference
    // Value of assignment expression will always be returned ('\0' for the last)
    // 0, '\0' can be cast as a boolean
    while(*dest_itr++ = *source++);

    // while(*(dest_itr++) = *(source++));

    return dest;
}

int triple(int x){
    return 3*x;
}


int main()
{
    // ---------------------------------------
    // Pass by reference and value
    // ---------------------------------------
    int a = 1;
    int b = 2;

    swapByValue(a, b);
    swap(&a, &b);
    swap(a, b);

    // LValue and RValue
    // LValue = must be addressable (must refer to some storage)
    // Rvalue = Appears on RHS that can form assignment expression

    // ONLY return by reference for things that won't go out of scope after exist of function
    // For stack variables:     Must exist before and after call
    // a = 10
    f(a) = 10;

    // BUG, a out of scope
    // May appear as though it might work but behavior is undefined
    g() = 2;

    // ---------------------------------------
    // Const
    // ---------------------------------------
    int x = 10;
    int &rx = x;

    const int y = 20;
    //int &yRef = y;        // Error, would mean that rb could modify b by a backdoor
	// int* yPtr = &y;

    const int &yRef = y;
	const int* yPtr = &y; 

    // Literals CANNOT be assigned to references
    // But const literals CAN be assigned to reference
    // int &rd = 10;        // Error, 10 is not yet a memory location therefor cannot be referenced

    const int &re = 10;     // Ok since 10 is treated as a constant

    // uRef(10);       // NOT ok, 10 is not addressible
    uConstRef(10);          // ok


    // ---------------------------------------
    // Object memory
    // ---------------------------------------
    // Atomic variables implicitly declare
    MyClass c;      // default constructor called, object already created. Not same as in java where would be null when declared

    MyClass *c_ptr = &c;
    // delete c_ptr;       // Wrong, trying to delete non-heap memory. Can only delete dynamic memory allocated on heap (via new)


    // ---------------------------------------
    // Assignment and expression evaluation
    // ---------------------------------------

    // Recall that assignment operator will always return value of expression after evaluation
    cout << (a = 20) << endl;

    {
        // When reading variables, read constructs to the right and then the left

        int a[10];              // array of 10 integers
        int* b[10];             // array of 10 pointers to integers

        int (*pa)[10] = &a;     // pa is a pointer to an array of 10 integers
        int (*f)(int);          // f is a pointer to a function taking an int and returning an int

        f = triple;             // Can also use & here
		// f = &triple;
        cout << f(3) << endl;

		int*d = new int[10];		// Returns pointer to head of array
		int*e = new int;			// Returns pointer to int
		int** x = new int*[10];		// Returns pointer to head of array of type int*
		int** y = new int*;			// Returns pointer to element of int*
		*y = new int[10];

        char * cStrings[10];    // cStrings is an array of 10 c-strings

    }


    // ---------------------------------------
    // Constructor, Destructor, Copy Constructor
    // ---------------------------------------

    {
        int a = 10, b = 20, c = 30;
        string name{"Joe"};
        Foo f(a,b,c, name);
        Foo g(a,b,c, "Jane");
        {
            Foo h(a,b,c, "Bob");
        }
        Foo * pf = new Foo(a,b,c, "Mary");
        delete pf;

        // ctor: Joe
        // ctor: Jane
        // ctor: Bob
        // dtor: Bob
        // ctor: Mary
        // dtor: Mary
        // dtor: Jane
        // dtor: Joe
    }


    {
        Bar b1;
        const Bar b2(40);

        cout << b1.get() << endl;

        // Would fail to build if get was not const since b2 is const.
        // If get() is not const then possible that it might change b2
        cout << b2.get() << endl;

        // On two lines because of overload of << insertion operator
        cout << b1 << b2 << endl;

        b1.clone().set(10);
        Bar b3;
        (b3 = b1.clone()).set(10);
        // b2.cloneAsConst().set(10);      // Error since set is a const
    }


    {
        FooBar f1, f2;
        f1 = 10;        // This is the same as f1 = Foobar(10), a temporary FooBar is made from 10, assignment operator called, then temp FooBar(10) deleted
        f2 = "Hello";
    }

	// system("pause"); 
    return 0;
}