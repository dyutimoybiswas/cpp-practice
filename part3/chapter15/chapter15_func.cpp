#include "chapter15.hpp"

Bulk_quote::Bulk_quote(const std::string& book, double p, std::size_t qty, double disc):
Disc_quote(book, p, qty, disc) {}

double Bulk_quote::net_price(std::size_t cnt) const {
    if (cnt >= min_qty)
        return cnt * (1 - discount) * price;
    else
        return cnt * price;
}

void Quote::debug() {
    std::cout << "book no: " << bookNo << ", price = " << price << std::endl;
}

void Bulk_quote::debug() {
    std::cout << "min qty: " << min_qty << ", discount = " << discount << std::endl;
}

double print_total(std::ostream& os, const Quote& item, std::size_t n) {
    double ret = item.net_price(n);
    // dynamic binding, Quote/Bulk_quote function will be invoked based on object.
    os << "ISBN: " << item.isbn()
       << "# sold: " << n << " total due: " << ret << std::endl;
    return ret;
}

double Basket::total_receipt(std::ostream& os) const {
    double sum = 0.0;
    // group of items with same isbn, upper_bound returns iterator to one past the last item.
    for (auto itr = items.cbegin(); itr != items.cend(); itr = items.upper_bound(*itr)) {
        // *itr = shared_ptr, **itr = object
        sum += print_total(os, **itr, items.count(*itr));
    }
    os << "Total Sale: " << sum << std::endl;
    return sum;
}

std::ostream& operator<<(std::ostream& os, const Query& query) {
    return os << query.rep();
}

inline Query::Query(const std::string& s): q(new WordQuery(s)) {}

QueryResult OrQuery::eval(const TextQuery& text) const {
    // virtual calls.
    auto right = rhs.eval(text), left = lhs.eval(text);
    
    // contains line numbers from beginning to end.
    auto ret_lines = std::make_shared<std::set<line_no>>(left.begin(), left.end());
    
    // insert line numbers from right hand operand.
    ret_lines->insert(right.begin(), right.end());

    return QueryResult(rep(), ret_lines, left.get_file());
}

QueryResult AndQuery::eval(const TextQuery& text) const {
    // virtual calls.
    auto right = rhs.eval(text), left = lhs.eval(text);
    
    // set to hold intersection of left and right.
    auto ret_lines = std::make_shared<std::set<line_no>>();
    
    // takes intersection of left and right and adds to destination (final argument).
    // final argument adds the elements to ret_lines.
    std::set_intersection(left.begin(), left.end(), right.begin(), right.end(), std::inserter(*ret_lines, ret_lines->begin()));

    return QueryResult(rep(), ret_lines, left.get_file());
}


QueryResult NotQuery::eval(const TextQuery& text) const {
    // virtual call.
    auto result = query.eval(text);
    auto ret_lines = std::make_shared<std::set<line_no>>();
    
    // to iterate through lines where operand (word) appears.
    auto begin = result.begin(), end = result.end();

    // for each line in file, if line not in result, add that line number to ret_lines.
    auto sz = result.get_file()->size();
    for (size_t n = 0; n != sz; ++n) {
        if (begin == end || *begin != n)
            ret_lines->insert(n);   // add line number if not in result.
        else if (begin != end)
            ++begin;                // get next line number in result
    }

    return QueryResult(rep(), ret_lines, result.get_file());
}