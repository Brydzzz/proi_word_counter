#pragma once
#include <iostream>
#include <string>

class entry {
   private:
    std::string value;
    int count = 0;

   public:
    entry() = default;
    entry(std::string const& word, int count);

    void operator++(int);
    std::string const& operator*() const;
    operator int() const;
};

std::ostream& operator<<(std::ostream& os, entry const& entry);
std::istream& operator>>(std::istream& is, entry& entry);