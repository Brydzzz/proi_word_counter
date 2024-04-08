#pragma once
#include <vector>

#include "entry.h"
class word_counter {
   private:
    std::vector<entry> counter;

   public:
    word_counter() = default;

    std::vector<entry> get_counter() const;

    void add_word(std::string const& word);
    void add_words(std::istream& is);
    void add_entry(entry const& ent);
    void clear();

    entry const& operator[](std::string const& word) const;
    entry& operator[](std::string const& word);

    class lex_iterator {
        std::vector<entry>::const_iterator it;

       public:
        lex_iterator(std::vector<entry>::const_iterator vit) : it(vit) {}

        lex_iterator operator++(int);
        lex_iterator& operator++();
        entry const& operator*() const;
        bool operator!=(lex_iterator const& wcit) const;
    };
    lex_iterator lex_begin() const;
    lex_iterator lex_end() const;

    class freq_iterator {
        std::vector<entry>::const_iterator it;

       public:
        freq_iterator(std::vector<entry>::const_iterator vit) : it(vit) {}

        freq_iterator operator++(int);
        freq_iterator& operator++();
        entry const& operator*() const;
        bool operator!=(freq_iterator const& wcit) const;
    };

    freq_iterator freq_begin() const;
    freq_iterator freq_end() const;

    word_counter& operator+=(const word_counter& other);

    friend std::ostream& operator<<(std::ostream& os, word_counter const& wc);
    friend std::istream& operator>>(std::istream& is, word_counter& wc);
};
