#include "chapter17.hpp"

using std::tuple;
using std::cout;
using std::endl;
using std::cin;
using std::bitset;
using std::string;
using std::boolalpha;
using std::noboolalpha;
using std::setw;
using std::left;
using std::right;
using std::setfill;

int main () {
    #ifdef CUSTOM
    tuple<size_t, size_t, size_t> test1;    // 3 members initialized to 0
    tuple<size_t, size_t, size_t> test2 = {1, 2, 3};
    cout << std::get<1>(test2) << endl;

    // Exercise 17.8 - since constructor has default args, object with default values will be used as initial.

    // Example of bitset.
    bitset<20> bitvec1(0xbeef);     // 00001011111011101111
    bitset<32> bitvec2("1100");     // from string, MSBs are filled with 0

    string str("1111111000000011001101");
    bitset<32> bitvec3(str, 5, 4);              // 1100
    bitset<32> bitvec4(str, str.size() - 4);    // last 4

    // Example of reading and writing to bitsets.
    bitset<12> bits;
    cin >> bits;                        // reads 12 chars
    cout << "bits: " << bits << endl;

    // Example of bitset usage.
    bool status;
    bitset<30> quiz;    // 30 students passed/failed in a quiz
    quiz.set(27);       // make 27th (0-indexed) student pass
    status = quiz[27];  // pass/fail status of 27th (0-indexed) student
    quiz.reset(27);     // make 27th (0-indexed) student fail

    // Example of IO formatters.
    cout << boolalpha << true << " " << noboolalpha << false << endl;

    // Example of setw.
    int i = -16;
    double d = 3.14159;
    printValues(i, d);

    // Example of left and right justification.
    cout << left;
    printValues(i, d);
    cout << right;
    printValues(i, d);

    // Example of setfill.
    cout << setfill('#');
    printValues(i, d);
    cout << setfill(' ');   // restore default padding

    // Example of reading from istream bytewise.
    int ch;
    while ((ch = cin.get()) != EOF) {
        // custom logic here.
    }
    #endif
}
