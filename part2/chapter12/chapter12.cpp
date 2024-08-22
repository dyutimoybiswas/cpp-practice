#include "chapter12.hpp"

using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;

StrBlob b1;

int main(int argc, char const *argv[])
{
    // Example - shared pointers.
    #ifdef CUSTOM
    shared_ptr<int> p(new int(42));
    int x = 28;
    // shared_ptr<int> px(&x);      // error, memory should be dynamically allocated.
    shared_ptr<int> px = make_shared<int>(x);

    // // Example - unique pointers.
    unique_ptr<int> u(new int(29));

    StrBlob b2 = {"a", "an", "the"};
    b1 = b2;
    b2.push_back("about");
    #endif
    // Exercise 12.1 - 4

    // Exercise 12.3 - we can modify push_back and pop_back to const.
    // Exercise 12.5 - we want to be able to use assignment (= {...}) in addition to direct initialization ({...})

    // Exercise 12.8 - p should be explicitly freed in calling function.
    // Exercise 12.9 - normal pointer will leak memory, shared pointer sees no leak
    // Exercise 12.10 - process(p)
    // Exercise 12.11 - temp pointer location gets freed

    // Exercise 12.17 - a, c will cause error

    // using shared_ptr to manage arrays - deleter is *mandatory*.
    #ifdef CUSTOM
    auto deleter = [](int* p) { delete [] p; };
    shared_ptr<int> sp(new int[10], deleter);
    #endif

    return 0;
}

// Exercise 12.15
#ifdef EXERCISE15
struct connection { void* mem; };
void disconnect(connection c) {}
auto end_connection = [](connection* p) { disconnect(*p); };
#endif
