#include "chapter7.hpp"

using std::cin;
using std::cout;
using std::string;
using std::vector;

int main(int argc, char const *argv[])
{
    // Exercise 7.10 - TODO: verify: determines whether both data1 & data2 have been read. 

    // Exercise 7.27
    Screen myScreen(5, 5, 'X');
    myScreen.move(4, 0).set('#').display(cout);
    cout << "\n";
    myScreen.display(cout);
    cout << "\n";

    // Exercise 7.28 & 7.29- operations only reflected in line 15 and not line 17

    // note
    SalesDataNew obj1;
    // SalesData obj2(obj1);   // valid
    // SalesData obj2 = obj1;  // invalid
    
    // Exercise 7.48 - TODO: verify
    string null_isbn("9-999-99999-9");
    // SalesData item1(null_isbn); // invalid
    // SalesData item2("9-999-99999-9");   //invalid

    // Exercise 7.51
    /* string constructor with single param (const char*) is not explicit, because it can be represented as a string as well.
       vector constructor with single param (size_t) is explicit to enforce that size passed is of type size_t.
    */
    // Exercise 7.58
    // double Example::rate;   // error
    // vector<double> Example::vec(Example::vecSize);  // error

    return 0;
}
