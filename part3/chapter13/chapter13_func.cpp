#include "chapter13.hpp"

#ifdef IMPL1
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

// uses swap.
HasPtr& HasPtr::operator=(HasPtr rhs) {
    swap(*this, rhs);   // swaps lhs & rhs
    return *this;       // returns lhs, rhs is destroyed as control goes out of scope.
}

inline void swap(HasPtr& lhs, HasPtr& rhs) {
    std::swap(lhs.ps, rhs.ps);
    std::swap(lhs.i, rhs.i);
}

HasPtr::~HasPtr() {
    // decrement ref count, and if it's 0, free resources.
    if (--*use == 0) {
        delete ps;
        delete use;
    }
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

#ifdef IMPL1
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

#else
void StrVec::reallocate() {
    auto newCapacity = size() ? 2 * size() : 1;
    auto first = alloc.allocate(newCapacity);

    // move the elements.
    auto last = std::uninitialized_copy(std::make_move_iterator(begin), std::make_move_iterator(end), first);
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