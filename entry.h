#pragma once
#include <string>
#include <iostream>

class Entry {
   private:
    std::string value;
    int count = 0;

   public:
    Entry() = default;
    Entry(std::string const& word, int count);

    void operator++(int);
    std::string const& operator*() const;
    operator int() const;
};

std::ostream& operator<<(std::ostream& os, Entry const& entry);
std::istream& operator>>(std::istream& is, Entry& entry);