#ifndef CHAPTER15_HPP
#define CHAPTER15_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <set>
#include <map>
#include <algorithm>

class Quote;
class Bulk_quote;
// class Bulk_quote: public Quote;    // wrong
class Disc_quote;
class Base;
class Sneaky;
class Derived;
class D;
class Basket;
class QueryResult;
class TextQuery;
class Query_base;
class Query;
class WordQuery;
class NotQuery;
class BinaryQuery;
class AndQuery;
class OrQuery;

double print_total(std::ostream&, const Quote&, std::size_t);

class Quote {
    public:
        Quote() = default;
        Quote(const std::string& book, double sales_price): bookNo(book), price(sales_price) {}
        inline std::string isbn() const { return bookNo; }
        inline virtual double net_price(std::size_t n) const { return n * price; }
        virtual void debug();
        virtual ~Quote() = default;
        // return dynamically allocated copies of the object
        virtual Quote* clone() const & { return new Quote(*this); }
        virtual Quote* clone() && { return new Quote(std::move(*this)); }
    private:
        std::string bookNo;
    protected:
        double price = 0.0;
};

class Disc_quote: public Quote {
    public:
        Disc_quote() = default;
        Disc_quote(const std::string& book, double price, std::size_t qty, double disc):
        Quote(book, price), quantity(qty), discount(disc) {}
        double net_price(std::size_t) const = 0;
        inline std::pair<std::size_t, double> discount_policy() const {
            return std::make_pair(quantity, discount);
        }
    protected:
        std::size_t quantity = 0;
        double discount = 0.0;
};

class Bulk_quote: public Disc_quote {
    public:
        Bulk_quote() = default;
        Bulk_quote(const std::string&, double, std::size_t, double);
        using Disc_quote::Disc_quote;   // example of using base class constructor
        double net_price(std::size_t) const override;
        void debug();
        ~Bulk_quote() = default;
        Bulk_quote* clone() const & { return new Bulk_quote(*this); }
        Bulk_quote* clone() && { return new Bulk_quote(std::move(*this)); }
    private:
        std::size_t min_qty = 0;
        // double discount = 0.0;   // overrides discount of Disc_quote
};

// Example of protected access.
class Base {
    public:
        inline std::size_t size() const { return n; }
    protected:
        int prot_mem;
        std::size_t n = 0;
};

class Sneaky: public Base {
    inline friend void clobber(Sneaky& s) { s.j = s.prot_mem = 0; }
    // inline friend void clobber(Base& b) { b.prot_mem = 0; }     // error
    int j;
};

// Example of making inherited private members accessible
class Derived: private Base {
    public:
        using Base::size;   // accessible outside the class, public
    protected:
        using Base::n;      // accessible by derived classes, protected
};

// Example of copy control in derived class.
class D: public Base {
    public:
        D(const D& d): Base(d) {}           // copy constructor
        D(D&& d): Base(std::move(d)) {}     // move constructor
        D& operator=(const D& rhs) { // assignment
            Base::operator=(rhs);    // assigns base members from rhs
            return *this;
        }
        ~D() {}   // Base destructor is invoked automatically
};

class Basket {
    public:
        inline void add_item(const std::shared_ptr<Quote>& sale) { items.insert(sale); }
        // to allow users to add items directly instead of converting to shared_ptr
        inline void add_item(const Quote& sale) { items.insert(std::shared_ptr<Quote>(sale.clone())); }
        inline void add_item(Quote&& sale) { items.insert(std::shared_ptr<Quote>(std::move(sale).clone())); }
        double total_receipt(std::ostream&) const;
    private:
        static bool compare(const std::shared_ptr<Quote>& lhs, const std::shared_ptr<Quote>& rhs) {
            return lhs->isbn() < rhs->isbn();
        }
        std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items {compare};
};

/**
 * Text Query: 
 * user enters a word and program returns occurrences of that word in a file, 
 * as well as actual lines where the word occurs. Also supports complex queries
 * like Query(word1) & Query(word2) | Query(word3), as well as ~Query(word4)
**/
void runQueries (std::ifstream&);

using line_no = std::vector<std::string>::size_type;

// to output query string.
std::ostream& operator<<(std::ostream&, const Query&);

class TextQuery {
    private:
        // input file
        std::shared_ptr<std::vector<std::string>> file;
        // map each word to set of lines where they occur.
        std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
    public:
        TextQuery(std::ifstream&);
        QueryResult query(const std::string&) const;
};

class QueryResult {
    friend std::ostream& print(std::ostream&, const QueryResult&);
    private:
        std::string sought;     // word entered by user
        std::shared_ptr<std::set<line_no>> lines;
        std::shared_ptr<std::vector<std::string>> file;     // input file
    public:
        QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p, 
                    std::shared_ptr<std::vector<std::string>> f): sought(s), lines(p), file(f) {}
        inline std::set<line_no>::iterator begin() { return lines->begin(); }
        inline std::set<line_no>::iterator end() { return lines->end(); }
        inline std::shared_ptr<std::vector<std::string>> get_file() { return file; }
};

// abstract base class for all query types.
class Query_base {
    friend class Query;
    protected:
        virtual ~Query_base() = default;
    private:
        // returns result matching this query.
        virtual QueryResult eval(const TextQuery&) const = 0;
        // string representation of the query.
        virtual std::string rep() const = 0;
};

// interface to manage Query_base inheritance hierarchy.
class Query {
    friend Query operator~(const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);
    public:
        Query(const std::string&);
        QueryResult eval(const TextQuery& t) const { return q->eval(t); }
        std::string rep() const { return q->rep(); }
    private:
        Query(std::shared_ptr<Query_base> query): q(query) {}
        std::shared_ptr<Query_base> q;
};

class WordQuery: public Query_base {
    friend class Query;         // Query uses WordQuery constructor
    private:
        WordQuery(const std::string& s): query_word(s) {}
        QueryResult eval(const TextQuery& t) const { return t.query(query_word); }
        std::string rep() const { return query_word; }
        std::string query_word;     // word to search
};

// handles query types like ~(word).
class NotQuery: public Query_base {
    inline friend Query operator~(const Query& operand) {
        return std::shared_ptr<Query_base>(new NotQuery(operand));
    }
    private:
        NotQuery(const Query& q): query(q) {}
        std::string rep() const { return "~(" + query.rep() + ")"; }
        QueryResult eval(const TextQuery&) const;
        Query query;
};

// abstract class for and & or queries.
class BinaryQuery: public Query_base {
    protected:
        BinaryQuery(const Query& l, const Query& r, std::string s): lhs(l), rhs(r), opSym(s) {}
        inline std::string rep() const {
            return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
        }
        // Note: eval not implemented (abstract class).
        Query lhs, rhs;        // operands
        std::string opSym;      // operator - & or |
};

// handles query(word1) & query(word2).
class AndQuery: public BinaryQuery {
    inline friend Query operator&(const Query& lhs, const Query& rhs) {
        return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
    }
    private:
        AndQuery(const Query& left, const Query& right): BinaryQuery(left, right, "&") {}
        QueryResult eval(const TextQuery&) const;
};

// handles query(word1) & query(word2).
class OrQuery: public BinaryQuery {
    inline friend Query operator|(const Query& lhs, const Query& rhs) {
        return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
    }
    private:
        OrQuery(const Query& left, const Query& right): BinaryQuery(left, right, "|") {}
        QueryResult eval(const TextQuery&) const;
};

#endif
