#include "chapter14.hpp"

bool operator==(const Sales_data& lhs, const Sales_data& rhs) {
    return lhs.isbn() == rhs.isbn() && lhs.units_sold == rhs.units_sold 
    && lhs.revenue == rhs.revenue;
}

std::ostream& operator<<(std::ostream& os, const Sales_data& item) {
    os << item.isbn() << " " << item.units_sold << " "
    << item.revenue << " " << item.avg_price();
    return os;
}

std::istream& operator>>(std::istream& is, Sales_data& item) {
    double price;
    is >> item.bookNo >> item.units_sold >> price;
    if (is)     // check inputs succeeded
        item.revenue = item.units_sold * price;
    else        // give default values
        item = Sales_data();
    return is;
}

Sales_data operator+(const Sales_data& lhs, const Sales_data& rhs) {
    Sales_data sum = lhs;
    sum += rhs;     // should implement += as well
    return sum;
}

// Exercise 14.13
Sales_data& Sales_data::operator+=(const Sales_data& rhs) {
    revenue += rhs.revenue;
    units_sold += rhs.units_sold;
    return *this;
}

// Exercise 14.35
#ifdef EXERCISE35
std::string LineReader::operator()(std::istream& ip) {
    std::string line;
    if (getline(ip, line))
        return line;
    return "";
}
#endif

// Exercise 14.36
#ifdef EXERCISE36
std::string LineReader::operator()(std::istream& ip) {
    std::string line;
    while (getline(ip, line))
        lines.push_back(line);
    return "";
}
#endif

// Exercise 14.44
#ifdef EXERCISE44
struct divide {
    int operator()(int dividend, int divisor) {
        return dividend / divisor;  // assuming divisor is non-zero
    }
};
auto mod = [](int a, int b) -> int {
    return a % b;   // assuming b is non-zero
};
int add(int a, int b) { return a + b; }
#endif
