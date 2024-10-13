#include <string>
#include <ostream>
#include <memory>

using allocator_traits = std::allocator_traits<std::allocator<std::string>>;

// Example - custom vector class
class StrVec {
    friend bool operator==(const StrVec&, const StrVec&);
    friend bool operator!=(const StrVec&, const StrVec&);
    friend bool operator<(const StrVec&, const StrVec&);
    friend bool operator>(const StrVec&, const StrVec&);
    friend bool operator<=(const StrVec&, const StrVec&);
    friend bool operator>=(const StrVec&, const StrVec&);
    friend std::ostream& operator<<(std::ostream&, const StrVec&);
    private:
        static allocator_traits::allocator_type alloc;
        void check_and_allocate(){   // adding elements, reallocate
            if (size() == capacity()) reallocate();
        }
        // utilized by copy constructor, assignment operator and destructor.
        std::pair<std::string*, std::string*> alloc_and_copy(const std::string*, const std::string*);
        void free();                // destroy elements and free space
        void reallocate();          // get more space and copy existing elements
        std::string* elements {nullptr};      // pointer to first element
        std::string* first_free {nullptr};    // pointer to first free element
        std::string* cap {nullptr};           // pointer to one past the end
    public:
        StrVec() = default;
        StrVec(const StrVec&);
        StrVec(std::initializer_list<std::string>);
        StrVec& operator=(const StrVec&);
        StrVec& operator=(std::initializer_list<std::string>);
        StrVec(StrVec&&) noexcept;                // move constructor
        StrVec& operator=(StrVec&&) noexcept;     // move assignment
        ~StrVec() { free(); }
        void push_back(const std::string&);
        void push_back(const std::string&&);    // move element
        void pop_back();
        // number of elements in use.
        size_t size() const { return first_free - elements;}
        // pointer to first element.
        std::string* begin() const { return elements; }
        // pointer to one past last element.
        std::string* end() const { return first_free; }
        void reserve(size_t);
        size_t capacity() const { return cap - elements; }    // number of elements StrVec can hold.
        void resize(size_t, std::string&& = "");
        // overloaded subscript.
        std::string& operator[](std::size_t n) { return elements[n]; }
        std::string& operator[](std::size_t n) const { return elements[n]; }

        // void peek() { for (auto p = begin(); p != end(); ++p) std::cout << *p << std::endl; }    // debug
};
