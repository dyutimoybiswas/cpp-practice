#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::runtime_error;
using std::cerr;

int main(void) {

    #ifdef CUSTOM
    // Valid
    int a = 1, b = 2;
    if (a == 1)
        while (b++ < 3)
            cout << "Here" << endl;

    // Example
    switch (false) {
        case true:
            // int i = 0;   // error
            int j;          // valid
            break;
        case false:
            j = 2;
            cout << j << endl;
            break;
    }

    int n = 6;
    switch (n % 2) {
        case 0, 2, 4, 6, 8:         // error
            cout << "Even" << endl;
            break;
    }
    #endif

    // Excercise 5.14 - FIXME: recheck logic
    #ifdef EXERCISE14
    string word, lastWord, maxWord;
    unsigned count = 0, maxCount = 0;
    cout << "Enter words: ";
    while (cin >> word) {   
        if (lastWord != word) {
            if (maxCount < count) {
                maxCount = count;
                maxWord = lastWord;
            }
            lastWord = word;
            count = 1;
        } else {
            count++;
        }
    }
    cout << maxWord << " occurs " << maxCount << " times." << endl;
    #endif

    // Excercise 5.17
    #ifdef EXERCISE17
    vector<int> v1 = {0, 1, 1, 2};
    vector<int> v2 = {0, 1, 1, 2, 3, 5, 8};
    bool prefixFlag = true;
    for (decltype(v1.size()) i = 0; i < v1.size() && i < v2.size(); ++i) {
        if (v1[i] != v2[i]) {
            prefixFlag = false;
            break;
        }
    }
    cout << "Vector1 " << (prefixFlag? "is a " : "is not a ") << "prefix of Vector2" << endl;
    #endif

    // Excercise 5.19
    #ifdef EXERCISE19
    bool continueFlag = true;
    do {
        string s1, s2;
        cout << "Enter 2 strings: ";
        cin >> s1 >> s2;
        if (s1 == s2)
            cout << "Strings are equal." << endl;
        else if (s1 < s2)
            cout << "1st string is lesser than 2nd." << endl;
        else
            cout << "2nd string is lesser than 1st." << endl;
            char response;
        cout << "Do you want to continue? ";
        cin >> response;
        continueFlag = tolower(response) == 'y';
    } while (continueFlag);
    #endif

    // Excercise 5.25
    #ifdef EXERCISE25
    try {
        int a, b;
        cout << "Enter 2 numbers: ";
        cin >> a >> b;
        if (b == 0)  // need to throw explicitly.
            throw runtime_error("Cannot divide by zero!");
        cout << "The result of integer division is " << a / b << endl;
    } catch (runtime_error re) {
        cerr << "Exception was raised: " << re.what() << endl;
    }
    #endif
}