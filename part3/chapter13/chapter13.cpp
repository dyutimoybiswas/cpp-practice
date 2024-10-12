#include "chapter13.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::vector;

// static member definitions.
unsigned int Employee::id = 0;
allocator_traits::allocator_type StrVec::alloc;
char_allocator_traits::allocator_type String::alloc;

int main(int argc, char const *argv[])
{
    // TODO: cover all classes through example uses, other than those covered in exercises.
    
    // Exercise 13.2 - recursively calls the constructor as object is created each time
    // Exercise 13.4 - copy constructors used in each case including function parameter.
    // Exercise 13.12 - 3: item1, item2, accum
    // Exercise 13.14 - same output for all 3 as mysn is copied around.
    // Exercise 13.15 - doesn't change output, same as above.

    #ifdef CUSTOM
    HasPtr hp1, hp2(hp1);   // copy constructor.
    HasPtr&& hp3 = std::move(hp1);
    HasPtr hp4(std::move(hp1)); // move constructor. Note that Hasptr hp4(hp3) will invoke copy cons.
    hp4 = hp1;                  // copy assignment. Note that this is invoked on already existing object. Hasptr hp4 = hp1 invokes copy cons.
    hp4 = std::move(hp2);       // move assignment. Note that this is invoked on already existing object. Hasptr hp4 = hp3 invokes copy assgn.

    // MyClass m1 = 10;     // fails when constructor is explicit.
    MyClass m2(15);
    // MyClass mc('x');     // fails
    #endif

    // Exercise 13.18
    #ifdef EXERCISE18
    Employee e1 = {"X"}, e2("Y"), e3;
    cout << Employee::getID() << endl;  // id = 3
    #endif

    // Exercise 13.19 - explicit copy constructor and assignment ensure ID is updated, synthesized versions don't update ID.
    #ifdef EXERCISE19
    Employee e1 = {"A"}, e2 = e1, e3(e2);
    cout << "e1 name: " << e1.getName() << ", e1 ID: " << Employee::getID() << endl;
    cout << "e2 name: " << e2.getName() << ", e2 ID: " << Employee::getID() << endl;
    cout << "e3 name: " << e3.getName() << ", e3 ID: " << Employee::getID() << endl;
    #endif

    // Exercise 13.24 - no destr: memory leak (ps not deleted), no copy cons - multiple objects refer to same memory pointed by ps.
    // Exercise 13.28 (copying trees) - TODO:
    // Exercise 13.35 - addToFolders, removeFromFolders not executed in synthesized versions.

    // Exercise 13.36
    #ifdef EXERCISE36
    Folder f1, f2;
    Message abc("ABC"), def("DEF"), pqr("PQR"), xyz("XYZ");
    
    f1.save(abc); f1.save(def);
    f2.save(pqr); f2.save(xyz);
    #endif

    // Exercise 13.38 - more work needed in implementing swap.
    // Exercise 13.41 - ++first_free results in garbage value for first element, and capacity is reached when (cap - 1) elements have been actually pushed.
    // TODO: Exercise 13.42
    // Exercise 13.45 - lvalue ref(&) can be used on lvalues (modifiable) while rvalue ref(&&) can be used on rvalues (const/variable op const/std::move(variable))
    // Exercise 13.46 - &&, &, &, &&
    // Exercise 13.56 - calls the enclosing function, resulting in infinite recursion
    // Exercise 13.57 - normal (expected) operation

    // Exercise 13.39
    #ifdef EXERCISE39
    StrVec s = {"this", "is", "the", "test", "string", "vector"};
    s.reserve(10);
    s.resize(2); s.resize(6, "ppap");
    s.peek();
    #endif
    
    // Example.
    #ifdef CUSTOM
    String s1("abc");
    s1.peek();
    String s2 = {'d', 'e', 'f'};
    s2.peek();
    String s3 = s1;
    s3.peek();
    String s4 = std::move(s2);
    s4.peek();
    s3 = s4;
    s3.peek();
    s4 = std::move(s4);         // self-assignment test
    s4.peek();
    s4 = std::move(s1);
    s4.peek();
    String s5("test");
    s5.reserve(8);
    cout << "size = " << s5.size() << ", capacity = " << s5.capacity() << std::endl;
    s5.peek();
    s5.resize(3);
    s5.peek();
    s5.resize(7, 'x');
    s5.peek();
    #endif

    // Exercise 13.48
    #ifdef EXERCISE48
    vector<String> v = {"jkl", "mno", "pqrs"};  // C style string constructor x4
    String tuv = "tuv", wxyz("wxyz");   // C style string constructor x2
    v.push_back(tuv);       // copy constructor
    v.push_back(wxyz);      // copy constructor
    v.push_back("0123");    // C style string constructor
    #endif

    // Exercise 13.50 - TODO: why is "move constructor" printed multiple times?
    #ifdef EXERCISE50
    vector<String> v = {"jkl", "mno", "pqrs"};  // C style string constructor x4
    String tuv = "tuv", wxyz("wxyz");   // C style string constructor x2
    v.push_back(std::move(tuv));       // move constructor
    v.push_back(wxyz);      // copy constructor
    v.push_back("0123");    // C style string constructor
    #endif

    // Example.
    #ifdef CUSTOM
    Foo obj1;
    Foo& obj2 = obj1.retFoo();          // lvalue invocation
    Foo obj3 = obj1.retVal().retBar();  // rvalue invocation
    #endif

    return 0;
}
