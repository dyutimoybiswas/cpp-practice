#include "chapter12.hpp"

StrBlob::StrBlob(): data(std::make_shared<std::vector<std::string>>()) {}
StrBlob::StrBlob(std::initializer_list<std::string> i1): data(std::make_shared<std::vector<std::string>>(i1)) {}

void StrBlob::check(size_type i, const std::string& msg) const {
    if (i >= data->size())
        throw std::out_of_range(msg);
}

std::string& StrBlob::front() {
    check(0, "front on empty StrBlob");
    return data->front();
}
std::string& StrBlob::back() {
    check(0, "back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back() {
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

StrBlobPtr::StrBlobPtr(StrBlob& a, size_t sz = 0): wptr(a.data), curr(sz) {}

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check (size_t i, const std::string& msg) const {
    auto ret = wptr.lock();
    if (!ret)
        throw std::runtime_error("unbound StrBlobPtr");
    if (i >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}

std::string& StrBlobPtr::deref() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr() {
    check(curr, "increment past end");
    ++curr;
    return *this;
}

StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); }

StrBlobPtr StrBlob::end() { return StrBlobPtr(*this, data->size()); }

void runQueries (std::ifstream& infile) {
    TextQuery tq(infile);
    while (true) {
        std::cout << "Enter word to look for, or q to quit: ";
        std::string s;
        if (!(std::cin >> s) || s == "q")  // quit if EOF or q is input
            break;
        print(std::cout, tq.query(s)) << std::endl;
    }
}

TextQuery::TextQuery(std::ifstream& is) : file(new std::vector<std::string>) {
    std::string text;
    while (getline(is, text)) {         // read each line into text
        file->push_back(text);
        int n = file->size() - 1;       // line number
        std::istringstream line(text);  // parse words
        std::string word;
        while (line >> word) {
            // store words without punctuations as map keys. Note that words are case-sensitive.
            word.erase(std::remove_if(word.begin(), word.end(), [](char ch) -> bool { return ispunct(ch); }), word.end());
            auto& lines = wm[word];     // add new entry if not present
            if (!lines)                 // not present (new entry)
                lines.reset(new std::set<line_no>);     // add a new set as value
            lines->insert(n);           // add line number to set
        }
    }
}

QueryResult TextQuery::query(const std::string& sought) const {
    // if sought not found.
    static std::shared_ptr<std::set<line_no>> nodata (new std::set<line_no>);
    auto loc = wm.find(sought);     // use find instead of [] to avoid adding sought to wm
    if (loc == wm.end())            // not found
        return QueryResult(sought, nodata, file);
    else
        return QueryResult(sought, loc->second, file);
}

std::ostream& print(std::ostream& os, const QueryResult& qr) {
    // print occurrences.
    os << qr.sought << " occurs " << qr.lines->size() << " time(s)" << std::endl;
    // print lines where occurred.
    for (auto num: *qr.lines)
        os << "\t(line " << (num+1) << ") " << *(qr.file->begin() + num) << std::endl;
    return os;
}
