#include "chapter14.hpp"
#include <map>
#include <functional>
#include <algorithm>
#include <fstream>

using std::cout;
using std::endl;
using std::map;
using std::vector;
using std::replace_if;
using std::string;
using std::ifstream;
using std::count_if;

int main(void) {
    // Exercise 14.1 - overloaded operators offer more flexibility than traditional operators wrt object types.
    // Exercise 14.3 - a - builtin, b, c, d: overloaded

    // Example
    #ifdef CUSTOM
    Sales_data data;
    cout << data << endl;
    #endif

    // Exercise 14.10 - a: improper, b: works
    #ifdef EXERCISE10
    Sales_data s = {10, 24.95, "0-210-99999-9"};
    cout << s << endl;
    #endif

    // Exercise 14.11 - doesn't handle input failure
    // Exercise 14.14 - uses less resources (+= calling + uses extra object)
    // Exercise 14.16 - TODO: String
    // Exercise 14.18 - TODO: String
    // Exercise 14.22 - copy and/or move assignment which is already synthesized for Sales_data.
    // Exercise 14.26 - TODO: String
    // Exercise 14.29 - because object attributes are modified
    // Exercise 14.31 - StrBlobPtr(StrBlob& a,..) takes care of copy and assignment,
    // and default destructor frees curr. shared and weak pointers are deallocated automatically.

    // Example - overloaded call
    #ifdef CUSTOM
    std::string s = "test";
    PrintString printer;                // prints to cout, space separator
    printer(s);
    PrintString errors(std::cerr, '\n');     // prints to cerr, newline separator
    errors(s);
    #endif

    // Exercise 14.33 - depends on arguments to be passed.
    
    // Exercise 14.34
    #ifdef EXERCISE34
    MyClass m1(2, 3, 4);
    cout << m1(3) << endl;  // prints 4
    cout << m1(2) << endl;  // prints 3
    #endif

    // Exercise 14.37
    #ifdef EXERCISE37
    vector<int> v {0, 1, 0, 3, 0, 5, 0, 7};
    replace_if(v.begin(), v.end(), CheckEquals(0), 8);  // create callable object that acts as predicate function.
    #endif

    // Exercise 14.38
    #ifdef EXERCISE38
    vector<string> words;
    string word;
    ifstream ip("/home/dyutimoy/repositories/cpp-primer-solutions/part3/chapter14/words.txt");
    while (getline(ip, word)) {
        words.push_back(word);
    }
    cout << count_if(words.cbegin(), words.cend(), CheckBounds(1, 10)) << endl;
    #endif

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

    // Exercise 14.47 - first converts to const int, second to int
}
