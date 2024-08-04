#ifndef CHAPTER7_HPP
#define CHAPTER7_HPP

#include <iostream>
#include <string>
#include <vector>

// Exercise 7.2
class SalesData {
    // Exercise 7.21
    private:
        std::string bookNo;
        unsigned unitsSold = 0;
        double revenue = 0.0;
    public:
        // Exercise 7.21
        friend std::istream& read (std::istream&, SalesData&);
        friend std::ostream& print (std::ostream&, const SalesData&);
        friend SalesData add (const SalesData&, const SalesData&);
        // Exercise 7.11
        SalesData (std::string bNo,unsigned units, double rev): bookNo(bNo), unitsSold(units), revenue(rev) {}
        // Exercise 7.12
        SalesData (std::istream&);
        std::string isbn (void) const {
            return bookNo;
        }
        SalesData& combine (const SalesData&);
        // Exercise 7.26
        inline double avgPrice (void) const;
};

// Exercise 7.4, 7.5
class Person {
    private:
        std::string name;
        std::string address;
    public:
        /* const as not modifying the calling object */
        std::string getName (void) const {
            return name;
        }
        std::string getAddress (void) const {
            return address;
        }
};

// Exercise 7.6
std::istream& read (std::istream&, SalesData&);
std::ostream& print (std::ostream&, const SalesData&);
SalesData add (const SalesData&, const SalesData&);

// Exercise 7.23 & 7.24
class Screen {
    public:
        using pos = std::string::size_type;
        Screen (void) = default;    // cannot rely because dimensionless screen created.
        Screen (pos ht, pos wd): height(ht), width(wd), contents(ht * wd, ' ') {}
        Screen (pos ht, pos wd, char c): height(ht), width(wd), contents(ht * wd, c) {}
        Screen& move (pos, pos);
        Screen& set (char);
        inline std::ostream& display (std::ostream& os) {
            os << contents;
            return os;
        }
        // Exercise 7.33
        pos size (void) const;
    private:
        pos cursor;
        pos height;
        pos width;
        std::string contents;
};

// Exercise 7.31
// class X;
// class Y;
// class X {
//     Y* pY;
// };
// class Y {
//     X objX;
// };

// Exercise 7.36 - no error
struct X {
    X(int i, int j):base(i), rem(base%j) {}
    int rem, base;
};

class SalesDataNew {
    public:
        int member;
        std::string s;
        SalesDataNew ():member(0),s("") {}
        explicit SalesDataNew (const SalesDataNew& s) { 
            this->member = s.member;
        }
        SalesDataNew (const std::string str):s(str) {}
};

// Exercise 7.53
class Debug {
    private:
        bool hw;
        bool io;
        bool other;
    public:
        constexpr Debug (bool b = true):hw(b),io(b),other(b) {}
        constexpr Debug (bool h, bool i, bool o):hw(h),io(i),other(o) {}
};

// Exercise 7.57
class Account {
    private:
        static constexpr int period = 30;
        static double interestRate;
        double amount;
        std::string owner;
    public:
        static double rate() {
            return interestRate;
        }
        void calculate () {
            amount += amount * interestRate;
        }
};

// Exercise 7.58
class Example {
    public:
        static double rate;
        // static double rate = 6.5;   // error, must be const
        static const int vecSize = 20;
        // static std::vector<double> vec(vecSize);    // error
        static std::vector<double> vec;
};

#endif
