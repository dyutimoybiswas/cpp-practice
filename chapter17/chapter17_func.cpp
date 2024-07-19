#include "chapter17.hpp"

inline bool operator==(const Sales_data& lhs, const Sales_data& rhs) {
    return lhs.isbn() == rhs.isbn() && lhs.units_sold == rhs.units_sold 
    && lhs.revenue == rhs.revenue;
}

std::ostream& operator<<(std::ostream& os, const Sales_data& item) {
    os << item.isbn() << " " << item.units_sold << " "
    << item.revenue << " " << item.avg_price();
    return os;
}

std::istream& operator>>(std::istream& is, Sales_data& item) {
    double price;
    is >> item.bookNo >> item.units_sold >> price;
    if (is)     // check inputs succeeded
        item.revenue = item.units_sold * price;
    else        // give default values
        item = Sales_data();
    return is;
}

Sales_data operator+(const Sales_data& lhs, const Sales_data& rhs) {
    Sales_data sum = lhs;
    sum += rhs;     // should implement += as well
    return sum;
}

Sales_data& Sales_data::operator+=(const Sales_data& rhs) {
    revenue += rhs.revenue;
    units_sold += rhs.units_sold;
    return *this;
}

inline bool compareIsbn(const Sales_data& lhs, const Sales_data& rhs) {
    // TODO: explore forwarding.
    return lhs.isbn() == rhs.isbn();
}

// Example of function returning a tuple.
std::vector<matches> findBook(const std::vector<std::vector<Sales_data>>& files, const std::string& book) {
    std::vector<matches> ret;
    for (auto it = files.cbegin(); it != files.cend(); ++it) {
        // find range of items with equal isbn.
        auto found = std::equal_range(it->cbegin(), it->cend(), Sales_data(book), compareIsbn);
        if (found.first != found.second)
            ret.push_back(std::make_tuple(it - files.cbegin(), found.first, found.second));
    }
    return ret; // empty, if no matches.
}

// Example of using tuple returned from a function.
void reportResults(std::istream& in, std::ostream& os, const std::vector<std::vector<Sales_data>>& files) {
    std::string s;      // book to search
    while(in >> s) {
        auto trans = findBook(files, s);    // stores that sold the book
        if (trans.empty()) {
            std::cerr << s << " not found in any stores." << std::endl;
            continue;       // process next book
        }
        for (const auto& store: trans)
            os << "store " << std::get<0>(store) << " sales: "
               << std::accumulate(std::get<1>(store), std::get<2>(store),
                                  Sales_data(s))
               << std::endl;
    }
}

void printValues(int i, double d) {
    std::cout << "i: " << std::setw(12) << i << "next col" << std::endl;
    std::cout << "d: " << std::setw(12) << d << "next col" << std::endl;
}
