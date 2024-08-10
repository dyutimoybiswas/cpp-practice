#ifndef CHAPTER6_HPP
#define CHAPTER6_HPP

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <initializer_list>

// Exercise 6.8
long factorial (int);
unsigned sequenceGenerator (void);

// Exercise 6.12
void swap (int&, int&);

// example
void foo (int*);
void foo (const std::string&);

bool containsCapital (const std::string&);
void convertToLower (std::string&);
int larger (int, int*);
void print (const int[10]);
int sumElements (std::initializer_list<int>);
void printVector (const std::vector<int>&, std::vector<int>::iterator);
std::string make_plural(size_t ctr, const std::string&, const std::string& = "s");

// Excercise 6.54 & 6.56
int baz (int, int);
int bam (int, int);

// Excercise 6.55
int add (int, int);
int subtract (int, int);
int multiply (int, int);
int divide (int, int);

#endif
