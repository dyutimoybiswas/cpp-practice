#include "StrVec.hpp"

StrVec& StrVec::operator=(std::initializer_list<std::string> i1) {
    auto data = alloc_and_copy(i1.begin(), i1.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
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

std::ostream& operator<<(std::ostream& os, const StrVec& sv) {
    for (auto p = sv.elements; p != sv.first_free; ++p)
        os << *p << ", ";
    return os;
}

void StrVec::push_back(const std::string& s) {
    check_and_allocate();               // ensure there is space
    allocator_traits::construct(alloc, first_free++, s);   // construct copy of s in first_free location.
}

void StrVec::push_back(const std::string&& s) {
    check_and_allocate();
    allocator_traits::construct(alloc, first_free++, std::move(s));
}

void StrVec::pop_back() {
    if (size())
        allocator_traits::destroy(alloc, --first_free);
}

std::pair<std::string*, std::string*> StrVec::alloc_and_copy(const std::string* b, const std::string* e) {
    auto data = allocator_traits::allocate(alloc, e - b);  // add space
    return {data, std::uninitialized_copy(b, e, data)};    // std::uninitialized_copy returns pointer to last element of data.
}

void StrVec::free() {
    if (elements) {     // nothing to free if no elements
        for (auto p = first_free; p != elements; /*empty*/)
            allocator_traits::destroy(alloc, --p);     // destroy in reverse order. Tip: this can be 3rd part of for loop.
        allocator_traits::deallocate(alloc, elements, cap - elements);
    }
}

StrVec::StrVec(const StrVec& s) {
    auto newData = alloc_and_copy(s.begin(), s.end());
    elements = newData.first;
    first_free = cap = newData.second;
}

StrVec& StrVec::operator=(const StrVec& rhs) {
    auto newData = alloc_and_copy(rhs.begin(), rhs.end());
    free();         // protection against self-assignment.
    elements = newData.first;
    first_free = cap = newData.second;
    return *this;
}

StrVec::StrVec(std::initializer_list<std::string> il) {
    for (const std::string& e: il)
        push_back(e);
}

#if 0
void StrVec::reallocate() {
    auto newCapacity = size() ? 2 * size() : 1;
    auto newData = allocator_traits::allocate(alloc, newCapacity);

    auto dest = newData;
    auto elem = elements;       // next element in the old array.
    for (size_t i = 0; i != size(); ++i)
        allocator_traits::construct(alloc, dest++, std::move(*elem++));
    free();
    elements = newData;
    first_free = dest;
    cap = elements + newCapacity;
}

#else
void StrVec::reallocate() {
    auto newCapacity = size() ? 2 * size() : 1;
    auto first = allocator_traits::allocate(alloc, newCapacity);

    // move the elements.
    auto last = std::uninitialized_copy(std::make_move_iterator(begin()), std::make_move_iterator(end()), first);
    free();
    elements = first;
    first_free = last;
    cap = elements + newCapacity;
}
#endif

// std::move doesn't throw exceptions
StrVec::StrVec(StrVec&& s) noexcept: elements(s.elements), first_free(s.first_free), cap(s.cap) {
    s.elements = s.first_free = s.cap = nullptr;    // safe to run destructor
}

StrVec& StrVec::operator=(StrVec&& rhs) noexcept {
    if (this != &rhs) {  // guard against self-assignment
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        // safe to run destructor
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

void StrVec::reserve(size_t n) {
    if (n > capacity()) {
        auto newData = allocator_traits::allocate(alloc, n);
        auto first_free_new = std::uninitialized_copy(elements, first_free, newData);   // wrt newData
        free();
        elements = newData;
        first_free = first_free_new;
        cap = elements + n;
    }
}

void StrVec::resize(size_t n, std::string&& val) {
    if (n > size())
        for (size_t i = size(); i < n; ++i)
            push_back(val);
    else if (n < size())
        for (size_t i = size(); i > n; --i)
            pop_back();
}
