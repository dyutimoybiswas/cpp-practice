#ifndef CHAPTER16_HPP
#define CHAPTER16_HPP

#include <iostream>
#include <vector>
#include <initializer_list>
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

// TODO: verify - Exercise 16.7
template<typename T> constexpr std::size_t size(const T* arr) {
    return sizeof(arr) / sizeof(T);
}

// Example of class template.
template<typename T> class Blob {
    public:
        typedef T value_type;
        // TODO: difference between below declarations.
        // typedef typename std::vector<T>::size_type size_type;
        typedef std::vector<T>::size_type size_type;
        
        Blob();
        Blob(std::initializer_list<T>);
        template<typename It> Blob(It, It);
        inline size_type size() const { return data->size(); }
        inline bool empty() const { return data->empty(); }
        inline void push_back(const T& t) { data->push_back(t); }
        inline void push_back(T&& t) { data->push_back(std::move(t)); }
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
    return (*data)[i];
}

template<typename T> void Blob<T>::pop_back() {
    check(0, "pop_back on empty Blob");
    return data->pop_back();
}

template<typename T> Blob<T>::Blob(): data(std::make_shared<std::vector<T>>()) { }

template<typename T> Blob<T>::Blob(std::initializer_list<T> i1): data(std::make_shared<std::vector<T>>(i1)) { }

template<typename T>
template<typename It>
Blob<T>::Blob(It b, It e): data(std::make_shared<std::vector<T>>(b, e)) {}

// Example of template type aliases
template<typename T> using twin = std::pair<T, T>;

// NOTE: below declarations refer to the same function.
template<typename T> T foo(T&);
template<typename U> U foo(U&);
template<typename Type> Type foo(Type&);

// Example of default parameters in function template.
template<typename T, typename F = std::less<T>>
int compare_default(const T& v1, const T& v2, F f = F()) {
    if (f(v1, v2)) return -1;
    if (f(v2, v1)) return -1;
    return 0;
}

// Example of default parameters in class template.
template<class T = int> class Numbers {     // default is int.
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
