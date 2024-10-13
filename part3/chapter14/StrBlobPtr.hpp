#include <memory>
#include <string>
#include <vector>
#include <stdexcept>

class StrBlob;
typedef std::vector<std::string>::size_type size_type;

class StrBlobPtr {
    friend bool operator==(const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator!=(const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator<(const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator>(const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator<=(const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator>=(const StrBlobPtr&, const StrBlobPtr&);
    private:
        std::shared_ptr<std::vector<std::string>> check (size_t, const std::string&) const;
        std::weak_ptr<std::vector<std::string>> wptr;
        size_t curr;   // position within the array
    public:
        StrBlobPtr(): curr(0) {}
        StrBlobPtr(StrBlob&, size_t = 0);
        std::string& deref() const;
        StrBlobPtr& incr();
        std::string& operator*() const {
            auto p = check(curr, "dereference past end");
            return (*p)[curr];
        }
        std::string* operator->() const { return &this->operator*(); }
        // prefix
        StrBlobPtr& operator++();
        StrBlobPtr& operator--();
        // postfix - compiler supplies 0 as argument, not to be used.
        StrBlobPtr& operator++(int);
        StrBlobPtr& operator--(int);
        std::string& operator[](size_t n) { return (*wptr.lock())[n]; }
        std::string& operator[](size_t n) const { return (*wptr.lock())[n]; }
        StrBlobPtr operator+(const size_t);
        StrBlobPtr operator-(const size_t);
        StrBlobPtr operator-(const StrBlobPtr&);
        StrBlobPtr& operator+=(const size_t);
        StrBlobPtr& operator-=(const size_t);
        StrBlobPtr& operator-=(const StrBlobPtr&);
        std::string& operator*();
        std::string* operator->();
};

class StrBlob {
    friend class StrBlobPtr;
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
        StrBlobPtr begin() { return StrBlobPtr(*this); }
        StrBlobPtr end() { return StrBlobPtr(*this, data->size()); }

        std::string& operator[](size_t n) { return (*data)[n]; }
        std::string& operator[](size_t n) const { return (*data)[n]; }
};
