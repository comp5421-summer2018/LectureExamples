#include <iostream>

using namespace std;

int c1 = 3;

void passByValue(int x){
    x++;
}

void passByReference(int &x){
    x++;
}

// This is pass by value (a copy of the value stored inside the pointer argument (an address) is made)
// However passing a pointer lets us modify the original copy
void passByPointerValue(int* x){
    (*x)++;
}


int main()
{
    cout << "Hello, World!" << endl;


    /* ------------------------------------
     * Examples of initialization
     * ------------------------------------*/

    // C++ 98
    int x1 = 0;

    // C++ 03
    int x2(0);

    // C++ 11 syntax
    int x3 {0};
    int x4 = {0};

    cout << x1 << x2 << x3 << x4 << endl;

    /* ------------------------------------
     * C-Strings
     * ------------------------------------*/

    char str[] = "abc";                 // Implied to be "abc\0"
    char str2[] = {'a', 'b', 'c'};      // NOTE: This has a bug since we did not specify null character '\0'
    cout << strlen(str) << endl;        // 3 as expected
    cout << strlen(str2) << endl;       // variable amount. Bug since no null character. strlen can't calculate length correctly


    /* ------------------------------------
     * Cin state
     * ------------------------------------*/

    int sum{0};
    int x = 0;
//    do {
//        sum += x;
//        cout << "Enter a number (ctrl+D or 'EOF' (mac) or ctrl+z (windows) to stop): ";
//    }while(cin >> x);
    cout << "Sum is: " << sum << endl;


    /* ------------------------------------
     * Overflows
     * ------------------------------------*/
    short o1 = 256;  // short has 16 bits
    char o2 = o1;     // char has 8 bits (can't represent 256)

    // Prints 256 0. 256 in 8 bits becomes 0 because 16 bits must be truncated down to 8 for char
    // 256 = 0000 0001 0000 0000 (16bits) -> 0000 0000 (8 bits)
    cout << o1 << " " << (int)o2 << endl;

    /* ------------------------------------
     * Signed and Unsigned
     * ------------------------------------*/
    // Data types can be marked with signed or unsigned (default is typically signed)
    short k1 = -1;              // signed range -2^15 to 2^15-1 (16 bits)
    unsigned short k2 = 0;      // unsigned range 0 - 2^16-1
    k2 = k1;

    // Prints k1=-1 k2=2^15-1 because:
    // -1 = 1111 1111 1111 1111 (using 2s complement)
    // but 1111 1111 1111 1111 unsigned is 2^15-1 = 65535
    cout << k1 << " " << k2 << endl;

    /* ------------------------------------
     * Booleans
     * ------------------------------------*/

    // In C++ other data types may be interpreted as a bool
    // Any non-zero value = true, zero value = false
    bool b1 = 1;         // true
    bool b2 = 2;        // true
    bool b3 = -2;        // true
    bool b4 = 0;        // false

    cout << b1 << b2 << b3 << b4 << endl;

    /* ------------------------------------
     * Casting
     * ------------------------------------*/

    // Implcit cast during initialization
    int s1 = 10.25;      // With C++98 style: warning
    //int s2 {10.25};   // With C++11 style: compiler error

    // Explicit cast
    int j = (int)10.25; // C style cast (legacy)
    int k = static_cast<int>(10.25);   // C++ style cast (preferred)


    /* ------------------------------------
     * References
     * ------------------------------------*/

    // Reference: variable alias, it directly refers to the variable itself

    int u = 10;
    int &v = u;
    int &z = u;

	// Not allowed since not a memory location to reference
	// int &w = 2; 

    u = 2*z;
    cout << u << v << z << endl;    // u = v = z = 20

    /* ------------------------------------
     * Pointers
     * ------------------------------------*/

    // Pointer: variable that stores the memory address of another variable

    int * u_ptr = &u;       // Do not confuse address operator & (rhs) with reference variable & (lhs)
    (*u_ptr)++;
    cout << u << endl;  // u=21


    /* ------------------------------------
     * Arrays and pointers
     * ------------------------------------*/

    // Arrays are actually implemented as pointers.
    // Array identifier is pointer to first element in array

    int a[] = {1,2,3,4,5,6};

    a[0] = 0;
    *a = 0;             // alternative

    a[1] = 0;
    *(a+1) = 0;         // alternative


    /* ------------------------------------
     * Pass by reference vs value
     * ------------------------------------*/

    int t = 1;
    passByValue(t);         // t = 1 after
    passByReference(t);     // t = 2 after
    passByPointerValue(&t); // t = 3 after
    cout << t << endl;

    /* ------------------------------------
     * Scopes
     * ------------------------------------*/

    int c1 = 2;

    {
        char c1 = 'a';
        cout << c1 << endl;     // local scope (by default we refer to the most precise current scope)
        cout << ::c1 << endl;   // global scope

        // Cannot refer to c1 in intermediate scope unfortunately
        // Can only refer to current scope or global scope using :: operator
    }


    /* ------------------------------------
     * Dynamic memory
     * ------------------------------------*/

    // Normal stack memory will be deleted when going out of scope
    // Dynamic memory allocated on the heap will be persisted even after the scope is exited
    // This is more flexible but introduces possibility of memory leaks
    // if programmer loses track memory remains allocated even after exits scope

    {
        // We declare dynamic memory storage with 'new' keyword
        int *c = new int;           // pointer to an int
        int *b = new int[5];        // pointer to a list of ints

        // Be sure to delete dynamic memory when done with it else will have memory leak
        delete c;
        delete [] b;
    }

    /* ------------------------------------
     * Input parsing
     * ------------------------------------*/

    {
        int x;
        char ch1;
        double d;
        char ch2;

        cout << "Enter '123x4.43ss': " << endl;

        // cin reads first valid data type until first whitespace or end of allowable datatype format
        cin >> x >> ch1 >> d >> ch2;

        // 123, x, 4.43, s
        cout << x << ch1 << d << ch2 << endl;
    }

    return 0;
}
