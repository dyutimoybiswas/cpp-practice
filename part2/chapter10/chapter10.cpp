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
using std::ostream_iterator;
using std::istream_iterator;

int main(int argc, char const *argv[])
{
    // Exercise 10.1
    #ifdef EXERCISE1
    // FIXME: check logic. not asking for value to count.
    vector<int> v1;
    cout << "Enter elements: ";
    int val;
    while (cin >> val) {
        v1.push_back(val);
        if (!val)
            break;
    }
    cout << endl << "Enter value to count: ";
    cin >>val;
    auto c = count(v1.cbegin(), v1.cend(), val);
    cout << endl << "Value " << val << " occurs " << c << " times." << endl;
    #endif

    // Exercise 10.4 - no issue/ initial should be 0.0
    // Exercise 10.5 - error since const char* has no == operation defined

    // Note: below call results in error, since v is empty.
    // constexpr int randomSize = 4;
    // constexpr int randomData = 6;
    // vector<int> v;
    // fill_n(v.begin(), randomSize, randomData);

    // Exercise 10.6
    #ifdef EXERCISE6
    int arr[5];
    fill_n(begin(arr), 5, 0);
    #endif

    // Exercise 10.7a - const iterator not allowed for copy
    // Exercise 10.7b - no error

    // Exercise 10.9
    #ifdef EXERCISE9
    vector<string> w = {"a", "bc", "d", "bc", "a"};
    elimDups(w);
    cout << "After removing duplicates: " << endl;
    for (const auto &e: w)
        cout << e << " ";
    cout << endl;
    #endif

    // Exercise 10.10 - only iterators are passed to functions as arguments

    // Exercise 10.13
    #ifdef EXERCISE13
    vector<string> w1 = {"test", "words", "sun", "is", "shining", "not"};
    partition(w1.begin(), w1.end(), hasFiveOrMoreLetters);
    for (const auto& s: w1)
        cout << s << " ";
    cout << endl;
    #endif

    // Note - lambda usage
    #ifdef CUSTOM
    vector<string> w1 = {"test", "words", "sun", "is", "shining", "not"};
    short sz = 5;
    auto itr = find_if(w1.cbegin(), w1.cend(), [sz](const string&a) {return a.size() >= sz;});
    auto test = [](int x, int y) -> int {
        cout << "Dummy statement" << endl;
        return x * y;
    };
    cout << test(4, 5) << endl;     // returns void if return type not specified.

    // Example - for_each usage (prints elements of the container).
    for_each(w1.cbegin(), w1.cend(), [](const string& s) {
        cout << s << " ";
    });
    cout << endl;

    // Example - ostream_iterator usage (prints elements separated by a delimiter).
    ostream_iterator<string> os(cout, ", ");
    for(string word: w1)
        *os++ = word;   // writes element(word) to cout.
    cout << endl;
    #endif

    // Exercise 10.14
    #ifdef EXERCISE14
    auto s = [] (int x, int y) { return x + y; };
    #endif

    // Exercise 10.15
    #ifdef EXERCISE15
    int a = 4;
    auto l = [a] (int b) { return a + b; };
    cout << l(5) << endl;
    #endif
    
    // Exercise 10.18
    #ifdef EXERCISE18
    vector<string> w1 = {"test", "words", "sun", "is", "shining", "not"};
    biggies(w1, 5);
    return 0;
    #endif

    // Exercise 10.20
    #ifdef EXERCISE20
    vector<string> vs1 = {"abcdef", "toilets", "test", "sentence", "boo"};
    auto c = count_if(vs1.cbegin(), vs1.cend(), [](string w){return w.size() > 6;});
    cout << c << " words are bigger than 6 characters." << endl;
    #endif

    // Exercise 10.21
    #ifdef EXERCISE21
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
    #endif

    // example to show bind reorder parameters
    #ifdef CUSTOM
    vector<string> vs1 = {"abcdef", "toilets", "test", "sentence", "boo"};
    sort(vs1.begin(), vs1.end(), isShorter);    // ascending, called as isShorter(s1, s2)
    sort(vs1.begin(), vs1.end(), bind(isShorter, _2, _1));    // descending, called as isShorter(s2, s1)
    #endif

    // Exercise 10.23 - callable and variable number of args

    // Exercise 10.24
    #ifdef EXERCISE24
    vector<int> v1 = {0, 1, 2, 3, 4, 5, 6};
    auto it = find_if(v1.cbegin(), v1.cend(), bind(checkSize, "", _1));
    if (it != v1.cend()) {
        cout << "Element = " << *it << endl;
    } else {
        cout << "No such element exists." << endl;
    }
    #endif

    // example to read inputs from cin and store in a vector
    #ifdef CUSTOM
    vector<int> vi;
    istream_iterator<int> in_itr(cin);     // read from cin
    istream_iterator<int> eof;             // holds EOF
    while (in_itr != eof) {
        vi.push_back(*in_itr);
        ++in_itr;
    }

    // example to write values to output
    ostream_iterator<int> out_itr(cout, " ");   // print space after each element
    for (const auto& e: vi) {
        *out_itr = e;
        ++out_itr;
    }
    cout << endl;
    #endif

    // Exercise 10.30, 10.33 - TODO:

    // Exercise 10.37
    #ifdef EXERCISE37
    vector<int>vi = {1,2,3,4,5,6,7,8,9,10};
    vector<int>vi1(5);      // NOTE: must specify destination vector size for copying
    copy(vi.rbegin() + 3, vi.rbegin() + 8, vi1.begin());
    for (const auto& e: vi1)
        cout << e << " ";
    cout << endl;
    #endif
}
