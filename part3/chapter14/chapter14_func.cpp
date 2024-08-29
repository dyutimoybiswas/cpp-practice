#include "chapter14.hpp"
#include "../chapter13/chapter13.hpp"    // for StrVec
#include "../../part2/chapter12/chapter12.hpp"    // for StrBlobPtr

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
    auto data = allocator_traits::allocate(alloc, e - b);  // add space
    return {data, std::uninitialized_copy(b, e, data)};
}

void StrVec::free() {
    if (elements) {     // nothing to free if no elements
        for (auto p = first_free; p != elements; /*empty*/)
            allocator_traits::destroy(alloc, --p);     // destroy in reverse order
        allocator_traits::deallocate(alloc, elements, cap - elements);
    }
}

bool operator==(const StrVec& sv1, const StrVec& sv2) {
    // TODO: explore algorithms.
    if (sv1.size() != sv2.size())
        return false;
    for (auto itr1 = sv1.elements, itr2 = sv2.elements; itr1 != sv1.first_free; ++itr1, ++itr2)
        if (*itr1 != *itr2)
            return false;
    return true;
}

bool operator<(const StrVec& sv1, const StrVec& sv2) {
    // ref: https://cplusplus.com/reference/algorithm/lexicographical_compare/
    auto itr1 = sv1.elements, itr2 = sv2.elements;
    while(itr1 != sv1.first_free) {
        if (itr1 == sv2.first_free || *itr2 < *itr1) return false;
        else if(*itr1 < *itr2) return true;
        ++itr1; ++itr2;
    }
    return itr2 != sv2.first_free;
}

bool operator>(const StrVec& sv1, const StrVec& sv2) {
    return sv2 < sv1;
}

bool operator<=(const StrVec& sv1, const StrVec& sv2) {
    return !(sv1 > sv2);
}

bool operator>=(const StrVec& sv1, const StrVec& sv2) {
    return !(sv1 < sv2);
}

bool operator!=(const StrVec& sv1, const StrVec& sv2) {
    return !(sv1 == sv2);
}

void StrBlob::check(size_type i, const std::string& msg) const {
    if (i >= data->size())
        throw std::out_of_range(msg);
}

bool operator==(const StrBlob& sb1, const StrBlob& sb2) {
    return *sb1.data == *sb2.data;
}

bool operator<(const StrBlob& sb1, const StrBlob& sb2) {
    return *sb1.data < *sb2.data;
}

bool operator>(const StrBlob& sb1, const StrBlob& sb2) {
    return sb2 < sb1;
}

bool operator<=(const StrBlob& sb1, const StrBlob& sb2) {
    return !(sb1 > sb2);
}

bool operator>=(const StrBlob& sb1, const StrBlob& sb2) {
    return !(sb1 < sb2);
}

bool operator!=(const StrBlob& sb1, const StrBlob& sb2) {
    return !(sb1 == sb2);
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

StrBlobPtr StrBlobPtr::operator+(const size_t n) {
    StrBlobPtr ret = *this;
    ret += n;
    return ret;
}

StrBlobPtr StrBlobPtr::operator-(const size_t n) {
    StrBlobPtr ret = *this;
    ret -= n;
    return ret;
}

StrBlobPtr StrBlobPtr::operator-(const StrBlobPtr& sbp) {
    StrBlobPtr ret = *this;
    ret -= sbp;
    return ret;
}

StrBlobPtr& StrBlobPtr::operator+=(const size_t n) {
    // cannot increment if past the end.
    check(curr, "increment past end of StrBlobPtr");
    curr += n;
    return *this;
}

StrBlobPtr& StrBlobPtr::operator-=(const size_t n) {
    curr -= n;
    // cannot decrement if past the beginning.
    check(curr, "decrement past begin of StrBlobPtr");
    return *this;
}

StrBlobPtr& StrBlobPtr::operator-=(const StrBlobPtr& sbp) {
    curr -= sbp.curr;
    // cannot decrement if past the beginning.
    check(curr, "decrement past begin of StrBlobPtr");
    return *this;
}

std::string& StrBlobPtr::operator*() const {
    auto p = check(curr, "dereference past end.");
    return (*p)[curr];
}

std::string* StrBlobPtr::operator->() const {
    return &this->operator*();
}

bool operator==(const StrBlobPtr& sbp1, const StrBlobPtr& sbp2) {
    // check that wptrs point to the same vector and index (curr) is same.
    return sbp1.wptr.lock() == sbp2.wptr.lock() && sbp1.curr == sbp2.curr; 
}

bool operator<(const StrBlobPtr& sbp1, const StrBlobPtr& sbp2) {
    return sbp1.wptr.lock() == sbp2.wptr.lock() && sbp1.curr < sbp2.curr; 
}

bool operator>(const StrBlobPtr& sbp1, const StrBlobPtr& sbp2) {
    return sbp2 < sbp1;
}

bool operator<=(const StrBlobPtr& sbp1, const StrBlobPtr& sbp2) {
    return !(sbp1 > sbp2);
}

bool operator>=(const StrBlobPtr& sbp1, const StrBlobPtr& sbp2) {
    return !(sbp1 < sbp2);
}

bool operator!=(const StrBlobPtr& sbp1, const StrBlobPtr& sbp2) {
    return !(sbp1 == sbp2);
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
