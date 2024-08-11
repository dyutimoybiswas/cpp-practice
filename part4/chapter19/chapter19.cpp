#include "chapter19.hpp"

using std::cout;
using std::endl;
using std::string;
using std::function;
using std::find_if;
using std::begin;
using std::end;
using std::mem_fn;

int main(void) {
    // TODO: Exercise 19.3, 19.6
    // TODO: verify - Exercise 19.10 - a: A, b: A, c: B

    // Example of typeid
    #ifdef CUSTOM
    Derived* dp = new Derived;
    Base* bp = dp;
    cout << typeid(bp).name() << endl;      // base
    cout << typeid(*bp).name() << endl;     // derived
    cout << typeid(dp).name() << endl;      // derived
    cout << typeid(*dp).name() << endl;     // derived

    // Example of enums usage.
    color eyes = green;         // unscoped
    // rgb p = green;           // error-rgb::green not in scope.
    color hair = color::green;  // ok
    rgb c1 = rgb::red;
    constexpr intTypes charbits = intTypes::charType;   // used as constexpr
    // color danger = 0;        // error
    
    // Example of pointer to class members.
    const string Screen::*pdata;    // can point to string members.
    pdata = Screen::data();

    // Usage.
    Screen myScreen;
    cout << myScreen.*pdata << endl;
    
    // Exercise 19.11 - ordinary pointer can point to any object/variable.
    // TODO: Exercise 19.12

    // Example of pointer to member functions.
    auto (Screen::*p1)(Screen::pos, Screen::pos) const = &Screen::get;
    // Usage
    char ch = (myScreen.*p1)(0, 0);

    // Example of aliasing.
    using Action = char (Screen::*)(Screen::pos, Screen::pos) const;
    // Usage
    Action get = &Screen::get;

    // Usage of function table.
    myScreen.move(Screen::HOME);    // invokes home
    myScreen.move(Screen::DOWN);    // invokes down

    // TODO: verify - Example 19.14 - legal.
    
    // Example of converting a pointer to member function to a callable.
    function<bool (const string&)> fcn = &string::empty;
    string arr[] = {"a", "test", "", "array"};
    find_if(begin(arr), end(arr), fcn);

    // Alternative way.
    find_if(begin(arr), end(arr), mem_fn(&string::empty));
    #endif

    // TODO: Exercise 19.20
    
}
