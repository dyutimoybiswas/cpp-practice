#ifndef CHAPTER18_HPP
#define CHAPTER18_HPP

#include <initializer_list>
#include <memory>
#include <vector>
#include <exception>
#include <stdexcept>
#include <string>
#include <iostream>

// Example of namespace usage.
namespace cplusplus_primer {
    template<typename T> class Blob {
        public:
            // Example of constrcutor raising exception.
            Blob(std::initializer_list<T> i1) try: 
            data(std::make_shared<std::vector<T>>(i1)) {
            } catch (const std::bad_alloc& e) {
                // handle out of memory.
            }
        private:
            std::shared_ptr<std::vector<T>> data;
    };

    // Example of nested namespace.
    namespace custom_exceptions {
        // Example of custom exception class (wrt a bookstore).
        class out_of_stock: public std::runtime_error {
            public:
                explicit out_of_stock(const std::string& s):
                        std::runtime_error(s) { }
        };
        class isbn_mismatch: public std::logic_error {
            public:
                explicit isbn_mismatch(const std::string& s):
                        std::logic_error(s) { }
                explicit isbn_mismatch(const std::string& s, const std::string& lhs, const std::string& rhs):
                            std::logic_error(s), left(lhs), right(rhs) { }
                const std::string left, right;
        };
    }

    class Sales_data {
        friend std::ostream& operator<<(std::ostream&, const Sales_data&);
        friend std::istream& operator>>(std::istream&, Sales_data&);
        friend Sales_data operator+(const Sales_data&, const Sales_data&);
        public:
            Sales_data(unsigned int units = 0, double rev = 0.0, std::string bNo = "test-123"): 
            units_sold(units), revenue(rev), bookNo(bNo) { }
            Sales_data(std::string b): bookNo(b) {}
            Sales_data& operator+=(const Sales_data&);
        private:
            std::string isbn() const { return bookNo; }
            unsigned int units_sold;
            double revenue;
            double avg_price() const { return units_sold ? revenue / units_sold : 0; }
            std::string bookNo;
    };

    // Example of multiple inheritance.
    class ZooAnimal {
        public:
            virtual std::string animalName() const noexcept = 0;
    };
    class Endangered {
        public:
            Endangered(unsigned int cat): category(cat) {}
            const static unsigned int leastConcern = 0;
            const static unsigned int critical = 1;
            const static unsigned int extinct = 2;
        private:
            unsigned int category;
    };
    // Example of virtual inheritance.
    class Bear: public virtual ZooAnimal {
        public:
            Bear(std::string name, bool onExhibit): name(name), onExhibit(onExhibit) {}
            Bear() = default;
            std::string animalName() const noexcept { return name; }
        private:
            std::string name;
            bool onExhibit;
    };
    class Raccoon: public virtual ZooAnimal {
        public:
            Raccoon(std::string name, bool onExhibit): name(name), onExhibit(onExhibit) {}
            Raccoon() = default;
            std::string animalName() const noexcept { return name; }
        private:
            std::string name;
            bool onExhibit;
    };
    class Panda: public Bear, public Raccoon, public Endangered {
        public:
            Panda(std::string, bool);
            Panda();
            std::string animalName() const noexcept { return name; }
        private:
            std::string name;
            bool onExhibit;
    };
}

// Example of unnamed namespace.
namespace local {
    namespace {
        int i;
    }
}

// Example of functions with parameters getting called but not those without parameters.
namespace A {
    class C {
        friend void f2();           // won't be called unless defined
        friend void f(const C& obj) {}    // will be called even without definition
    };
}

namespace mathlib {
    namespace matrixLib {
        class matrix {};
        matrix operator*(const matrix&, const matrix&);
    }
}

#endif
