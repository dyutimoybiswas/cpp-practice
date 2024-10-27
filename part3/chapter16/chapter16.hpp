#ifndef CHAPTER16_HPP
#define CHAPTER16_HPP

#include <iostream>
#include <vector>
#include <initializer_list>
#include <list>
#include <memory>
#include <string>
#include <sstream>
#include <unordered_set>

class Sales_data;

// Example of function template, works even with pointers.
template<typename T> int compare(const T& v1, const T& v2) {
    if (std::less<T>()(v1, v2)) return -1;      // less
    if (std::less<T>()(v2, v1)) return 1;       // greater
    return 0;       // equal
}

// Exercise 16.4
template <typename Titer, typename Val>
Titer myFind(Titer f, Titer l, const Val v) {
    while (f != l)
        if (*(f++) == v)
            break;
    return f;
}

// Exercise 16.7
template<typename T, size_t N>
constexpr size_t size(T (&arr)[N]) {
    return N;
}

// Example of class template.
template<typename T> class Blob {
    public:
        typedef typename std::vector<T>::size_type size_type;   // typename is used to specify that T is a type (optional).
        
        Blob() = default;
        Blob(std::initializer_list<T>);
        template<typename It> Blob(It, It);
        size_type size() const { return data->size(); }
        bool empty() const { return data->empty(); }
        void push_back(const T& t) { data->push_back(t); }
        void push_back(T&& t) { data->push_back(std::move(t)); }
        void pop_back();
        T& back();
        T& operator[](size_type);
    private:
        std::shared_ptr<std::vector<T>> data;
        void check(size_type, const std::string&) const;
};

// NOTE: define all member functions of Blob in this file.
template<typename T> void Blob<T>::check(size_type i, const std::string& msg) const {
    if (i >= data->size())
        throw std::out_of_range(msg);
}

template<typename T> T& Blob<T>::back() {
    check(0, "back on empty Blob");
    return data->back();
}

template<typename T> T& Blob<T>::operator[](size_type i) {
    check(i, "subscript out of range");
    return (*data)[i];  // alternate way: data->at(i);
}

template<typename T> void Blob<T>::pop_back() {
    check(0, "pop_back on empty Blob");
    return data->pop_back();
}

template<typename T> Blob<T>::Blob(std::initializer_list<T> i1): data(std::make_shared<std::vector<T>>(i1)) { }

template<typename T>
template<typename It>
Blob<T>::Blob(It b, It e): data(std::make_shared<std::vector<T>>(b, e)) {}

// Exercise 16.16
template <typename T> class Vec;
template <typename T> using allocator_traits = std::allocator_traits<std::allocator<T>>;
template <typename T> bool operator==(const Vec<T>&, const Vec<T>&);
template <typename T> bool operator<(const Vec<T>&, const Vec<T>&);
template <typename T>
class Vec {
    friend bool operator==<T>(const Vec&, const Vec&);
    friend bool operator< <T>(const Vec&, const Vec&);
    public:
        Vec() = default;
        Vec(const Vec<T>&);
        Vec<T>& operator=(const Vec<T>&);
        Vec<T>& operator=(std::initializer_list<T>);
        Vec(Vec<T>&&) noexcept;                   // move constructor
        Vec<T>& operator=(Vec<T>&&) noexcept;     // move assignment
        void push_back(const T&);
        void push_back(const T&&);                // move element
        // number of elements in use.
        size_t size() const { return first_free - elements;}
        // number of elements Vec can hold.
        size_t capacity() const { return cap - elements;}
        // pointer to first element.
        T* begin() const { return elements; }
        // pointer to one past last element.
        T* end() const { return first_free; }
        // Chapter 14 - overloaded subscript.
        T& operator[](size_t n) { return elements[n]; }
        T& operator[](size_t n) const { return elements[n]; }
    private:
        static typename allocator_traits<T>::allocator_type alloc;
        void check_and_allocate(){   // adding elements, reallocate
            if (size() == capacity()) reallocate();
        }
        // utilized by copy constructor, assignment operator and destructor.
        std::pair<T*, T*> alloc_and_copy(const T*, const T*);
        void free();                // destroy elements and free space
        void reallocate();          // get more space and copy existing elements
        T* elements {nullptr};      // pointer to first element
        T* first_free {nullptr};    // pointer to first free element
        T* cap {nullptr};           // pointer to one past the end
};

