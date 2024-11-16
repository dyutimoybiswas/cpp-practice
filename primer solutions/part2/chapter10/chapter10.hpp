#ifndef CHAPTER10_HPP
#define CHAPTER10_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <iterator>
#include <functional>
#include <fstream>

const std::string inputFile = "/home/dyutimoy/repositories/cpp-primer-solutions/part2/chapter10/input.txt";
const std::string oddsFile = "/home/dyutimoy/repositories/cpp-primer-solutions/part2/chapter10/odds.txt";
const std::string evensFile = "/home/dyutimoy/repositories/cpp-primer-solutions/part2/chapter10/evens.txt";

bool isShorter (const std::string&, const std::string&);

bool checkSize (const std::string&, std::string::size_type);

// Exercise 10.9
void elimDups (std::vector<std::string>&);

// Exercise 10.13
bool hasFiveOrMoreLetters (const std::string&);

// Exercise 10.18
void biggies (std::vector<std::string>&, std::vector<std::string>::size_type);

#endif
