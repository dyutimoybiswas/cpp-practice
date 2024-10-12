#ifndef CHAPTER13_HPP
#define CHAPTER13_HPP

#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>

class HasPtr {
    public:
        // each object's ps member will have its own copy of string s.
        HasPtr(const std::string& s = std::string(), int x = 0) 
        : ps(new std::string(s)), i(x), use(new std::size_t(1)) { }
        
        // Exercise 13.5
        HasPtr(const HasPtr& hp) 
        : ps(new std::string(*hp.ps)), i(hp.i), use(hp.use) { }

        HasPtr& operator=(const HasPtr&);
        HasPtr& operator=(HasPtr&&) noexcept;      // move assignment.
        friend void swap(HasPtr&, HasPtr&);

        // move constructor.
        HasPtr(HasPtr&& hp) noexcept : ps(new std::string(*hp.ps)), i(hp.i), use(hp.use) { }

        ~HasPtr();
    private:
        std::string *ps;
        int i;
        std::size_t* use;   // reference counter
};

// Exercise 13.18 & 13.19
class Employee {
    public:
        Employee() { ++id; }
        Employee(const std::string& n): name(n) { ++id; }

        // without copy control below, id is not updated beyond 1 (corresponding to 1st created object).
        Employee(const Employee& e): name(e.name) { ++id; }
        Employee& operator=(const Employee& e) {
            this->name = e.name;
            ++id;
            return *this;
        }

        static unsigned int getID() { return id; }
        std::string& getName() const { return const_cast<std::string&>(name); }
    private:
        std::string name;
        static unsigned int id;
};

// Example of explicit constructors.
class MyClass {
    public:
        MyClass() = default;
        // MyClass (int member): mem(member) { }        // this allows initialization like - MyClass m = 10;
        explicit MyClass (int member): mem(member) { }  // this doesn't
        MyClass(char) = delete;                         // prevents type conversion from char to int
    private:
        int mem;
};

/**Example - copy control
 * Message class contains emails and/or other messages
 * Folder class is analogous to a directory containing messages
**/
class Message;
class Folder;
class Message {
    friend class Folder;
    friend void swap(Message&, Message&);
    friend void swap(Folder&, Folder&);
    private:
        std::string contents;               // messages, etc
        std::set<Folder*> folders;          // folders holding this message
        void addToFolders(const Message&);  // add this message to all Folders in param.folders 
        void removeFromFolders();           // remove this message from all Folders in folders
        void moveFolders(Message*);         // moves Folder pointers to 'this'.
    public:
        explicit Message(const std::string& str = "") : contents(str) {}    // initialize empty set
        Message(const Message&);                // copy constructor
        Message& operator=(const Message&);     // copy assignment
        ~Message();                             // destructor
        Message(Message&&) noexcept;            // move constructor
        Message& operator=(Message&&) noexcept; // move assignment
        void save(Folder&);                     // store messages in folders
        void remove(Folder&);                   // delete messages from folders
};

// Exercise 13.36
class Folder {
    friend class Message;
    friend void swap(Message&, Message&);
    friend void swap(Folder&, Folder&);
    private:
        std::string name;
        std::set<Message*> msgs;
        void addMsg(Message* msg) { msgs.insert(msg); }
        void remMsg(Message* msg) { msgs.erase(msg); }
    public:
        Folder(const std::string& n = "test"): name(n) { }
        Folder(const Folder&);
        Folder& operator=(const Folder&);
        ~Folder();
        void save(Message&);
        void remove(Message&);
};

using allocator_traits = std::allocator_traits<std::allocator<std::string>>;
using char_allocator_traits = std::allocator_traits<std::allocator<char>>;

// Example - custom vector class
class StrVec {
    // Chapter 14.
    friend bool operator==(const StrVec&, const StrVec&);
    friend bool operator!=(const StrVec&, const StrVec&);
    friend bool operator<(const StrVec&, const StrVec&);
    friend bool operator>(const StrVec&, const StrVec&);
    friend bool operator<=(const StrVec&, const StrVec&);
    friend bool operator>=(const StrVec&, const StrVec&);
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
        // Exercise 13.39
        void reserve(size_t);
        size_t capacity() const { return cap - elements; }    // number of elements StrVec can hold.
        void resize(size_t, std::string&& = "");
        // Chapter 14 - overloaded subscript.
        std::string& operator[](std::size_t n) { return elements[n]; }
        std::string& operator[](std::size_t n) const { return elements[n]; }

        void peek() { for (auto p = begin(); p != end(); ++p) std::cout << *p << std::endl; }    // debug
};

// Exercise 13.44 - custom string class
class String {
    private:
        using iterator = char*;
        using const_iterator = const char*;
        char* elements {nullptr};     // current position
        char* first_free {nullptr};   // one past last assigned
        char* cap {nullptr};          // last position of allocated memory
        static char_allocator_traits::allocator_type alloc;
        void check_and_allocate() { if (size() == capacity()) reallocate(); }
        void free();                // destroy elements and free space
        void reallocate();          // get more space and copy existing elements
        std::pair<char*, char*> allocate_and_copy(const char*, const char*);
    public:
        // constructors.
        String() = default;
        String(const char*);
        String(std::initializer_list<char>);
        
        // copy control - needed when we have traditional pointers as class members.
        String(const String&);
        String(String&&) noexcept;
        String& operator=(const String&);
        String& operator=(String&&) noexcept;
        ~String() { free(); }

        // modifiers.
        size_t size() const noexcept { return first_free - elements; }
        size_t capacity() const noexcept { return cap - elements; }
        void resize(size_t, char=' ');
        void reserve(size_t);
        bool empty() const noexcept { return elements == first_free; }
        void push_back(const char);
        void pop_back();

        // iterators.
        iterator begin() const noexcept { return elements; }
        iterator end() const noexcept { return first_free; }
        const_iterator cbegin() const noexcept { return const_cast<char*>(elements); }
        const_iterator cend() const noexcept { return const_cast<char*>(first_free); }

        void peek() { for (char* p = elements; p != first_free; ++p) std::cout << *p << std::endl; }   // debug
};

// Example - lvalue and rvalue reference member functions.
class Foo {
    public:
        Foo() = default;
        Foo(std::vector<int> d): data(d) {}
        Foo& operator=(const Foo&) &;   // result can only be an lvalue.
        Foo sorted() &&;        // run on modifiable rvalues
        Foo sorted() const &;   // run on any object
        Foo& retFoo() & { return *this; }   // can only be invoked by lvalue
        Foo retVal() { return *this; }
        Foo retBar() && { return *this; }   // can only be invoked by rvalue
    private:
        std::vector<int> data;
};

#endif
