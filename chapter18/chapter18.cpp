#include "chapter18.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::cerr;

int main (void) {

    // Usage of namespace.
    using cplusplus_primer::Sales_data;
    using cplusplus_primer::custom_exceptions::isbn_mismatch;

    // Exercise 18.2 - program terminates.
    // TODO: Exercise 18.4
    
    // Example of custom exception usage.
    Sales_data item1, item2, sum;
    // while (cin >> item1 >> item2) {
    //     try {
    //         sum = item1 + item2;
    //     } catch (const isbn_mismatch& e) {
    //         cerr << e.what() << ": left isbn(" << e.left
    //              << ") right isbn(" << e.right << ")" << endl;
    //     }
    // }

    // Example of unnamed namespace usage.
    using local::i;
    
    // TODO: Exercise 18.13, 18.14
    
    // Example of namespace aliasing.
    namespace primer = cplusplus_primer;
    namespace excp = cplusplus_primer::custom_exceptions;

    A::C obj;
    f(obj);    // no error
    // f2();       // error

    // TODO: verify - Exercise 18.18 - recursion.
    // TODO: Exercise 18.21
    // Exercise 18.22 - A, B, C, X, Y, Z.
    
    // Exercise 18.29 - a. Base, Class, D1, D2, Class (constructors) b. 1 base, 2 class c. a, c
}
