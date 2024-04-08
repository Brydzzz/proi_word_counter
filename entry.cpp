#include "entry.h"

#include <stdexcept>
entry::entry(std::string const& word, int count) : value(word), count(count) {
    if (count < 0) throw std::invalid_argument("Count cannot be negative");
}

std::string const& entry::operator*() const { return value; }

void entry::operator++(int) { count++; }

entry::operator int() const { return count; }

bool entry::operator<(std::string const& str_value) const {
    return *(*this) < str_value;
}

std::ostream& operator<<(std::ostream& os, entry const& entry) {
    os << '[';
    os << *entry << ' ' << int(entry);
    return os << ']';
}

std::istream& operator>>(std::istream& is, entry& ent) {
    char left, right;
    std::string word;
    int count;
    is >> left;
    if (is.eof()) return is;
    is >> word >> count >> right;
    if (left != '[' || right != ']')
        throw std::invalid_argument("Invalid entry in >> operator.");
    ent.value = word;
    ent.count = count;
    return is;
}
