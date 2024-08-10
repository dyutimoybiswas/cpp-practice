#include <iostream>

int main(void) {
    // Exercise 2.3 & 2.4
    #if defined(EXERCISE3) || defined(EXERCISE4)
    std::cout << sizeof(unsigned int) << std::endl;  // 4, 0 to 4294967295 (-1)

    unsigned int u = 10, u2 = 42;
    std::cout << u2 - u << std::endl;   // 32
    std::cout << u - u2 << std::endl;   // 4294967264
    #endif

    // Exercise 2.9
    // std::cin >> int x;  // syntax error
    // double salary = wage = 999.99;  // wage undefined

    // Exercise 2.10
    #ifdef EXERCISE10
    std::string global_str;  // empty string ("")
    int global_int;     // garbage (unpredictable)
    #endif

    // Exercise 2.12
    #ifdef EXERCISE12
    int _;          // valid
    // int catch-22;   // invalid
    // int 1_or_2 = 1; // invalid
    double Double;  // valid
    #endif

    // Exercise 2.13
    #ifdef EXERCISE13
    int x = 12;
    {
        int x = 35;
        std::cout << x << std::endl;  // prints 35, outer scope x is overridden
    }
    #endif

    // Exercise 2.14
    #ifdef EXERCISE14
    int i = 100, sum = 0;
    for (int i = 0; i != 10; ++i)
    {
        sum += i;
    }
    std::cout << sum << ", " << i << std::endl;  // 45, 100
    #endif

    // Exercise 2.16
    #ifdef EXERCISE16
    int v = 0, &r1 = v; double d = 0, &r2 = d;
    r2 = 3.14159;   // modifies d
    r2 = r1;        // modifies d to 0
    v = r2;         // v stays 0
    r1 = 2;         // changes v to 2
    #endif

    // Exercise 2.35
    #ifdef EXERCISE35
    const int i1 = 42;
    auto j = i1;                    // int, not const
    j = 5;                          // no error
    const auto &k = i1;             // const ref, cannot be modified
    auto *p = &i1;                  // const pointer, cannot be modified
    const auto j2 = i1, &k2 = i1;   // both variable and reference are constant.
    #endif

    // Exercise 2.37
    #ifdef EXERCISE37
    int a = 3, b = 4;
    decltype(a) c = b;              // c is an int
    std::cout << c << std::endl;
    #endif
}
