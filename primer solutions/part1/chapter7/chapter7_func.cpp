#include "chapter7.hpp"

using std::string;
using std::istream;
using std::ostream;

SalesData& SalesData::combine (const SalesData& rhs) {
    unitsSold += rhs.unitsSold;
    revenue += rhs.revenue;
    return *this;   // return object which called the function
}

double SalesData::avgPrice () const {
    return unitsSold ? revenue / unitsSold : 0.0;
}

istream& read (istream& is, SalesData& item) {
    double price = 0.0;
    is >> item.bookNo >> item.unitsSold >> price;
    item.revenue = price * item.unitsSold;
    return is;
}

ostream& print (ostream& os, const SalesData& item) {
    os << item.isbn() << " " << item.unitsSold << " " << item.revenue << " " << item.avgPrice();
    return os;
}

SalesData add (const SalesData& lhs, const SalesData& rhs) {
    SalesData sum = lhs;
    sum.combine(rhs);
    return sum;
}

SalesData::SalesData (istream& is) {
    read (is, *this);
}

Screen& Screen::move (pos r, pos c) {
    pos row = r * width;
    cursor = row + c;
    return *this;
}

Screen& Screen::set (char c) {
    contents[cursor] = c;
    return *this;
}

// Exercise 7.33
Screen::pos Screen::size () const {
    return height * width;
}
