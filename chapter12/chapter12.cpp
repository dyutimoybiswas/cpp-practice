#include "chapter12.hpp"

StrBlob b1;
int main(int argc, char const *argv[])
{
    StrBlob b2 = {"a", "an", "the"};
    b1 = b2;
    b2.push_back("about");
    // Exercise 12.1 - 4

    // Exercise 12.3 - we can modify push_back and pop_back to const.
    // Exercise 12.5 - TODO:

    // Exercise 12.8 - p should be explicitly freed in calling function.
    // Exercise 12.9 - normal pointer will leak memory, shared pointer sees no leak
    // Exercise 12.10 - process(p)
    // Exercise 12.11 - temp pointer location gets freed

    // Exercise 12.17 - a, c will cause error

    // using shared_ptr to manage arrays - deleter is *mandatory*.
    auto deleter = [](int* p) { delete [] p; };
    std::shared_ptr<int> sp(new int[10], deleter);

    return 0;
}

// Exercise 12.15
/*struct connection;
void disconnect(connection);
auto end_connection = [](connection* p) { disconnect(*p); }*/