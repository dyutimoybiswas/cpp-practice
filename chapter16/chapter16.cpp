#include "chapter16.hpp"

using std::cout;
using std::endl;
using std::unique_ptr;
using std::string;
using std::begin;
using std::end;
using std::vector;

int main (void) {
    // Example of function template usage.
    cout << compare(5, 6) << endl;
    cout << compare(-3.99, -4.1) << endl;

    // TODO: Exercise 16.4, 16.8

    // Example of Blob usage
    Blob<int> squares = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (size_t i = 0; i != squares.size(); ++i)
        squares[i] = i * i;

    // member template usage.
    int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> v1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Blob<int> b1(begin(ia), end(ia));   // using array
    Blob<int> b2(v1.begin(), v1.end());   // using vector


    twin<std::string> authors;      // authors is pair<string, string>

    // TODO: verify - Exercise 16.11 - ListItem in private should provide type
    // TODO: Exercise 16.16

    // Example of function template usage (default args).
    cout << compare_default(0, 42) << endl;     // uses less (default)
    cout << compare_default(2, -1, std::greater<int>()) << endl;

    // Example of class template usage (default args).
    Numbers<long double> lots_of_precision;
    Numbers<> average_precision;            // uses int

    // custom deleter for unique_ptr.
    unique_ptr<int, DebugDelete> pi(new int, DebugDelete());     // uses int
    unique_ptr<string, DebugDelete> ps(new string, DebugDelete());     // uses string

    // TODO: Exercise 16.27
    // Exercise 16.34 - both are illegal, as char* cannot be converted to reference.

    // explicit arguments usage.
    int i = 5; long n = 1000000000;
    auto v = sum<long long>(i, n);      // T1 = long long, T2 = int, T3 = long.

    // TODO: Exercise 16.45
    // Example of forwarding.
    f(42, i);
    flip1(f, i, 42);    // equivalent to previous

    // Example of template overloading.
    string s = "test";
    cout << debug_rep(s) << endl;   // calls (const T&) variant
    cout << debug_rep(&s) << endl;   // calls (T*) variant
    const string* sp = &s;
    cout << debug_rep(sp) << endl;  // both calls match the argument, but (T*) is called since better fit

    // Function template variadic params usage.
    print(cout, i, s, 24);  // 2nd - print(cout, s, 24), 3rd - print(cout, 24) - calls non-variadic version
    cout << endl;
}
