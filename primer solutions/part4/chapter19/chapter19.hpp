#ifndef CHAPTER19_HPP
#define CHAPTER19_HPP

#include <iostream>
#include <cstdlib>
#include <string>
#include <functional>
#include <algorithm>

// Example of linkage directives.
extern "C" {
    #include <math.h>
}

// Example of enum forward declaration.
enum color: unsigned int;
enum class rgb;
// enum class color;       // error

// Example of overloaded new and delete.
void* operator new(size_t);
void operator delete(void*) noexcept;

// Example of typeid in RTTI.
class Base {
    // objects are equal when both TYPE and MEMBERS are equal.
    friend bool operator==(const Base&, const Base&);
    protected:
        // logic to check for equality among members.
        virtual bool equal(const Base&) const;
};

class Derived: public Base {
    protected:
        bool equal(const Base&) const;
};

// Example of enums.
enum color: unsigned int {red, green, blue};  // red=0, green=1, blue=2
enum class rgb {red, green,blue};
enum class intTypes {
    charType = 8, shortType = 16, intType = 16, // repititions allowed
    longType = 32
};

class Screen {
    public:
        typedef std::string::size_type pos;
        Screen() = default;
        char get_cursor() const { return contents[cursor]; }
        char get() const { return contents[0]; }
        char get(pos row, pos col) const { return contents[row * width + col]; }
        // Example of function returning pointer to member.
        static const std::string Screen::*data() { return &Screen::contents; }
        // Example of pointer to member function tables.
        Screen& home() { return *this; }
        Screen& forward() { return *this; }
        Screen& back() { return *this; }
        Screen& up() { return *this; }
        Screen& down() { return *this; }
        using Action = Screen& (Screen::*)();
        enum Directions { HOME, FORWARD, BACK, UP, DOWN};
        Screen& move(Directions d) {
            return (this->*Menu[d])();  // Menu[d] points to a member function.
        }
        // Exercise 19.12
        pos *cfoo() { return &cursor; }
    private:
        std::string contents = "some content";
        pos cursor;
        pos height, width;
        static constexpr Action Menu[] = {
            &Screen::home, &Screen::forward, &Screen::back, &Screen::up, &Screen::down
        };   // function table
};


// Example of union usage.
class Token {
    public:
        Token(): tok(INT), ival(0) {}
        // TODO: move constructor, move assignment.
        Token(const Token& t): tok(t.tok) { copyUnion(t); }
        Token& operator=(const Token&);
        Token& operator=(const std::string&);
        Token& operator=(char);
        Token& operator=(int);
        Token& operator=(double);
    private:
        // discriminant, to keep track of union's current value.
        enum { INT, CHAR, DBL, STR} tok;
        union {
            char cval;
            int ival;
            double dval;
            std::string sval;
        };
        void copyUnion(const Token&);
};

#endif
