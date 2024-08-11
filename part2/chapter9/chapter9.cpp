#include "chapter9.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::list;
using std::string;
using std::deque;
using std::forward_list;
using std::stoi;
using std::stof;

int main(int argc, char const *argv[])
{
    /* Exercise 9.1 a - list
        Exercise 9.1 b - deque 
        Exercise 9.1 c - vector
    */

    // Exercise 9.4
    #ifdef EXERCISE4
    vector<int> vect {1, 2, 3, 4, 5, 6};
    cout << "Element 3" << (isPresent(vect, vect.cbegin(), vect.cend() - 1, 3) ? " is present" : " isn't present") << " in the vector." << endl;
    #endif

    // Reverse traversal
    #ifdef CUSTOM
    vector<int> vect {1, 2, 3, 4, 5, 6};
    for (auto it = vect.rbegin(); it != vect.rend(); ++it)
        cout << *it << " ";
    cout << endl;
    #endif

    // Exercise 9.6 - list iterator does not support < and >
    // Exercise 9.7, 9.8 - vector<type>::size_type, list<type>::const_iterator/iterator
    // Exercise 9.10 - vector<type>::iterator, vector<type>::const_iterator

    // Exercise 9.13
    #ifdef EXERCISE13
    list<int> l = {1, 2, 3, 4};
    vector<double> v (l.begin(), l.end());
    #endif

    // Exercise 9.14
    #ifdef EXERCISE14
    list<const char*>ls = {"this", "is", "a", "test"};
    vector<string>vs;
    vs.assign(ls.cbegin(), ls.cend());
    #endif

    // Exercise 9.19
    #ifdef EXERCISE19
    list<string> ls;
    string s;
    cout << "Enter strings: ";
    while (cin >> s) {
        ls.push_back(s);
    }
    cout << "Entered strings were: ";
    for (auto itr = ls.cbegin(); itr != ls.cend(); ++itr) {
        cout << *itr << " ";
    }
    cout << endl;
    #endif

    // Exercise 9.20
    #ifdef EXERCISE20
    list<int>l1 = {1, 2, 3, 4, 5, 6, 7};
    deque<int> odd, even;
    for (auto itr = l1.cbegin(); itr != l1.cend(); ++itr) {
        if (*itr % 2)
            odd.push_back(*itr);
        else
            even.push_back(*itr);
    }
    cout << "Odds: ";
    for (const auto& e: odd)
        cout << e << " ";
    cout << endl << "Even: ";
    for (const auto& e: even)
        cout << e << " ";
    cout << endl;
    #endif

    // Exercise 9.22 - infinite loop. as long as value is present it keeps inserting
    
    // Exercise 9.24
    #ifdef EXERCISE24
    vector<int>v1 = {1, 2, 3};
    // FIXME: use assert to check that below items are equal instead of printing.
    // cout << "First element: " << v1.at(0) << " " << v1[0] << " " << v1.front() << " " << *v1.begin() << endl;
    v1.clear();
    // cout << "First element: " << v1.at(0) << " " << v1[0] << " " << v1.front() << " " << *v1.begin() << endl; // error
    #endif
    
    
    // Example - remove odd elements in-place.
    #ifdef CUSTOM
    list<int> lst = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto it = lst.begin();
    while (it != lst.end()) {
        if (*it % 2)    //remove odd
            it = lst.erase(it);
        else
            ++it;
    }
    #endif

    // Exercise 9.26
    #ifdef EXERCISE26
    int ia[] = {0,1,1,2,3,5,8,13,21,55,89};
    vector<int> ia_vect;
    ia_vect.assign(ia, ia+11);
    list<int> ia_lst;
    ia_lst.assign(ia, ia+11);
    for (const int& e: ia_vect)
        cout << e << " ";
    cout<<endl;
    for (const int& e: ia_lst)
        cout << e << " ";
    cout<<endl;
    #endif

    // Exercise 9.27
    #ifdef EXERCISE27
    forward_list<int> fl1 = {0,1,2,3,4,5,6,7,8,9};
    auto prev = fl1.before_begin();
    auto curr = fl1.begin();
    while (curr != fl1.end()) {
        if (*curr % 2)
            curr = fl1.erase_after(prev);   // remove *curr, return curr+1
        else {
            prev = curr;    // *prev is even
            ++curr;
        }
    }
    #endif

    // Example - remove even and duplicate odds.
    #ifdef CUSTOM
    vector<int>v2 = {0,1,2,3,4,5,6,7,8,9};
    auto itr = v2.begin();
    while (itr != v2.end()) {
        if (*itr % 2) {
            itr = v2.insert(itr, *itr); // duplicate element before itr, returns itr-1 (duplicated element index)
            itr += 2;   // advance beyond this element
        } else {
            v2.erase(itr);  // erase *itr, returns itr+1
        }
    }
    #endif

    // Exercise 9.28
    #ifdef EXERCISE28
    forward_list<string>fwl = {"this", "is", "test"};
    findInsert(fwl, "is", "a");
    findInsert(fwl, "the", "string");
    for (const auto& e: fwl)
        cout << e << " ";
    cout << endl;
    #endif

    // Exercise 9.29 - vec.resize(100) adds 75 0s at the end, vec.resize(10) erases 90 values from the end
    // Exercise 9.30 - if new elements are to be added, value to be specified

    // Exercise 9.31
    #ifdef EXERCISE31
    list<int>l2 = {0,1,2,3,4,5,6,7,8,9};
    auto iter = l2.begin();
    while (iter != l2.end()) {
        if (*iter % 2) {
            iter = l2.insert(iter, *iter); // duplicate element before itr, returns itr-1 (duplicated element index)
            // iter += 2; // not supported
            ++iter; ++iter;// advance beyond this element
        } else {
            iter = l2.erase(iter);  // erase *iter, returns iter+1
        }
    }
    #endif
    // Exercise 9.32 - no, because iter++ != iter += 2
    // Exercise 9.37 - array size is defined at declaration. list is non-contiguous and allocates memory dynamically.

    // Exercise 9.42
    #ifdef EXERCISE42
    string s1;
    s1.reserve(100);
    #endif

    // Exercise 9.44
    #ifdef EXERCISE44
    string str = "thru and thru";
    // foo(str, "tho", "though");
    foo(str, "thru", "through");
    cout << "Replaced string: " << str << endl;
    #endif

    // Exercise 9.46
    #ifdef EXERCISE46
    string s2 = "Dyutimoy";
    bar(s2, "Mr. ", " Biswas");
    cout << s2 << endl;
    #endif

    // Example - find occurrences of digits in a string
    #ifdef CUSTOM
    string name = "dyu123timo45y", numbers = "123";
    decltype(name.size()) idx = 0;
    while ((idx = name.find_first_of(numbers, idx)) != string::npos) {
        cout << "Found number at index: " << idx << ". Digit is " << name[idx] << endl;
        ++idx;
    }
    #endif

    // Exercise 9.48 - string::npos

    // Exercise 9.50
    #ifdef EXERCISE50
    vector<string> vsi = {"12", "34", "56", "78", "90", "-9", "-123"};
    vector<string> vsf = {"1.2", ".34", "56.0", "7.8", "9.0", "-9", "-1.23"};
    int isum = 0;
    for (const string& s: vsi) 
        isum += stoi(s);
    cout << "Sum of numbers = " << isum << endl;
    int fsum = 0;
    for (const string& s: vsf) 
        fsum += stof(s);
    cout << "Sum of numbers = " << fsum << endl;
    #endif

    return 0;
}
