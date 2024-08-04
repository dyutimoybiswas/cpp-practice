#include "chapter18.hpp"

namespace cplusplus_primer {
    Sales_data& Sales_data::operator+=(const Sales_data& rhs) {
        if (isbn() != rhs.isbn())
            throw custom_exceptions::isbn_mismatch("wrong isbns", isbn(), rhs.isbn());
        units_sold += rhs.units_sold;
        revenue += rhs.revenue;
        return *this;
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

    // Example of multiple inheritance.
    Panda::Panda(std::string name, bool onExhibit):
    Bear(name, onExhibit), Endangered(Endangered::critical) {}

    // implicitly uses Bear's default constructor.
    Panda::Panda(): Endangered(Endangered::critical) {}
}
