#include "chapter15.hpp"

Bulk_quote::Bulk_quote(const std::string& book, double p, size_t qty, double disc):
Disc_quote(book, p, qty, disc) {}

double Bulk_quote::net_price(size_t cnt) const {
    if (cnt >= min_qty)
        return cnt * (1 - discount) * price;
    else
        return cnt * price; /*alternate way: Quote::net_price(cnt);*/
}

void Quote::debug() { std::cout << "book no: " << bookNo << ", price = " << price << std::endl; }

void Bulk_quote::debug() { std::cout << "min qty: " << min_qty << ", discount = " << discount << std::endl; }

double print_total(std::ostream& os, const Quote& item, size_t n) {
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

void runQueries (std::ifstream& infile) {
    TextQuery tq(infile);
    while (true) {
        std::cout << "Enter word(s) to look for, or q to quit: ";
        std::string s;
        if (!(getline(std::cin, s)) || s == "q") // quit if EOF or q is input
            break;
        print(std::cout, tq.handleQuery(s)) << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const Query& query) { return os << query.rep(); }

Query::Query(const std::string& s): q(new WordQuery(s)) {}

TextQuery::TextQuery(std::ifstream& is) : file(new std::vector<std::string>) {
    std::string text;
    while (getline(is, text)) {         // read each line into text
        file->push_back(text);
        int n = file->size() - 1;       // line number
        std::istringstream line(text);  // parse words
        std::string word;
        while (line >> word) {
            // store words without punctuations as map keys. Note that words are case-sensitive.
            word.erase(std::remove_if(word.begin(), word.end(), [](char ch) -> bool { return ispunct(ch); }), word.end());
            auto& lines = wm[word];     // add new entry if not present
            if (!lines)                 // not present (new entry)
                lines.reset(new std::set<line_no>);     // add a new set as value
            lines->insert(n);           // add line number to set
        }
    }
}

QueryResult TextQuery::handleQuery(const std::string& expression) const {

    // TODO: handle validations - invalid operator-operand combo (op1 ~ op2, & | op1 etc).
    if (!expression.empty()) {
        std::vector<Query> queries;
        std::vector<char> operators;
        std::string word;
        for (char ch: expression) {
            if (isspace(ch))        // ignore spaces
                continue;
            if (ispunct(ch)) {
                if ((ch == '~' || ch == '&' || ch == '|') && ch != expression.back())
                    operators.push_back(ch);
                else
                    throw std::invalid_argument("Invalid expression.");
                if (!word.empty())
                    queries.push_back(Query(word));
                word.clear();
            } else {
                word += ch;
            }
        }
        if (!word.empty())        // last word.
            queries.push_back(Query(word));

        // Evaluate not queries.
        for (size_t i = 0; i < operators.size(); ++i) {
            if (operators[i] == '~') {
                queries[i] = ~queries[i];
                operators.erase(operators.begin() + i);
            }
        }

        // Handle other operators.
        for (size_t i = 0; i < operators.size(); ++i) {
            switch (operators[i]) {
                case '&':
                    queries[i + 1] = queries[i] & queries[i + 1];
                    break;
                case '|':
                    queries[i + 1] = queries[i] | queries[i + 1];
                    break;
            }
        }

        return queries.back().eval(*this);
    }
    
    return query(expression);
}

QueryResult TextQuery::query(const std::string& sought) const {
    // if sought not found.
    std::shared_ptr<std::set<line_no>> nodata (new std::set<line_no>);
    auto loc = wm.find(sought);     // use find instead of [] to avoid adding sought to wm
    if (loc == wm.end())            // not found
        return QueryResult(sought, nodata, file);
    else
        return QueryResult(sought, loc->second, file);
}

std::ostream& print(std::ostream& os, const QueryResult& qr) {
    // print occurrences.
    os << qr.sought << " occurs " << qr.lines->size() << " time(s)" << std::endl;
    // print lines where occurred.
    for (auto num: *qr.lines)
        os << "\t(line " << (num+1) << ") " << *(qr.file->begin() + num) << std::endl;
    return os;
}

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