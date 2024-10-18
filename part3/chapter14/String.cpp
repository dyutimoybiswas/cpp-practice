#include "String.hpp"

std::pair<char*, char*> String::allocate_and_copy(const char* b, const char* e) {
    char* data = char_allocator_traits::allocate(alloc, e - b);
    return std::make_pair(data, std::uninitialized_copy(b, e, data));
}

void String::free() {
    if (elements) {
        for (char* p = elements; p != first_free; char_allocator_traits::destroy(alloc, p++));
        char_allocator_traits::deallocate(alloc, elements, capacity());
        elements = first_free = cap = nullptr;
    }
}

void String::reallocate() {
    size_t newCapacity = size() ? 2 * size() : 1;
    char* newData = char_allocator_traits::allocate(alloc, newCapacity);

    char* e = elements;
    char* dest = newData;
    while (e != first_free)
        char_allocator_traits::construct(alloc, dest++, std::move(*e++));

    free();     // deallocate current memory
    elements = newData;
    first_free = dest;      // should be allocated wrt newData.
    cap = elements + newCapacity;
}

String::String(const char* s) {
    std::cout << "C style string constructor" << std::endl;
    size_t len = 0;
    while (s[len]) ++len;
    auto newData = allocate_and_copy(s, s + len);
    elements = newData.first;
    cap = first_free = newData.second;
}

String::String(std::initializer_list<char> il) {
    auto newData = allocate_and_copy(il.begin(), il.end());
    elements = newData.first;
    cap = first_free = newData.second;
}

String::String(const String& s) {
    std::cout << "copy constructor" << std::endl;
    auto newData = allocate_and_copy(s.begin(), s.end());
    elements = newData.first;
    cap = first_free = newData.second;
}

String::String(String&& s) noexcept: elements(s.elements), first_free(s.first_free), cap(s.cap) {
    std::cout << "move constructor" << std::endl;
    s.elements = s.first_free = s.cap = nullptr;
}

String& String::operator=(const String& s) {
    std::cout << "copy assignment" << std::endl;
    auto newData = allocate_and_copy(s.begin(), s.end());
    free();
    elements = newData.first;
    cap = first_free = newData.second;
    return *this;
}

String& String::operator=(String&& s) noexcept {
    std::cout << "move assignment" << std::endl;
    if (this != &s) {
        free();
        elements = s.elements;
        first_free = s.first_free;
        cap = s.cap;
        s.elements = s.first_free = s.cap = nullptr;
    }
    return *this;
}

void String::push_back(const char ch) {
    check_and_allocate();
    char_allocator_traits::construct(alloc, first_free++, ch);
}

void String::pop_back() {
    if (size())
        char_allocator_traits::destroy(alloc, --first_free);
}

void String::reserve(size_t n) {
    if (n > capacity()) {
        char* newData = char_allocator_traits::allocate(alloc, n);
        char* first_free_new = std::uninitialized_copy(elements, first_free, newData);
        free();
        elements = newData;
        first_free = first_free_new;
        cap = elements + n;
    }
}

void String::resize(size_t n, char ch) {
    if (n > size())
        for (size_t i = size(); i < n; ++i)
            push_back(ch);
    else if (n < size())
        for (size_t i = size(); i > n; --i)
            pop_back();
}

std::ostream& operator<<(std::ostream& os, const String& s) {
    for (char* p = s.elements; p != s.first_free; ++p)
        os << *p;
    return os;
}

std::istream& operator>>(std::istream& is, String& s) {
    s.free();
    char ch;
    while (is >> ch)
        s.push_back(ch);
    return is;
}

bool operator==(const String& s1, const String& s2) {
    if (s1.size() != s2.size())
        return false;
    #if 0
    for (auto itr1 = s1.elements, itr2 = s2.elements; itr1 != s1.first_free; ++itr1, ++itr2)
        if (*itr1 != *itr2)
            return false;
    return true;
    #else
    return std::equal(s1.begin(), s1.end(), s2.begin());
    #endif
}

bool operator!=(const String& s1, const String& s2) { return !(s1 == s2); }

bool operator<(const String& s1, const String& s2) {
    char *itr1 = s1.elements, *itr2 = s2.elements;
    while(itr1 != s1.first_free) {
        if (itr1 == s2.first_free || *itr2 < *itr1) return false;
        else if(*itr1 < *itr2) return true;
        ++itr1; ++itr2;
    }
    return itr2 != s2.first_free;
}

bool operator<=(const String& s1, const String& s2) { return s1 < s2 || s1 == s2; }

bool operator>(const String& s1, const String& s2) { return s2 < s1; }

bool operator>=(const String& s1, const String& s2) { return s1 > s2 || s1 == s2; }

// TODO: optimize below using chatgpt.
String operator+(const String& s, char ch) {
    String result = s;
    result += ch;
    return result;
}

String operator+(char ch, const String& s) {
    String result;
    result += ch;
    result += s;
    return result;
}

String operator+(const String& s1, const String& s2) {
    String result = s1;
    result += s2;
    return result;
}

String& String::operator+=(char ch) {
    (*this).push_back(ch);
    return *this;
}

String& String::operator+=(const String& s) {
    for (const_iterator p = s.cbegin(); p != s.cend(); ++p)
        (*this).push_back(*p);
    return *this;
}
