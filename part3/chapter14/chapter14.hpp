#ifndef CHAPTER14_HPP
#define CHAPTER14_HPP

#include <iostream>
#include <string>
#include <vector>

class Sales_data;
class PrintString;
class LineReader;   // Exercise 14.35, 14.36
class SmallInt;

class Sales_data {

    friend std::ostream& operator<<(std::ostream&, const Sales_data&);
    friend std::istream& operator>>(std::istream&, Sales_data&);
    friend Sales_data operator+(const Sales_data&, const Sales_data&);
    friend bool operator==(const Sales_data&, const Sales_data&);
    inline friend bool operator!=(const Sales_data& lhs, const Sales_data& rhs) {
        return !(lhs == rhs);
    }

    public:
        Sales_data(unsigned int units = 0, double rev = 0.0, std::string bNo = "test-123"): 
        units_sold(units), revenue(rev), bookNo(bNo) { }
        Sales_data& operator+=(const Sales_data&);
        // since arithmetic operators are defined, below overloads are NOT recommended.
        explicit operator std::string() const { return bookNo; }
        explicit operator double() const { return revenue; }
    
    private:
        inline std::string isbn() const { return bookNo; }
        unsigned int units_sold;
        double revenue;
        inline double avg_price() const { 
            return units_sold ? revenue / units_sold : 0;
        }
        std::string bookNo;
};

class PrintString {
    public:
        PrintString(std::ostream& o = std::cout, char ch = ' '): os(o), sep(ch) { }
        inline void operator()(const std::string& s) const { os << s << sep; }
    private:
        std::ostream& os;
        char sep;
};

class LineReader {
    public:
        std::string operator()(std::istream& = std::cin);
    private:
        std::vector<std::string> lines;
};

// Example - class that stores integers between 0 and 255, both inclusive
class SmallInt {
    public:
        SmallInt(int i = 0): val(i) {
            if (i < 0 || i > 255)
                throw std::out_of_range("Bad SmallInt value");
        }
        explicit operator int() const { return val; }
    private:
        std::size_t val;
};

// Exercise 14.34
class MyClass {
    public:
        MyClass() = default;
        MyClass(int v1, int v2, int v3): x(v1), y(v2), z(v3) {}
        int operator()(int a, int b = 0, int c = 0) { return x == a ? y : z; }
    private:
        int x = 0;
        int y = 0;
        int z = 0;
};

// Exercise 14.37
class CheckEquals {
    public:
        CheckEquals(int v): val(v) { }
        bool operator()(int v) { return val == v; }
    private:
        int val;
};

// Exercise 14.38
class CheckBounds {
    public:
        CheckBounds(int lb, int ub): lowerBound(lb), upperBound(ub) { }
        bool operator()(const std::string& s) const {
            return s.size() >= lowerBound && s.size() <= upperBound;
        }
    private:
        int lowerBound;
        int upperBound;
};

#endif
