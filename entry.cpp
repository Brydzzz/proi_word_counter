#include "entry.h"

#include <stdexcept>
Entry::Entry(std::string const& word, int count) : value(word), count(count) {
    if (count < 0) throw std::invalid_argument("Count cannot be negative");
}

std::string const& Entry::operator*() const { return value; }

void Entry::operator++(int) { count++; }

Entry::operator int() const { return count; }

std::ostream& operator<<(std::ostream& os, Entry const& entry) {
    os << '[';
    os << *entry << ' ' << int(entry);
    return os << ']';
}

std::istream& operator>>(std::istream& is, Entry& entry) {
    std::string value;
    is >> value;
    value.erase(0, 1);
    std::string count;
    is >> count;
    count.pop_back();
    Entry ent(value, std::stoi(count));
    entry = ent;
    return is;
}
