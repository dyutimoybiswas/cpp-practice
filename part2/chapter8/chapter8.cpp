#include "chapter8.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::istream;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::istringstream;

int main(int argc, char const *argv[])
{
    // Exercise 8.1 & 8.2
    #if defined(EXERCISE1) || defined(EXERCISE2)
    read(cin);
    #endif

    // Exercise 8.3 - when EOF or invalid input is entered (eofbit/badbit/failbit).
    
    // Exercise 8.4
    #ifdef EXERCISE4
    ifstream input;
    input.open(fileName);
    if (!input) {
        cerr << "Failed to open file." << endl;
        return -1;
    }
    vector<string> v;
    string s;
    while (getline(input, s))
        v.push_back(s);
    cout << "Lines:" << endl;
    for (string line: v)
        cout << line << endl;
    input.close();
    #endif

    // Exercise 8.5
    #ifdef EXERCISE5
    ifstream input;
    vector<string> v;
    string s;
    v.clear();
    input.open(fileName);
    if (!input) {
        cerr << "Failed to open file." << endl;
        return -1;
    }
    while (input >> s) 
        v.push_back(s);
    cout << "Words:" << endl;
    for (string word: v)
        cout << word << endl;
    input.close();
    #endif

    // Exercise 8.10
    #ifdef EXERCISE10
    ifstream input;
    vector<string> v;
    string s;
    v.clear();
    input.open(fileName);
    if (!input) {
        cerr << "Failed to open file." << endl;
        return -1;
    }
    while (getline(input, s))
        v.push_back(s);
    for (const string &line: v) {
        istringstream iss(line);
        while (iss) {
            string word;
            iss >> word;
            cout << word << endl;
        }
    }
    #endif

    // Exercise 8.14 - const because not modifying members, reference to prevent copying.
    return 0;
}