template <typename T>
bool operator==(const Vec<T>& sv1, const Vec<T>& sv2) {
    if (sv1.size() != sv2.size())
        return false;
    #if 0
    for (auto itr1 = sv1.elements, itr2 = sv2.elements; itr1 != sv1.first_free; ++itr1, ++itr2)
        if (*itr1 != *itr2)
            return false;
    return true;
    #else
    return std::equal(sv1.begin(), sv1.end(), sv2.begin());
    #endif
}

template <typename T>
bool operator<(const Vec<T>& sv1, const Vec<T>& sv2) {
    // ref: https://cplusplus.com/reference/algorithm/lexicographical_compare/
    auto itr1 = sv1.elements, itr2 = sv2.elements;
    while(itr1 != sv1.first_free) {
        if (itr1 == sv2.first_free || *itr2 < *itr1) return false;
        else if(*itr1 < *itr2) return true;
        ++itr1; ++itr2;
    }
    return itr2 != sv2.first_free;
}

template <typename T>
Vec<T>::Vec(const Vec<T>& v) {
    auto newData = alloc_and_copy(v.begin(), v.end());
    elements = newData.first;
    first_free = cap = newData.second;
}

template <typename T>
Vec<T>& Vec<T>::operator=(const Vec<T>& rhs) {
    auto newData = alloc_and_copy(rhs.begin(), rhs.end());
    free();
    elements = newData.first;
    first_free = cap = newData.second;
    return *this;
}

template <typename T>
Vec<T>& Vec<T>::operator=(std::initializer_list<T> il) {
    auto newData = alloc_and_copy(il.begin(), il.end());
    free();
    elements = newData.first;
    first_free = cap = newData.second;
    return *this;
}

template <typename T>
Vec<T>::Vec(Vec<T>&& v) noexcept: elements(v.elements), first_free(v.first_free), cap(v.cap) {
    v.elements = v.first_free = v.cap = nullptr;    // safe to run destructor
}

