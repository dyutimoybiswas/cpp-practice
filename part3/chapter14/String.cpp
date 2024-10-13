#include "String.hpp"

std::pair<char*, char*> String::allocate_and_copy(const char* b, const char* e) {
    char* data = char_allocator_traits::allocate(alloc, e - b);
    return std::make_pair(data, std::uninitialized_copy(b, e, data));
}

void String::free() {
    if (elements) {
        for (char* p = elements; p != first_free; char_allocator_traits::destroy(alloc, p++));
        char_allocator_traits::deallocate(alloc, elements, capacity());
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
