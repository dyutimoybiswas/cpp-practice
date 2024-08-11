#include "chapter14.hpp"
#include <map>
#include <functional>

using std::cout;
using std::endl;
using std::map;

int main(void) {
    // TODO: Exercise 14.1, 14.2
    // TODO: verify - Exercise 14.3 - a, b, c, d: overloaded

    // Example
    #ifdef CUSTOM
    Sales_data data;
    cout << data << endl;
    #endif

    // TODO: Exercise 14.9, 14.10
    // Exercise 14.11 - doesn't handle input failure
    // Exercise 14.14 - uses less resources (+= calling + uses extra object)
    // TODO: Exercise 14.16, 14.18, 14.22, 14.26, 14.28
    // TODO: verify - Exercise 14.29 - because object attributes are modified
    // TODO: verify - Exercise 14.31 - StrBlobPtr(StrBlob& a,..) takes care of copy and assignment,
    // and default destructor frees curr. shared and weak pointers are deallocated automatically.

    // Example - overloaded call
    #ifdef CUSTOM
    std::string s = "test";
    PrintString printer;                // prints to cout, space separator
    printer(s);
    PrintString errors(std::cerr, '\n');     // prints to cerr, newline separator
    errors(s);
    #endif

    // TODO: verify - Exercise 14.33 - depends on arguments to be passed.
    // TODO: Exercise 14.30, 14.34, 14.37, 14.38
    
    // Exercise 14.44
    #ifdef EXERCISE44
    map<std::string, std::function<int(int, int)>> ops = {
        {"+", add},
        {"-", std::minus<int>()},
        {"/", divide()},
        {"*", [](int a, int b) -> int { return a * b; }},
        {"%", mod}
    };
    #endif

    // Example - conversion overload.
    #ifdef CUSTOM
    SmallInt si = 3.14;     // convert to int implicitly and call SmallInt constructor
    // calls overloaded conversion and implicitly converts to double before adding.
    // doesn't work if conversion overload is explicit.
    static_cast<int>(si) + 3.14; // si + 3.14;
    #endif

    // TODO: Exercise 14.45
    // TODO: verify - Exercise 14.47 - first converts to const int, second to int
}
