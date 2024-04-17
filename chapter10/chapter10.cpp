#include "chapter10.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::count;
using std::fill_n;
using std::begin;
using std::string;
using std::unique;
using std::sort;
using std::stable_sort;
using std::partition;
using std::find_if;
using std::for_each;
using std::bind;
using std::placeholders::_1;
using std::placeholders::_2;

int main(int argc, char const *argv[])
{
    // Exercise 10.1
    // vector<int> v1;
    // cout << "Enter elements: ";
    // int val;
    // while (cin >> val) {
    //     v1.push_back(val);
    //     if (!val)
    //         break;
    // }
    // cout << endl << "Enter value to count: ";
    // cin >>val;
    // auto c = count(v1.cbegin(), v1.cend(), val);
    // cout << endl << "Value " << val << " occurs " << c << " times." << endl;

    // Exercise 10.4 - no issue/ initial should be 0.0
    // Exercise 10.5 - error since const char* has no == operation defined

    // Exercise 10.6
    int arr[5];
    fill_n(begin(arr), 5, 0);

    // Exercise 10.7a - const iterator not allowed for copy
    // Exercise 10.7b - no error

    // Exercise 10.9
    vector<string> w = {"a", "bc", "d", "bc", "a"};
    elimDups(w);
    cout << "After removing duplicates: " << endl;
    for (const auto &e: w)
        cout << e << " ";
    cout << endl;

    // Exercise 10.10 - only iterators are passed to functions as arguments

    // Exercise 10.13
    vector<string> w1 = {"test", "words", "sun", "is", "shining", "not"};
    partition(w1.begin(), w1.end(), hasFiveOrMoreLetters);
    for (const auto& s: w1)
        cout << s << " ";
    cout << endl;

    // Note - lambda usage
    short sz = 5;
    auto itr = find_if(w1.cbegin(), w1.cend(), [sz](const string&a) {return a.size() >= sz;});

    // Exercise 10.14
    auto s = [] (int x, int y) { return x + y; };

    // Exercise 10.15
    int a = 4;
    auto l = [a] (int b) { return a + b; };
    cout << l(5) << endl;
    
    // Exercise 10.18
    biggies(w1, 5);
    return 0;

    // Exercise 10.20
    vector<string> vs1 = {"abcdef", "toilets", "test", "sentence", "boo"};
    auto c = count_if(vs1.cbegin(), vs1.cend(), [](string w){return w.size() > 6;});
    cout << c << " words are bigger than 6 characters." << endl;

    // Exercise 10.21
    int x = 4;
    // auto didBecomeZero = [&x] () -> bool {
    auto didBecomeZero = [x] () mutable -> bool {
        if (!x)
            return false;
        --x;
        return true;
    };
    while (didBecomeZero()) 
        cout << "x value = " << x << endl;
    cout << "x became 0. Decrement not possible." << endl;

    // example to show bind reorder parameters
    sort(vs1.begin(), vs1.end(), isShorter);    // ascending, called as isShorter(s1, s2)
    sort(vs1.begin(), vs1.end(), bind(isShorter, _2, _1));    // descending, called as isShorter(s2, s1)

    // Exercise 10.23 - callable and variable number of args
    // Exercise 10.24
    vector<int> v1 = {0, 1, 2, 3, 4, 5, 6};
    auto it = find_if(v1.cbegin(), v1.cend(), bind(checkSize, "", _1));
    if (it != v1.cend()) {
        cout << "Element = " << *it << endl;
    } else {
        cout << "No such element exists." << endl;
    }

    // example to read inputs from cin and store in a vector
    // vector<int> vi;
    // istream_iterator<int> in_itr(cin);     // read from cin
    // istream_iterator<int> eof;             // holds EOF
    // while (in_itr != eof) {
    //     vi.push_back(*in_itr);
    //     ++in_itr;
    // }

    // example to write values to output
    // ostream_iterator<int> out_itr(cout, " ");   // print space after each element
    // for (const auto& e: vi) {
    //     *out_itr = e;
    //     ++out_itr;
    // }
    // cout << endl;

    // Exercise 10.30, 10.33 - TODO:

    // Exercise 10.37
    vector<int>vi = {1,2,3,4,5,6,7,8,9,10};
    vector<int>vi1(5);      // NOTE: must specify destination vector size for copying
    copy(vi.rbegin() + 3, vi.rbegin() + 8, vi1.begin());
    for (const auto& e: vi1)
        cout << e << " ";
    cout << endl;
}
