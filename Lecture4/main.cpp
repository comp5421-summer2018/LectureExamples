#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>

using namespace std;

// EXAMPLE: extract all words from a text file
// -------------------------

void readFile(){
    string fileName;
    cout << "Enter file name: ";
    cin >> fileName;

    ifstream fin(fileName);

    // OR
    // ifstream fin;
    // fin.open(fileName);

    if(!fin){
        cout << "cout not open " << fileName;
        exit(1);
    }

    string word;

    // WARNING:     You must do at least one read before doing while(fin)
    //              If not, flag bits will be unset and behavior is undefined

    // Example 1: This will read all word in a file
    while(fin >> word){
        cout << word << endl;
    }

    // Example 2: Read all words and associate line numbers to each line
    string line;
    int n = 0;

    while(getline(fin, line)) {
		n++;
    	istringstream sin(line);        // stream reader for a string (1 line in this example)
        string word;
        while(sin >> word){
            cout << word << n << endl;
        }
    }

}


int main()
{
    cout << "Hello, World!" << endl;

    // Sample input
    //
    // ABC<return>
    // Ctrl+Z
    //
    // Count value 4
    char ch;
	int count = 0; 
    while(cin.get(ch)){
        ++count;
    }
    cout << count << endl;

	cin.clear();
	string str2;
	count = 0; 
	while(getline(cin, str2))
	{
		count++; 
	}
	cout << count << " lines entered" << endl;

    // Operator >> skips over whitespace and newline characters
    // Keeps going until it finds the eof

    // Sample input
    //
    // 123<space><space>45<return>
    // 97<return>
    // 82<space>-10<return>
    // Ctrl+Z<return>
    // 99
	cin.clear();
    int x;
    while(cin >> x){
        cout << x << endl;
    }

    // cin >> x;       // Does not work (see reason below), blocks forever

    // Output:  123<return>45<return>97<return>82<return>-10<return>

    // Note that cin will not read the last 99 because eof has already
    // been reached so eof bit is already set on cin and thus cin will no longer read any further input

    // Reset all bits on cin. This will reset io flags and we can now read from cin
    cin.clear();

    cin >> x;       // 99


    // Sample input
    //
    // A<space><space>B<space>C<return>
    // <space><space<space>DE<return>
    // Ctrl+Z
    {

        char ch;
		int i = 0; 
        while(cin >> ch){
            cout << ch;
			i++;
        }
        // Output:  ABCDE
		// i = 5

    }

    // Input Manipulators
    // -----------------------------------------
    // set(w)       - Sets width of next field whether reading or writing
    // ws           - Skip to first non-whitespace character. Use configured whitespace settings for subsequent operations
    // skipws       - Always skip whitespaces (DEFAULT BEHAVIOR)
    // noskipws     - Turns off skipws (will always read whitespace now)
    // dec          - read decimal numbers
    // oct          - read octel numbers
    // hex          - read hexadecimal numbers
    // boolalpha    - Read 'true' and 'false' as string literals instead of boolean values
    // noboolalpha  - Return off boolalpha

	// Sample input:
	// 12 12 a0
	// Read values:     10, 12, 160
	cin.clear(); 
    {
        int x,y,z;
        cin >> oct >> x >> dec >> y >> hex >> z;
    }

    int n = 70;
    cout << dec << n << endl;	// 70
    cout << hex << n << endl;	// 46
    cout << oct << n << endl;	// 106


	char a;

	// All subsequent reads do not skip whitespace
	cin >> noskipws;
	// Skip to non first whitespace character for 1 read
    cin >> ws >> a;

    // Reset back to default behavior of skipping whitespace
    cin >> skipws;

    // Get and getLine
    // 1) char c = cin.get()                   - return
    // 2) cin.get(c)                           - Fill existing variable
    // 3) cin.getline(str, n = 1, t = '\n')    - str = char array to fill, n = number of characters to read, t = terminator (default \n)
    // 4) cin.get(str, n=1, t='\n')
    // AVOID 3) and 4) since hard to set n correctly (hard to know how much space needed)
    // Use the following version
    // 5) getline(istream &, string);

    // Sample input
    //
    // This is a line<return>

    // Can read max 10 char because need 1 for null byte
    char str[10];

    // Reads: this<space>is<space>a
    cin.getline(str, 10, '\n');
	
    // Difference with getline -> removes the newline character for next read


    // Ignore
    // ---------------------------------
    // cin.ignore(n = 1, t = eof)   -> Ignores n characters or until the terminator

    // Ignores the next character
    cin.ignore();

    // Looks at next characte rin stream but does not remove it
    cin.peek();

    // Puts c back into stream
    char c;
    cin.putback(c);

    // Puts the last character read back into stream
    cin.unget();


    // Output Manipulators
    // -----------------------------------------
    // left             - Left aligns
    // right            - Right aligns
    // internal         -
    // setfill(c)       - Sets fill character (does not persist)
    // setw(n)          - Sets width of next output (persists)
    // dec              - Outputs number in decimal format
    // oct              - Outputs number in octel format
    // hex              - Outputs number in hexadecimal format
    // uppercase        - Controls the casing of number formatters.     (ex for hex numbers:    0xA5 Vs. 0XA5   ex for exp      1.0e5   Vs. 1.0E5)
    // nouppercase      - Turns off uppercase
    // boolalpha        - Prints true/false boolean values as string iterators
    // noboolalpha      - Turns off boolalpha
    // showbase         - Show numberic base
    // noshowbase       - Do not show numeric base
    // showpoint        - cout << 1.0   (prints 1)  cout << showpoint << 1.0 (prints 1.0)
    // showpos          - Shows + sybmol for positive numbers
    // noshowpos        - Turns off showpos
    // fixed            - Shows numeric output in fixed number format
    // scientific       - Shows numeric output in scientific number
    // setprecision(n)  - Sets the decimal precision
    // flush            - Output stream is buffered. When buffer is full the stream is flushed. IF you want to flush the stream prematurely, do flush command
    // endl             - Calls flush (flushes buffer) then enters newline
    //                  - cout << flush<< '\n'

    cout << setw(5) << left << "ABC" << setw(7) << right << "XYZ";
    // output:
    // ABC<space><space><space><space><space><space>XYZ

    cout << oct << 10;      // 012      - 0 is leading character of octel numbers
    cout << hex << 165;     // A5     - 0x is leading character for hex numbers

    {
        cout << fixed << setprecision(2);       // TODO: Try without fixed
        double x = 1.2345;
        cout << x;      // 1.23
    }

    // Standard error stream
    // cerr is standard error stream similar to cout object
    // cerr will always flush buffer immediately when written to


    // STL template classes
    // ------------------------------------
    // sequential:  list, vector, array, forward list, dequeue
    // associative:     map, set, multimap, multiset

    {
        // Iterators
        int a[10] = {1,2,3,4,5,6,7,8,9,10};

        for(int * p = a; p != a+10; p++){
            cout << *p << " ";
        }

        // Initialize a vector from other collection
        vector<int> v(a, a+10);
		vector<int> v(begin(a), end(a)); 

        // end is one element after the last
        for(vector<int>::iterator it = v.begin(); it != v.end(); it++){
            cout << *it << endl;
        }

        // Alternative with begin(v) and end(v)
        for(vector<int>::iterator it = begin(v); it != end(v); it++){
            cout << *it << endl;
        }

    }


    {
        // C++11 array iterators
        array<int, 3> arr = {1,2,3};
        for(array<int,3>::iterator it = arr.begin(); it != arr.end(); it++){
            cout << *it << endl;
        }

    }


    return 0;
}