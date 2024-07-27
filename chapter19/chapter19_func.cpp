#include "chapter19.hpp"

void* operator new(size_t size) {
    if (void* mem = std::malloc(size))
        return mem;
    else
        throw std::bad_alloc();
}

void operator delete(void* mem) noexcept {
    std::free(mem);
}

bool operator==(const Base& lhs, const Base& rhs) {
    return typeid(lhs) == typeid(rhs) && lhs.equal(rhs);
}

bool Base::equal(const Base& b) const {
    // logic for members equality.
    return true;
}

bool Derived::equal(const Base& b) const {
    auto d = dynamic_cast<const Derived&>(b);   // converts to reference of derived type.
    // logic for members equality.
    return true;
}

// check discriminant value and copy union member as appropriate.
void Token::copyUnion(const Token& t) {
    switch(t.tok) {
        case Token::INT:
            ival = t.ival;
            break;
        case Token::CHAR:
            cval = t.cval;
            break;
        case Token::DBL:
            dval = t.dval;
            break;
        case Token::STR:
            new(&sval) std::string(t.sval);
            break;
    }
}

// TODO: char, double overloads.
Token& Token::operator=(int i) {
    if (tok == STR)
        sval.~basic_string();
    ival = i;
    tok = INT;
    return *this;
}

Token& Token::operator=(const std::string& s) {
    if (tok == STR)
        sval = s;   // assign if already holding a string
    else
        new(&sval) std::string(s);  // construct a string otherwise
    tok = STR;
    return *this;
}

Token& Token::operator=(const Token& t) {
    if (tok == STR && t.tok != STR)
        sval.~basic_string();
    if (tok == STR && t.tok == STR)
        sval = t.sval;
    else
        copyUnion(t);
    tok = t.tok;
    return *this;
}