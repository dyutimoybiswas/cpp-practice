#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

/**
 * N denotes number of elements in the container
 * Map - O(logN) time and O(1) space for search, insert and delete
 * Set - O(logN) time and O(1) space for search, insert and delete
 * Stack - O(1) time and space for push and pop
 * Queue - O(1) time and space for push and pop
 * Vector - O() time and space for push_back and pop_back, O(N) time and O(1) space for erase and clear
 * String - O() time and space for push_back and pop_back, O(N) time and O(1) space for erase and clear
 */

int main(void) {
    // Exercise 3.2
    #ifdef EXERCISE2
    string line;
    while (getline(cin, line)) {
        cout << line << endl;
    }
    string word;
    while (cin >> word) {
        cout << word << " ";
    }
    cout << endl;
    #endif

    // Exercise 3.4
    #ifdef EXERCISE4
    string s1, s2;
    cin >> s1 >> s2;
    if (s1 == s2) {
        cout << "Equal" << endl;
    } else {
        cout << (s1 > s2 ? s1 : s2) << " is larger." << endl;
    }
    if (s1.size() == s2.size()) {
        cout << "Equal" << endl;
    } else {
        cout << (s1.size() > s2.size() ? s1 : s2) << " is longer." << endl;
    }
    #endif

    // Exercise 3.6 & Exercise 3.7
    #if defined(EXERCISE6) || defined(EXERCISE7)
    string s;
    cout << "Enter a string: ";
    cin >> s;
    for (char &c : s) {   // ref used to modify in-place
        c = 'X';
    }
    cout << "The modified string is: " << s << endl;
    #endif

    // Exercise 3.9
    #ifdef EXERCISE9
    string str;
    cout << str[0] << endl;  // no error. >1 outputs garbage
    #endif

    // Exercise 3.10
    #ifdef EXERCISE10
    string line;
    cout << "Enter a sentence: ";
    // cin.ignore();  // to skip the newline at the end of the previous input
    getline(cin, line);
    for (char ch : line) {
        if (ispunct(ch)) continue;
        cout << ch;
    }
    cout << endl;
    #endif

    // Exercise 3.11
    #ifdef EXERCISE11
    const string t = "Keep out!";
    for (auto &c : t) {}  // no error
    #endif

    // Exercise 3.12
    #ifdef EXERCISE12
    vector<vector<int>> ivec;
    // vector<string> svec = ivec;     // error
    #endif

    // Exercise 3.13
    #ifdef EXERCISE13
    vector<string> v1 {10, "hi"};  // 10 counts of "hi"
    vector<int> v2 {10, 42};  // 2 elements - 10 and 42
    vector<string>v3 {10};      // same as vector<string> v3(10)
    vector<int> vtest(5);  // 5 counts of 0
    #endif

    // Exercise 3.14
    #ifdef EXERCISE14
    vector<int> v4; int a;
    cout << "Enter numbers: ";
    while (cin >> a) {
        v4.push_back(a);
    }
    for (int v: v4) cout << v << " ";
    cout << endl;
    #endif

    // Exercise 3.17
    #ifdef EXERCISE17
    vector<string> wv;
    string w;
    unsigned int count = 0;
    cout << "Enter words: ";
    while (cin >> w) {
        wv.push_back(w);
    }
    for (string w: wv) {
        for (char &c: w) c = toupper(c);
        count++;
        if (count > 8) {
            count = 1;
            cout << endl;
        }
        cout << w << " ";
    }
    cout << endl;
    #endif

    // Exercise 3.18
    // vector<int> ivec; ivec[0] = 42;  // error: index out of bounds

    // Exercise 3.19
    #ifdef EXERCISE19
    vector<string> v5(10, "test");
    cout << v5.size() << endl;  // 10
    #endif

    // Exercise 3.20
    #ifdef EXERCISE20
    vector<int> v6; int i;
    cout << "Enter integers: " ;
    while (cin >> i) {
        v6.push_back(i);
    }
    decltype(v6.size()) l = 0, r = 1;
    cout << endl << "Adjacent sums: ";
    while (r < v6.size()) {
        cout << v6[l] + v6[r] << " ";
        l++; r++;
    }
    cout << endl << "Extremes sums: ";
    l = 0, r = v6.size() - 1;
    while (l != r) {
        cout << v6[l] + v6[r] << " ";
        l++; r--;
    }
    cout << endl;
    #endif

    // Exercise 3.23
    #ifdef EXERCISE23
    vector<int> v7(10);
    for (int i = 0; i < 10; i++) {
        v7[i] = i;
    }
    for (auto it = v7.begin(); it != v7.end(); it++) {
        *it *= 2;
    }
    for (int e : v7) {
        cout << e << " ";
    }
    cout << endl;
    #endif

    // Binary search
    #ifdef CUSTOM
    vector<int> v7(10);
    auto b = v7.begin(), e = v7.end();
    auto mid = b + (e - b)/2;
    cout << "Enter the element to find: ";
    int element; cin >> element;
    bool isFound = false;
    while (b != e) {
        if (element == *mid) {
            isFound = true;
            break;
        } else if (element > *mid) {
            b = mid + 1;
        } else {
            e = mid;
        }
        mid = b + (e - b)/2;
    }
    cout << (isFound ? "Element was found" : "Element wasn't found") << endl;
    #endif

    // Exercise 3.25 - grade clustering
    #ifdef EXERCISE25
    vector<unsigned> scores (11);   // 0-9,10-19...90-99,100.
    unsigned grade;
    cout << "Enter the grades: ";
    while (cin >> grade) {
        if (grade >= 0 && grade <= 100) {
            auto it = scores.begin() + grade / 10; // ex- 42/10 = 4(int), scores[4] denotes 40-49
            (*it)++;    // operator precedence
        }
    }
    cout << endl << "Cluster scores are: ";
    for (int s: scores) {
        cout << s << " ";
    }
    cout << endl;
    #endif

    #ifdef CUSTOM
    int a[] = {0, 1, 2};
    int *a1 = a;    // allowed
    // int a2[] = a;   // error
    #endif
}
