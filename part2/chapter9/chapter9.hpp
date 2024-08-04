#ifndef CHAPTER9_HPP
#define CHAPTER9_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <string>
#include <forward_list>

bool isPresent (const std::vector<int>&, std::vector<int>::const_iterator, std::vector<int>::const_iterator, int);

// Exercise 9.28
void findInsert(std::forward_list<std::string>&, const std::string, const std::string);

// Exercise 9.44
void foo (std::string&, const std::string&, const std::string&);

// Exercise 9.46
void bar (std::string&, const std::string&, const std::string&);

#endif
