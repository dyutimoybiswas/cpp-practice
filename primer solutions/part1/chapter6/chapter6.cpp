#include "chapter6.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::runtime_error;
using std::cerr;

// Excercise 6.44
#ifdef EXERCISE44
inline bool isShorter(const string &s1, const string &s2) { return s1.size() < s2.size(); }
#endif

// Excercise 6.46
#ifdef EXERCISE46
constexpr bool isShorter(const string &s1, const string &s2) {
    return s1.size() < s2.size();   // error: size is non-constexpr
}
#endif

// Excercise 6.25
int main(int argc, char const *argv[])
{
    // Exercise 6.4
    #ifdef EXERCISE4
    int n;
    cout << "Enter a number to find factorial: ";
    cin >> n;
    cout << "Factorial is " << factorial(n) << endl;
    #endif

    // Exercise 6.7
    #ifdef EXERCISE7
    for (unsigned i = 0; i < 5; i++)
        cout << sequenceGenerator() << " "; // prints 0 through 4
    cout << endl;
    #endif

    // Exercise 6.12
    #ifdef EXERCISE12
    int x = 5, y = 6;
    cout << "Before swap - " << x << ", " << y << endl;
    swap(x, y);
    cout << "After swap - " << x << ", " << y << endl;
    #endif

    // example
    #ifdef CUSTOM
    int x = 5;
    foo(&x);
    cout << "Modified x: " << x << endl;

    // note
    int i = 2;
    int *const p = &i;
    *p = 1;             // valid
    const int &r = 42;  // valid
    foo("test");        // error, valid when parameter is const
    #endif

    // Excercise 6.17
    #ifdef EXERCISE17
    string word = "abCdef";
    cout << word << (containsCapital(word) ? " contains" : " doesn't contain") << " capital letter(s)" << endl;
    convertToLower(word);
    cout << "After converting to lowercase, word is " << word << endl;
    #endif

    // Excercise 6.21
    #ifdef EXERCISE21
    int v = 4;
    cout << "Larger between 5 and " << v << " is " << larger(5, &v) << endl;
    #endif

    // Excercise 6.24
    #ifdef EXERCISE24
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    print(arr);     // no error
    #endif

    // Excercise 6.25
    #ifdef EXERCISE25
    if (argc != 3) {
        throw runtime_error ("Arguments passed must be 2!");
    }
    cout << "Concatenated string: " << (argv[1] + static_cast<string>(argv[2])) << endl;
    #endif

    // Excercise 6.27
    #ifdef EXERCISE27
    cout << "Sum of elements = " << sumElements({2, 3, 4, 5}) << endl;
    #endif

    // Excercise 6.35
    #ifdef EXERCISE35
    vector<int> vect {3, 6, 9, 12, 1};
    printVector(vect, vect.begin());
    #endif

    // Excercise 6.42
    #ifdef EXERCISE42
    cout << make_plural(2, "success") << endl;
    cout << make_plural(2, "failure") << endl;
    #endif

    // Excercise 6.44
    #ifdef EXERCISE44
    cout << "Shorter string between a and bc is " << (isShorter("a", "bc") ? "a" : "bc") << endl;
    #endif

    // assert(false);   // throws error

    // Excercise 6.54 & 6.56
    #if defined(EXERCISE54) || defined(EXERCISE56)
    vector<int (*)(int, int)> pvect {baz, bam};
    pvect[0](1, 2);
    pvect[1](3, 4);
    #endif

    // Excercise 6.55
    #ifdef EXERCISE55
    vector<int (*)(int, int)> pvect {add, subtract, multiply, divide};
    cout << "Adding 2 and 5 = " << pvect[0](2, 5) << endl;
    cout << "Subtracting 4 from 18 = " << pvect[1](18, 4) << endl;
    cout << "Multiplying 17 and 31 = " << pvect[2](17, 31) << endl;
    // cout << "Dividing 4 by 0 = " << pvect[3](4, 0) << endl; // error
    cout << "Dividing 4 by 2 = " << pvect[3](4, 2) << endl;
    #endif

    return 0;
}
