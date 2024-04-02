#include "entry.h"

#include <stdexcept>
entry::entry(std::string const& word, int count) : value(word), count(count) {
    if (count < 0) throw std::invalid_argument("Count cannot be negative");
}

std::string const& entry::operator*() const { return value; }

void entry::operator++(int) { count++; }

entry::operator int() const { return count; }

std::ostream& operator<<(std::ostream& os, entry const& entry) {
    os << '[';
    os << *entry << ' ' << int(entry);
    return os << ']';
}

std::istream& operator>>(std::istream& is, entry& ent) {
    std::string value;
    is >> value;
    value.erase(0, 1);
    std::string count;
    is >> count;
    count.pop_back();
    ent = entry(value, std::stoi(count));
    return is;
}
