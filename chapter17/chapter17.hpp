#ifndef CHAPTER17_HPP
#define CHAPTER17_HPP

#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <bitset>
#include <iomanip>

class Sales_data {

    friend std::ostream& operator<<(std::ostream&, const Sales_data&);
    friend std::istream& operator>>(std::istream&, Sales_data&);
    friend Sales_data operator+(const Sales_data&, const Sales_data&);
    friend bool operator==(const Sales_data&, const Sales_data&);
    inline friend bool operator!=(const Sales_data& lhs, const Sales_data& rhs) {
        return !(lhs == rhs);
    }
    friend bool compareIsbn(const Sales_data&, const Sales_data&);

    public:
        Sales_data(unsigned int units = 0, double rev = 0.0, std::string bNo = "test-123"): 
        units_sold(units), revenue(rev), bookNo(bNo) { }
        Sales_data(std::string b): bookNo(b) {}
        Sales_data& operator+=(const Sales_data&);
    
    private:
        inline std::string isbn() const { return bookNo; }
        unsigned int units_sold;
        double revenue;
        inline double avg_price() const { 
            return units_sold ? revenue / units_sold : 0;
        }
        std::string bookNo;
};

// store index and iterators to Sales_data vector.
typedef std::tuple<std::vector<Sales_data>::size_type,
                   std::vector<Sales_data>::const_iterator,
                   std::vector<Sales_data>::const_iterator> matches;
std::vector<matches> findBook(const std::vector<std::vector<Sales_data>>&, const std::string&);
void reportResults(std::istream&, std::ostream&, const std::vector<std::vector<Sales_data>>&);

void printValues(int, double);

#endif
