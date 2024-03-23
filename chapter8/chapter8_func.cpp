#include "chapter8.hpp"
#include <string>

using std::istream;
using std::string;
using std::cout;

// Exercise 8.1 & 8.2
istream& read (istream& is) {
    string ip;
    while (is >> ip) {
        cout << ip;
    }
    is.clear();
    return is;
}
