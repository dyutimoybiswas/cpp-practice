#include "chapter15.hpp"

using std::cout;
using std::endl;
using std::vector;
using std::make_shared;
using std::shared_ptr;

int main(void) {
    Quote basic;
    Bulk_quote bulk;

    Quote *pitem = &bulk;   // valid
    Quote &ritem = bulk;    // valid

    // Exercise 15.11
    #ifdef EXERCISE11
    Quote *pobj = &basic;
    pobj->debug();  // prints Quote items
    pitem->debug(); // prints Bulk_quote items
    #endif

    // Exercise 15.13 - print call inside derived print is recursive.
    // Exercise 15.14 - all object calls are compile time, all pointer and reference calls are runtime.

    #ifdef CUSTOM
    print_total(cout, basic, 20);
    print_total(cout, bulk, 20);
    #endif

    // Disc_quote obj;     // error
    // Exercise 15.18 - only valid for classes inheriting publicly.
    // Exercise 15.19 - valid for all except Derived_from_Private

    #ifdef CUSTOM
    // pitem->discount_policy();   // error, member not present in class
    Bulk_quote *pbulk = &bulk;
    pbulk->discount_policy();       // Disc_quote has this member
    #endif

    // Exercise 15.28
    #ifdef EXERCISE28
    vector<Quote> items;
    items.push_back(Quote("0-201-82470-1", 50));
    items.push_back(Bulk_quote("0-201-54848-8", 50, 10, 0.25));
    cout << items.back().net_price(15) << endl;     // calls net_price of BQuote, discount not applied
    #endif

    // Exercise 15.29
    #ifdef EXERCISE29
    vector<shared_ptr<Quote>> basket;
    basket.push_back(make_shared<Quote>("0-201-82470-1", 50));
    basket.push_back(make_shared<Bulk_quote>("0-201-54848-8", 50, 10, 0.25));
    cout << basket.back()->net_price(15) << endl;   // calls net_price of Bulk_quote, discount applied
    #endif

    // TODO: Exercise 15.32, 15.39, 15.42
    
    // Exercise 15.38 - all operations return query objects and cannot be used to access class-specific members. all 3 are invalid.
    // Exercise 15.40 - all valid cases, returns left/right/empty based on non-empty lhs and/or rhs.
}
