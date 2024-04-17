#ifndef CHAPTER10_HPP
#define CHAPTER10_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <functional>

bool isShorter (const std::string&, const std::string&);

bool checkSize (const std::string&, std::string::size_type);

// Exercise 10.9
void elimDups (std::vector<std::string>&);

// Exercise 10.13
bool hasFiveOrMoreLetters (const std::string&);

// Exercise 10.18
void biggies (std::vector<std::string>&, std::vector<std::string>::size_type);

#endif
