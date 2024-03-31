#include "chapter9.hpp"

bool isPresent (const std::vector<int>& v, std::vector<int>::const_iterator it1, std::vector<int>::const_iterator it2, int value) {
    while (it1 < it2) {
        // std::cout<<*it1<<" "<<*it2<<std::endl;
        if (*it1 == value || *it2 == value) {
            return true;
        }
        ++it1; --it2;
    }
    return false;
}

void findInsert(std::forward_list<std::string>& fl, const std::string fstr, const std::string istr) {
    auto prev = fl.before_begin(), curr = fl.begin();
    bool found = false;
    while (curr != fl.end()) {
        if (*curr == fstr) {
            found = true;
            fl.insert_after(curr, istr);
        }
        ++prev;
        ++curr;
    }
    if (!found) {
        fl.insert_after(prev, istr);
    }
}

void foo (std::string& s, const std::string& oldVal, const std::string& newVal) {
    for (decltype(s.size()) i = 0; i < s.size(); ++i) {
        if (s.substr(i, oldVal.size()) == oldVal) {
            s.replace(i, oldVal.size(), newVal);
        }
    }
}

void bar (std::string& name, const std::string& prefix, const std::string& suffix) {
    name.insert(0, prefix);
    name.insert(name.size(), suffix);
}
