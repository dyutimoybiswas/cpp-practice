#include "chapter13.hpp"

HasPtr& HasPtr::operator=(const HasPtr& rhs) {
    // copy is done to prevent undefined behavior when lhs and rhs are the same object
    auto newp = new std::string(*rhs.ps);
    // delete lhs ps and redefine them from rhs
    delete ps;
    ps = newp;
    i = rhs.i;
    return *this;   // lhs
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
    removeFromFolders();
}

Message::Message(Message&& m): contents(std::move(m.contents)) {
    moveFolders(&m);
}

Message& Message::operator=(Message&& rhs) {
    if (this != &rhs) {         // check for self-assignment
        removeFromFolders();
        contents = std::move(rhs.contents);     // move assignment
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

void StrVec::push_back(const std::string& s) {
    check_and_allocate();               // ensure there is space
    alloc.construct(first_free++, s);   // construct copy of s in first_free location.
}

void StrVec::push_back(const std::string&& s) {
    check_and_allocate();
    alloc.construct(first_free++, std::move(s));
}

std::pair<std::string*, std::string*> StrVec::alloc_and_copy(const std::string* b, const std::string* e) {
    auto data = alloc.allocate(e - b);  // add space
    return {data, std::uninitialized_copy(b, e, data)};
}

void StrVec::free() {
    if (elements) {     // nothing to free if no elements
        for (auto p = first_free; p != elements; /*empty*/)
            alloc.destroy(--p);     // destroy in reverse order
        alloc.deallocate(elements, cap - elements);
    }
}

StrVec::StrVec(const StrVec& s) {
    auto newData = alloc_and_copy(s.begin(), s.end());
    elements = newData.first;
    first_free = cap = newData.second;
}

StrVec& StrVec::operator=(const StrVec& rhs) {
    auto newData = alloc_and_copy(rhs.begin(), rhs.end());
    free();
    elements = newData.first;
    first_free = cap = newData.second;
    return *this;
}

void StrVec::reallocate() {
    auto newCapacity = size() ? 2 * size() : 1;
    auto newData = alloc.allocate(newCapacity);

    auto dest = newData;
    auto elem = elements;
    for (size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    free();
    elements = newData;
    first_free = dest;
    cap = elements + newCapacity;
}

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

