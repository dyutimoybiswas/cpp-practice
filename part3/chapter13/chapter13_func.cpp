#include "chapter13.hpp"
#include <memory>

#if 1
HasPtr& HasPtr::operator=(const HasPtr& rhs) {
    // copy is done to prevent undefined behavior when lhs and rhs are the same object
    // i.e. when an object is assigned to itself.
    auto newp = new std::string(*rhs.ps);
    // delete lhs ps and redefine them from rhs
    delete ps;
    ps = newp;
    i = rhs.i;
    return *this;   // lhs
}

#else
HasPtr& HasPtr::operator=(const HasPtr& rhs) {
    ++*rhs.use; // increment ref count
    // if lhs = rhs, use will become 0. Then free members before copying.
    if (--*use == 0) {
        delete ps;
        delete use;
    }
    // copying
    ps = rhs.ps;
    i = rhs.i;
    use = rhs.use;
    return *this;
}
#endif

#ifdef EXERCISE11
HasPtr::~HasPtr() {
    delete ps;
}

#else
HasPtr::~HasPtr() {
    // decrement ref count, and if it's 0, free resources.
    if (--*use == 0) {
        delete ps;
        delete use;
    }
}
#endif

// uses swap.
HasPtr& HasPtr::operator=(HasPtr&& rhs) noexcept {
    swap(*this, rhs);   // swaps lhs & rhs
    return *this;       // returns lhs, rhs is destroyed as control goes out of scope.
}

inline void swap(HasPtr& lhs, HasPtr& rhs) {
    std::swap(lhs.ps, rhs.ps);
    std::swap(lhs.i, rhs.i);
}

void Message::save(Folder& f) {
    folders.insert(&f);
    f.addMsg(this);
}

void Message::remove(Folder& f) {
    folders.erase(&f);
    f.remMsg(this);
}

void Message::addToFolders(const Message& m) {
    for (auto f: m.folders) 
        f->addMsg(this);
}

Message::Message(const Message& m): contents(m.contents), folders(m.folders) {
    addToFolders(m);
}

void Message::removeFromFolders() {
    for (auto f: folders) 
        f->remMsg(this);
    folders.clear();
}

void Message::moveFolders(Message* m) {
    folders = std::move(m->folders);
    for (auto f: folders) {
        f->remMsg(m);       // remove old message from folder
        f->addMsg(this);    // add 'this' message.
    }
    m->folders.clear();
}

Message::~Message() {
    // not marked as noexcept as allocation might throw bad_alloc exception.
    removeFromFolders();
}

Message::Message(Message&& m) noexcept : contents(m.contents) {
    moveFolders(&m);
}

Message& Message::operator=(Message&& rhs) noexcept {
    if (this != &rhs) {              // check for self-assignment
        removeFromFolders();
        contents = rhs.contents;     // move assignment
        moveFolders(&rhs);
    }
    return *this;
}

Message& Message::operator=(const Message& rhs) {
    removeFromFolders();
    contents = rhs.contents;
    folders = rhs.folders;
    addToFolders(rhs);
    return *this;
}

void swap(Message& lhs, Message& rhs) {
    using std::swap;
    for (auto f: lhs.folders)
        f->remMsg(&lhs);
    for (auto f: rhs.folders)
        f->remMsg(&rhs);
    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);
    for (auto f: lhs.folders)
        f->addMsg(&lhs);
    for (auto f: rhs.folders)
        f->addMsg(&rhs);
}

void swap(Folder& lhs, Folder& rhs) {
    using std::swap;
    for(auto& msg: lhs.msgs)
        msg->folders.erase(&lhs);
    for(auto& msg: rhs.msgs)
        msg->folders.erase(&rhs);
    swap(lhs.msgs, rhs.msgs);
    for(auto& msg: lhs.msgs)
        msg->folders.insert(&lhs);
    for(auto& msg: rhs.msgs)
        msg->folders.insert(&rhs);
}

Folder::Folder(const Folder& f): msgs(f.msgs) {
    for(auto& msg: msgs)
        msg->folders.insert(this);
}

Folder& Folder::operator=(const Folder& f) {
    for(auto& msg: msgs)
        msg->folders.erase(this);
    this->msgs = f.msgs;
    for(auto& msg: f.msgs)
        msg->folders.insert(this);
    return *this;
}

Folder::~Folder() {
    for(auto& msg: msgs)
        msg->folders.erase(this);
}

void Folder::save(Message& msg) {
    addMsg(&msg);
    msg.folders.insert(this);
}

void Folder::remove(Message& msg) {
    remMsg(&msg);
    msg.folders.erase(this);
}

void StrVec::push_back(const std::string& s) {
    check_and_allocate();               // ensure there is space
    allocator_traits::construct(alloc, first_free++, s);   // construct copy of s in first_free location. TODO: why not std::move(s)?
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
        #ifdef EXERCISE43
        std::for_each(elements, first_free, [](std::string* p) { allocator_traits::destroy(alloc, p); })
        #else
        for (auto p = first_free; p != elements; /*empty*/)
            allocator_traits::destroy(alloc, --p);     // destroy in reverse order. Tip: this can be 3rd part of for loop.
        #endif
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

// Exercise 13.40
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

// Exercise 13.39
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

// Exercise 13.47
String::String(const String& s) {
    std::cout << "copy constructor" << std::endl;
    auto newData = allocate_and_copy(s.begin(), s.end());
    elements = newData.first;
    cap = first_free = newData.second;
}

// Exercise 13.49
String::String(String&& s) noexcept: elements(s.elements), first_free(s.first_free), cap(s.cap) {
    std::cout << "move constructor" << std::endl;       // Exercise 13.50
    s.elements = s.first_free = s.cap = nullptr;
}

// Exercise 13.47
String& String::operator=(const String& s) {
    std::cout << "copy assignment" << std::endl;
    auto newData = allocate_and_copy(s.begin(), s.end());
    free();
    elements = newData.first;
    cap = first_free = newData.second;
    return *this;
}

// Exercise 13.49
String& String::operator=(String&& s) noexcept {
    std::cout << "move assignment" << std::endl;       // Exercise 13.50
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

// Exercise 13.51 - function returns rvalue.
std::unique_ptr<int> clone(int p) {
    return std::make_unique<int>(p);
}

// this is rvalue, so sorted in-place.
Foo Foo::sorted() && {
    std::sort(data.begin(), data.end());
    return *this;
}

// this is either const or lvalue, cannot sort in-place.
Foo Foo::sorted() const & {
    Foo ret(*this);
    sort(ret.data.begin(), ret.data.end());
    return ret;
}
