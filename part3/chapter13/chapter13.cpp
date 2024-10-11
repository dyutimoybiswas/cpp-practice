#include "chapter13.hpp"

using std::cout;
using std::cin;
using std::endl;

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
    // Exercise 13.39 till 13.44 - TODO:
    // Exercise 13.45 - lvalue ref(&) can be used on lvalues (modifiable) while rvalue ref(&&) can be used on rvalues (const/variable op const/std::move(variable))
    // Exercise 13.46 - &&, &, &, &&
    // Exercise 13.47, 13.48, 13.50 - TODO:
    // Exercise 13.56 - calls the enclosing function, resulting in infinite recursion
    // Exercise 13.57 - normal (expected) operation
    
    // Example.
    #ifdef CUSTOM
    String s1("abc");
    cout << s1.peek() << endl;
    String s2 = {'d', 'e', 'f'};
    cout << s2.peek() << endl;
    String s3 = s1;
    cout << s3.peek() << endl;
    String s4 = std::move(s2);
    cout << s4.peek() << endl;
    s3 = s4;
    cout << s3.peek() << endl;
    s4 = std::move(s4);         // self-assignment test
    cout << s4.peek() << endl;
    s4 = std::move(s1);
    cout << s4.peek() << endl;
    #endif

    // Example.
    #ifdef CUSTOM
    Foo obj1;
    Foo& obj2 = obj1.retFoo();          // lvalue invocation
    Foo obj3 = obj1.retVal().retBar();  // rvalue invocation
    #endif

    return 0;
}
