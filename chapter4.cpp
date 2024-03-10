#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(void) {

    // Exercise 4.1
    cout << (5 + 10 * 20 / 2) << endl;  // 105

    // Exercise 4.4
    cout << (12/3*4+5*15+24%4/2) << endl;  // 16+75+0=91

    // Exercise 4.10 - TODO: check solution
    // int x;
    // cout << "Enter numbers: ";
    // while (cin >> x) {
    //     if (x == 42) break;
    //     cout << x << " ";
    // }
    // cout << endl;

    // Exercise 4.11
    // int a, b, c, d;
    // cout << "Enter 4 numbers: ";
    // cin >> a >> b >> c >> d;
    // if (!(a > b && b > c && c > d)) {
    //     cout << "Criteria do not match!" << endl;
    // }

    // cout << (a = 2) << endl;    // prints 2

    // Exercise 4.13
    int i; double d;
    d = i = 3.5;    // both 3
    i = d = 3.5;    // 3 and 3.5

    // Exercise 4.19 - TODO: check solution
    int ival = -1;
    cout << (ival++ && ival) << endl;

    int a, b; 
    int &ra = a, &rb = b;
    // int &r[2];           // invalid
    int r[] = {ra, rb};     // valid

    // Exercise 4.32
    constexpr int size = 5;
    int ia[size] = {1,2,3,4,5};
    for (int *ptr = ia, ix = 0;  // ptr=&ia[0], ix is 0
        ix != size && ptr != ia + size;  // equivalent, checking till size-1
        ++ix, ++ptr) {  // increment both

        }

    const char* c = "test";
    // char *c1 = static_cast<char*>(c);   // error: const cannot be removed
    char *c1 = const_cast<char*>(c);
    // c1[0] = 'a';        // runtime error
    int *p;
    char *p1 = reinterpret_cast<char*>(p);

    // Exercise 4.32
    void *pv; const string *ps;
    // pv = const_cast<void*>(ps);  // error
}