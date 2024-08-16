#include "chapter8.hpp"
#include <fstream>
#include <sstream>

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
using std::ostringstream;

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

    // Example of ostringstream.
    #ifdef CUSTOM
    vector<PersonInfo> people = {{"riju", {"9843895550", "8240539463"}}, {"skd", {"01234", "8961051602"}}, {"sdk", {""}}};
    for(const auto& entry: people) {
        ostringstream formatted, badNums;   // invalid phones < 10 digits are stored in badNums, valid in formatted.
        for(const auto& p: entry.phones) {
            if(p.size() < 10)
                badNums << p << ", ";
            else
                formatted << "+91-" << p << ", ";
        }
        if(!formatted.str().empty())
            cout << entry.name << " has phones: " << formatted.str() << endl;
        if(!badNums.str().empty())
            cout << entry.name << " has invalid phones: " << badNums.str() << endl;
    }
    #endif
    // Exercise 8.14 - const because not modifying members, reference to prevent copying.
    return 0;
}
