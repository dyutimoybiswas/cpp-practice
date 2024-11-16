#ifndef CHAPTER8_HPP
#define CHAPTER8_HPP

#include <iostream>
#include <string>
#include <vector>

const std::string fileName = "/home/dyutimoy/repositories/cpp-primer-solutions/part2/chapter8/lorem_ipsum.txt";
std::istream& read (std::istream&);

class PersonInfo {
    public:
        std::string name;
        std::vector<std::string> phones;
        PersonInfo(std::string n, std::vector<std::string> p):
        name(n), phones(p) {}
};

#endif
