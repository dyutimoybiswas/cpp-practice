#include "chapter10.hpp"

bool isShorter (const std::string& s1, const std::string& s2) {
    return s1.size() < s2.size();
}

bool checkSize (const std::string& s, std::string::size_type sz) {
    return s.size() > sz;
}

void elimDups (std::vector<std::string>& words) {
    std::sort(words.begin(), words.end());
    auto dupItr = unique(words.begin(), words.end());
    words.erase(dupItr, words.end());
}

bool hasFiveOrMoreLetters (const std::string& word) {
    decltype(word.size()) count = 0;
    for (const char ch: word)
        ++count;
    return count >= 5;
}

void biggies (std::vector<std::string>& words, std::vector<std::string>::size_type sz) {
    elimDups(words);
    auto itr = std::partition(words.begin(), words.end(), [sz] (const std::string& word) { return word.size() >= sz; });
    std::cout << (itr - words.cbegin()) << " word(s) have size bigger than " << sz << std::endl;
    std::for_each(words.begin(), itr, [] (const std::string& s) {std::cout << (s + ", ");});
    std::cout << std::endl;
}
