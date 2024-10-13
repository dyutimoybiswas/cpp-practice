#include "StrBlobPtr.hpp"

StrBlob::StrBlob(): data(std::make_shared<std::vector<std::string>>()) {}
StrBlob::StrBlob(std::initializer_list<std::string> i1): data(std::make_shared<std::vector<std::string>>(i1)) {}

void StrBlob::check(size_type i, const std::string& msg) const {
    if (i >= data->size())
        throw std::out_of_range(msg);
}

std::string& StrBlob::front() {
    check(0, "front on empty StrBlob");
    return data->front();
}
std::string& StrBlob::back() {
    check(0, "back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back() {
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check (std::size_t i, const std::string& msg) const {
    auto ret = wptr.lock();
    if (!ret)
        throw std::runtime_error("unbound StrBlobPtr");
    if (i >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}

std::string& StrBlobPtr::deref() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr() {
    check(curr, "increment past end");
    ++curr;
    return *this;
}

bool operator==(const StrBlob& sb1, const StrBlob& sb2) { return *sb1.data == *sb2.data; }

bool operator<(const StrBlob& sb1, const StrBlob& sb2) { return *sb1.data < *sb2.data; }

bool operator>(const StrBlob& sb1, const StrBlob& sb2) { return sb2 < sb1; }

bool operator<=(const StrBlob& sb1, const StrBlob& sb2) { return !(sb1 > sb2); }

bool operator>=(const StrBlob& sb1, const StrBlob& sb2) { return !(sb1 < sb2); }

bool operator!=(const StrBlob& sb1, const StrBlob& sb2) { return !(sb1 == sb2); }

StrBlobPtr::StrBlobPtr(StrBlob& a, size_t sz): wptr(a.data), curr(sz) {}

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

std::string& StrBlobPtr::operator*() {
    auto p = check(curr, "dereference past end.");
    return (*p)[curr];
}

std::string* StrBlobPtr::operator->() { return &this->operator*(); }

bool operator==(const StrBlobPtr& sbp1, const StrBlobPtr& sbp2) {
    // check that wptrs point to the same vector and index (curr) is same.
    return sbp1.wptr.lock() == sbp2.wptr.lock() && sbp1.curr == sbp2.curr; 
}

bool operator<(const StrBlobPtr& sbp1, const StrBlobPtr& sbp2) {
    return sbp1.wptr.lock() == sbp2.wptr.lock() && sbp1.curr < sbp2.curr; 
}

bool operator>(const StrBlobPtr& sbp1, const StrBlobPtr& sbp2) { return sbp2 < sbp1; }

bool operator<=(const StrBlobPtr& sbp1, const StrBlobPtr& sbp2) { return !(sbp1 > sbp2); }

bool operator>=(const StrBlobPtr& sbp1, const StrBlobPtr& sbp2) { return !(sbp1 < sbp2); }

bool operator!=(const StrBlobPtr& sbp1, const StrBlobPtr& sbp2) { return !(sbp1 == sbp2); }