template <typename T>
Vec<T>& Vec<T>::operator=(Vec<T>&& rhs) noexcept {
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

template <typename T>
void Vec<T>::push_back(const T& t) {
    check_and_allocate();               // ensure there is space
    allocator_traits<T>::construct(alloc, first_free++, t);   // construct copy of t in first_free location.
}

template <typename T>
void Vec<T>::push_back(const T&& t) {
    check_and_allocate();
    allocator_traits<T>::construct(alloc, first_free++, std::move(t));
}

template <typename T>
std::pair<T*, T*> Vec<T>::alloc_and_copy(const T* b, const T* e) {
    auto data = allocator_traits<T>::allocate(alloc, e - b);  // add space
    return {data, std::uninitialized_copy(b, e, data)};    // std::uninitialized_copy returns pointer to last element of data.
}

template <typename T>
void Vec<T>::free() {
    if (elements) {     // nothing to free if no elements
        for (auto p = first_free; p != elements; /*empty*/)
            allocator_traits<T>::destroy(alloc, --p);     // destroy in reverse order
        allocator_traits<T>::deallocate(alloc, elements, cap - elements);
    }
}

#if 0
template <typename T>
void Vec<T>::reallocate() {
    auto newCapacity = size() ? 2 * size() : 1;
    auto newData = allocator_traits<T>::allocate(alloc, newCapacity);

    auto dest = newData;
    auto elem = elements;
    for (size_t i = 0; i != size(); ++i)
        allocator_traits<T>::construct(alloc, dest++, std::move(*elem++));
    free();
    elements = newData;
    first_free = dest;
    cap = elements + newCapacity;
}

#else
template <typename T>
void Vec<T>::reallocate() {
    auto newCapacity = size() ? 2 * size() : 1;
    auto first = allocator_traits<T>::allocate(alloc, newCapacity);

    // move the elements.
    auto last = std::uninitialized_copy(std::make_move_iterator(begin()), std::make_move_iterator(end()), first);
    free();
    elements = first;
    first_free = last;
    cap = elements + newCapacity;
}
#endif

// Example of template type aliases
template<typename T> using twin = std::pair<T, T>;

// NOTE: below declarations refer to the same function.
template<typename T> T foo(T&);
template<typename U> U foo(U&);
template<typename Type> Type foo(Type&);

// Example of default parameters in function template.
template<typename T, typename F = std::less<T>>
int compare_default(const T& v1, const T& v2, F f = F()) {
    if (f(v1, v2)) return 1;
    if (f(v2, v1)) return -1;
    return 0;
}

// Example of default parameters in class template.
template<class T = int>
class Numbers {     // default is int.
    public:
        Numbers(T v = 0): val(v) {}
    private:
        T val;
};

// Example of custom deleter to unique_ptr.
class DebugDelete {
    public:
        DebugDelete(std::ostream& s = std::cerr): os(s) {}
        template<typename T> void operator()(T* p) const {
            os << "deleting unique_ptr" << std::endl;
            delete p;
        }
    private:
        std::ostream& os;
};

// Example of extern.
// extern template class Blob<std::string>;                // not instantiated here.
// extern template int compare(const int&, const int&);    // not instantiated here.

// Example of explicit template argument (T1 not present in params).
// Note that type deduction happens in order - T1, T2, T3.
template<typename T1, typename T2, typename T3>
T1 sum(T2 x, T3 y) {
    return x + y;
}

void f(int v1, int& v2) {
    std::cout << v1 << " " << ++v2 << std::endl;
}

// Example of forwarding.
template<typename F, typename T1, typename T2>
void flip1(F f, T1 t1, T2 t2) {
    f(t2, t1);      // invoke f with reverse order of args.
}

// Example of overloading templates.
template<typename T>
std::string debug_rep(const T& t) {
    std::ostringstream ret;
    ret << t;
    return ret.str();
}

template<typename T>
std::string debug_rep(T* p) {
    std::ostringstream ret;
    ret << "pointer: " << p;            // p value
    if (p)
        ret << " " << debug_rep(*p);    // value that p points to
    else
        ret << " null pointer";
    return ret.str();
}

// Example of function template with variadic parameters.
template<typename T>
std::ostream& print(std::ostream& os, const T& t) {
    return os << t;
}

template<typename T, typename... Args>
std::ostream& print(std::ostream& os, const T& t, const Args&... rest) {
    os << t << ", ";
    return print(os, rest...);      // recursive call.
}

template<typename T, typename... Args>
std::ostream& errorMsg(std::ostream& os, const Args&... rest) {
    return print(os, debug_rep(rest)...);   // print(os, debug_rep(e1), debug_rep(e2), ... debug_rep(en))
}

// Example of template specialization classes.
namespace std {     // to use std::hash  
    
    template<class T> class hash;
    class Sales_data{
        friend class hash<Sales_data>;
        public:
            friend inline bool operator==(const Sales_data& lhs, const Sales_data& rhs) {
                return lhs.bookNo == rhs.bookNo && 
                    lhs.units_sold == rhs.units_sold && 
                    lhs.revenue == rhs.revenue;
            }
        private:
            std::string bookNo;
            unsigned units_sold;
            double revenue;
    };
    
    template<>
    struct hash<Sales_data> {
        typedef size_t result_type;
        typedef Sales_data argument_type;
        size_t operator()(const Sales_data&) const;
    };

    size_t hash<Sales_data>::operator()(const Sales_data& s) const {
        // creating hash key for comparison.
        return hash<string>()(s.bookNo) ^
               hash<unsigned>()(s.units_sold) ^
               hash<double>()(s.revenue);
    }
}

std::unordered_multiset<std::Sales_data> SDset;  // uses hash function to compare elements.

#endif
