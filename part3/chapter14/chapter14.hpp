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
        LineReader(std::istream& is = std::cin): ip(is) { }
        std::string operator()();
    private:
        std::istream& ip;
        std::vector<std::string> lines;
};

// Exercise 14.44
struct divide {
    int operator()(int dividend, int divisor) {
        return dividend / divisor;  // assuming divisor is non-zero
    }
};
int add(int, int);
auto mod = [](int a, int b) -> int {
    return a % b;   // assuming b is non-zero
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

#endif
