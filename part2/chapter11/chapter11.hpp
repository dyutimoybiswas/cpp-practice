#ifndef CHAPTER11_HPP
#define CHAPTER11_HPP

#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <set>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
// #include <cassert>

void wordTransform(std::ifstream&, std::ifstream&);
std::map<std::string, std::string> buildMap (std::ifstream&);
const std::string& transform(const std::string&, const std::map<std::string, std::string>&);

const std::string pwd = "/home/dyutimoy/repositories/cpp-primer-solutions/part2/chapter11/";

#endif
