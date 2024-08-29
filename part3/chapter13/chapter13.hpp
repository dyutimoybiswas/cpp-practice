#ifndef CHAPTER13_HPP
#define CHAPTER13_HPP

#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <stdexcept>

class HasPtr {
    public:
        // each object's ps member will have its own copy of string s.
        HasPtr(const HasPtr& hp, const std::string& s = std::string(), int x = 0) 
        : ps(new std::string(s)), i(x), use(new std::size_t(1)) { }
        
        // Exercise 13.5
        HasPtr(const HasPtr& hp) 
        : ps(new std::string(*hp.ps)), i(hp.i), use(hp.use) { }

        HasPtr& operator=(const HasPtr&);
        HasPtr& operator=(HasPtr);      // passed by value
        friend void swap(HasPtr&, HasPtr&);

        // move constructor.
        HasPtr(HasPtr&& hp): ps(new std::string(*hp.ps)), i(hp.i), use(hp.use) {
            hp.ps = nullptr;
            hp.use = nullptr;
            hp.i = 0;
        }

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
        Employee& operator=(const Employee& e){
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
        Message(Message&&);                     // move constructor
        Message& operator=(Message&&);          // move assignment
        void save(Folder&);                     // store messages
        void remove(Folder&);                   // delete messages
};

// Exercise 13.36
class Folder {
    friend class Message;
    friend void swap(Message&, Message&);
    friend void swap(Folder&, Folder&);
    private:
        std::set<Message*> msgs;
        void addMsg(Message* msg) { msgs.insert(msg); }
        void remMsg(Message* msg) { msgs.erase(msg); }
    public:
        Folder() = default;
        Folder(const Folder&);
        Folder& operator=(const Folder&);
        ~Folder();
        void save(Message&);
        void remove(Message&);
};

using allocator_traits = std::allocator_traits<std::allocator<std::string>>;

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
        inline void check_and_allocate(){   // adding elements, reallocate
            if (size() == capacity()) reallocate();
        }
        // utilized by copy constructor, assignment operator and destructor.
        std::pair<std::string*, std::string*> alloc_and_copy(const std::string*, const std::string*);
        void free();                // destroy elements and free space
        void reallocate();          // get more space and copy existing elements
        std::string* elements;      // pointer to first element
        std::string* first_free;    // pointer to first free element
        std::string* cap;            // pointer to one past the end
    public:
        StrVec(): elements(nullptr), first_free(nullptr), cap(nullptr) {}
        StrVec(const StrVec&);
        StrVec& operator=(const StrVec&);
        StrVec& operator=(std::initializer_list<std::string>);
        StrVec(StrVec&&) noexcept;                // move constructor
        StrVec& operator=(StrVec&&) noexcept;     // move assignment
        inline ~StrVec() { free(); }
        void push_back(const std::string&);
        void push_back(const std::string&&);    // move element
        // number of elements in use.
        inline size_t size() const { return first_free - elements;}
        // number of elements StrVec can hold.
        inline size_t capacity() const { return cap - elements;}
        // pointer to first element.
        inline std::string* begin() const { return elements; }
        // pointer to one past last element.
        inline std::string* end() const { return first_free; }
        // Chapter 14 - overloaded subscript.
        inline std::string& operator[](std::size_t n) { return elements[n]; }
        inline std::string& operator[](std::size_t n) const { return elements[n]; }
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
