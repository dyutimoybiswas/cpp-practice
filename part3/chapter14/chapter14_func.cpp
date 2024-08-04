#include "chapter14.hpp"
#include "../chapter13/chapter13.hpp"    // for StrVec
#include "../chapter12/chapter12.hpp"    // for StrBlobPtr

inline bool operator==(const Sales_data& lhs, const Sales_data& rhs) {
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

StrVec& StrVec::operator=(std::initializer_list<std::string> i1) {
    auto data = alloc_and_copy(i1.begin(), i1.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

std::pair<std::string*, std::string*> StrVec::alloc_and_copy(const std::string* b, const std::string* e) {
    auto data = alloc.allocate(e - b);  // add space
    return {data, std::uninitialized_copy(b, e, data)};
}

void StrVec::free() {
    if (elements) {     // nothing to free if no elements
        for (auto p = first_free; p != elements; /*empty*/)
            alloc.destroy(--p);     // destroy in reverse order
        alloc.deallocate(elements, cap - elements);
    }
}

void StrBlob::check(size_type i, const std::string& msg) const {
    if (i >= data->size())
        throw std::out_of_range(msg);
}

StrBlobPtr& StrBlobPtr::operator++() {
    // cannot increment if past the end.
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

StrBlobPtr& StrBlobPtr::operator--() {
    --curr;
    // cannot decrement if past the beginning.
    check(curr, "decrement past begin of StrBlobPtr");
    return *this;
}

StrBlobPtr& StrBlobPtr::operator++(int) {
    StrBlobPtr ret = *this;     // save value before increment
    ++*this;        // calls prefix
    return ret;     // return saved value
}

StrBlobPtr& StrBlobPtr::operator--(int) {
    StrBlobPtr ret = *this;     // save value before decrement
    --*this;        // calls prefix
    return ret;     // return saved value
}

// TODO: verify - Exercise 14.35
// std::string LineReader::operator()() {
//     std::string line;
//     if (getline(ip, line))
//         return line;
//     return "";
// }

// TODO: verify - Exercise 14.36
std::string LineReader::operator()() {
    std::string line;
    while (getline(ip, line))
        lines.push_back(line);
    return "";
}

// Exercise 14.44
int add(int a, int b) { return a + b; }