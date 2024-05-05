#ifndef CHAPTER13_HPP
#define CHAPTER13_HPP

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

// Exercise 13.5 - TODO: verify
class HasPtr {
    private:
        std::string *ps;
        int i;
    public:
        HasPtr(const HasPtr& hp, const std::string& s = std::string(), int x = 0) : ps(new std::string(s)), i(x) { }
        HasPtr(const HasPtr& hp) : ps(hp.ps), i(hp.i) { }
        HasPtr& operator=(const HasPtr&);
        // Exercise 13.11
        ~HasPtr() {
            delete ps;
        }
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
// Exercise 13.36 - TODO: verify
class Folder {
    private:
        std::vector<Message*> msg;
    public:
        void addMsg(Message* m) {
            msg.push_back(m);
        }
        void remMsg(Message* m) {
            auto it = std::find(msg.cbegin(), msg.cend(), m);
            if (it == msg.cend())
                throw std::out_of_range("Message not found in folder!");
            msg.erase(it);
        }
};

// Example - custom vector class
class StrVec {
    private:
        static std::allocator<std::string> alloc;
        inline void check_and_allocate();   // adding elements, reallocate
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
        StrVec(StrVec&&);                // move constructor
        StrVec& operator=(StrVec&&);     // move assignment
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
};
std::allocator<std::string>StrVec::alloc;

#endif
