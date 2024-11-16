#include "chapter18.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::cerr;

int main (void) {
    #ifdef CUSTOM
    // Usage of namespace.
    using cplusplus_primer::Sales_data;
    using cplusplus_primer::custom_exceptions::isbn_mismatch;

    // Exercise 18.2 - program terminates.
    // Exercise 18.4 - since all custom exceptions inherit exception class, corresponding block should be put in the end.

    // Example of custom exception usage.
    Sales_data item1, item2, sum;
    while (cin >> item1 >> item2) {
        try {
            sum = item1 + item2;
        } catch (const isbn_mismatch& e) {
            cerr << e.what() << ": left isbn(" << e.left
                 << ") right isbn(" << e.right << ")" << endl;
        }
    }

    // Example of unnamed namespace usage.
    using local::i;
    
    // Exercise 18.13 - to limit access of members to the local file.
    
    // Example of namespace aliasing.
    namespace primer = cplusplus_primer;
    namespace excp = cplusplus_primer::custom_exceptions;

    A::C obj;
    f(obj);    // no error
    // f2();       // error
    #endif

    #ifdef EXERCISE14
    mathlib::matrixLib::matrix m1, m2;
    m1 * m2;
    #endif

    // Exercise 18.18 - template invoked for int, string overload invoked for string.
    // Exercise 18.21 - a: access sp missing, b: duplicate inheritance, c: valid.
    // Exercise 18.22 - A, B, C, X, Y, Z.
    
    // Exercise 18.29 - a. Base, Class, D1, D2, Class (constructors) b. 1 base, 2 class c. a, c
}
