#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <initializer_list>

class StrBlob;
typedef std::vector<std::string>::size_type size_type;

class StrBlobPtr {
    // Chapter 14.
    friend bool operator==(const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator!=(const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator<(const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator>(const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator<=(const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator>=(const StrBlobPtr&, const StrBlobPtr&);
    private:
        std::shared_ptr<std::vector<std::string>> check (std::size_t, const std::string&) const;
        std::weak_ptr<std::vector<std::string>> wptr;
        std::size_t curr;   // position within the array
    public:
        StrBlobPtr(): curr(0) {}
        StrBlobPtr(StrBlob&, std::size_t);
        std::string& deref() const;
        StrBlobPtr& incr();
        inline std::string& operator*() const {
            auto p = check(curr, "dereference past end");
            return (*p)[curr];
        }
        inline std::string* operator->() const {
            return &this->operator*();
        }
        // prefix
        StrBlobPtr& operator++();
        StrBlobPtr& operator--();
        // postfix - compiler supplies 0 as argument, not to be used.
        StrBlobPtr& operator++(int);
        StrBlobPtr& operator--(int);
        // Chapter 14
        std::string& operator[](size_t n) { return (*wptr.lock())[n]; }
        std::string& operator[](size_t n) const { return (*wptr.lock())[n]; }
        StrBlobPtr operator+(const size_t);
        StrBlobPtr operator-(const size_t);
        StrBlobPtr operator-(const StrBlobPtr&);
        StrBlobPtr& operator+=(const size_t);
        StrBlobPtr& operator-=(const size_t);
        StrBlobPtr& operator-=(const StrBlobPtr&);
        std::string& operator*() const;
        std::string* operator->() const;
};

class StrBlob {
    friend class StrBlobPtr;
    // Chapter 14.
    friend bool operator==(const StrBlob&, const StrBlob&);
    friend bool operator!=(const StrBlob&, const StrBlob&);
    friend bool operator<(const StrBlob&, const StrBlob&);
    friend bool operator>(const StrBlob&, const StrBlob&);
    friend bool operator<=(const StrBlob&, const StrBlob&);
    friend bool operator>=(const StrBlob&, const StrBlob&);
    private:
        std::shared_ptr<std::vector<std::string>> data;
        void check (size_type, const std::string&) const;
    public:
        StrBlob();
        StrBlob(std::initializer_list<std::string>);
        size_type size() const { return data->size(); }
        bool empty() const { return data->empty(); }

        // add, remove
        void push_back(const std::string& t) { data->push_back(t); }
        void pop_back();

        // access
        std::string& front();
        std::string& back();

        // Pointer access
        StrBlobPtr begin();
        StrBlobPtr end();

        // Chapter 14
        std::string& operator[](size_t n) { return (*data)[n]; }
        std::string& operator[](size_t n) const { return (*data)[n]; }
};


/**
 * Text Query: 
 * user enters a word and program returns occurrences of that word in a file, 
 * as well as actual lines where the word occurs.
**/
void runQueries (std::ifstream&);

using line_no = std::vector<std::string>::size_type;

class QueryResult;
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
};
