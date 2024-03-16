#include "chapter6.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::initializer_list;
using std::runtime_error;

long factorial (int num) {
    long fact = 1;
    while (num) {
        fact *= num;
        num--;
    }
    return fact;
}

unsigned sequenceGenerator (void) {
    static unsigned n = 0;
    return n++;
}

void swap (int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void foo (int* p) {
    *p = 3; // this change will happen in the variable
    // p = 0;  // local change
}

void foo (const string &s) {}

bool containsCapital (const string &s) {
    for (char ch: s) {
        if (isupper(ch)) return true;
    }
    return false;
}

void convertToLower (string &s) {
    for(char &ch: s) ch = tolower(ch);
}

int larger (int a, int* pb) {
    return a > *pb ? a : *pb;
}

// Excercise 6.24
void print (const int ia[10]) {
    for (size_t i = 0; i != 10; ++i)
        cout << ia[i] << endl;
}

int sumElements (initializer_list<int> nums) {
    int sum = 0;
    for (int n: nums) sum += n;
    return sum;
}

void printVector (const vector<int> &v, vector<int>::iterator it) {
    if (it == v.end()) {
        cout << endl;
        return;
    }
    cout << *it << " ";
    printVector(v, it+1);   // it++ will increment it in the previous stack location
}

// Excercise 6.36 - TODO: verify
int (&bar(string s))[10] {}

// Excercise 6.42
string make_plural(size_t ctr, const string &word, const string &ending) {
    return ctr > 1 ? word + ending : word;
}

// Excercise 6.46
// constexpr bool isShorter(const string &s1, const string &s2) {
//     return s1.size() < s2.size();   // error: size is non-constexpr
// }

// Excercise 6.54 & 6.56
int baz (int a, int b) {
    cout << "Called baz. a = " << a << " and b = " << b << endl;
    return 0;
}
int bam (int a, int b) {
    cout << "Called bam. a = " << a << " and b = " << b << endl;
    return 0;
}

// Excercise 6.55
int add (int x, int y) {
    return x + y;
}

int subtract (int x, int y) {
    return x - y;
}

int multiply (int x, int y) {
    return x * y;
}

int divide (int x, int y) {
    if (!y) {
        throw runtime_error("Divide by 0 is invalid! ");
    }
    return x / y;
}
