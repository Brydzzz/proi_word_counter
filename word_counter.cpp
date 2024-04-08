#include "word_counter.h"

#include <algorithm>
std::vector<entry> word_counter::get_counter() const { return counter; }

void word_counter::add_word(std::string const& word) {
    if (word == "") return;
    entry ent(word, 1);
    add_entry(ent);
}

void word_counter::add_entry(entry const& ent) {
    if (counter.size() == 0) {
        counter.push_back(ent);
        return;
    }

    for (size_t i = 0; i < counter.size(); ++i) {
        if (*counter[i] == *ent) {
            counter[i]++;
            return;
        }
    }

    int insert_idx = counter.size();
    for (int i = counter.size() - 1; i >= 0; --i) {
        if (*counter[i] > *ent)
            insert_idx = i;
        else
            break;
    }
    counter.insert(counter.begin() + insert_idx, ent);
}

void word_counter::add_words(std::istream& is) {
    std::string word;
    while (is >> word) {
        add_word(word);
    }
}

void word_counter::clear() { counter.clear(); }

entry const& word_counter::operator[](std::string const& word) const {
    auto it = std::lower_bound(counter.begin(), counter.end(), word);
    if (*(*it) == word)
        return *it;
    else
        throw std::invalid_argument("Word is not in counter.");
}

entry& word_counter::operator[](std::string const& word) {
    auto it = std::lower_bound(counter.begin(), counter.end(), word);
    if (*(*it) == word)
        return *it;
    else
        throw std::invalid_argument("Word is not in counter.");
}

word_counter::lex_iterator word_counter::lex_begin() const {
    return counter.begin();
}
word_counter::lex_iterator word_counter::lex_end() const {
    return counter.end();
}

word_counter::lex_iterator word_counter::lex_iterator::operator++(int) {
    auto retv = *this;
    it++;
    return retv;
}

word_counter::lex_iterator& word_counter::lex_iterator::operator++() {
    ++it;
    return *this;
}

entry const& word_counter::lex_iterator::operator*() const { return *it; }

bool word_counter::lex_iterator::operator!=(lex_iterator const& wcit) const {
    return it != wcit.it;
}

std::ostream& operator<<(std::ostream& os, word_counter const& wc) {
    for (size_t i = 0; i < wc.counter.size(); ++i) {
        os << wc.counter[i] << '\n';
    }
    return os;
}

std::istream& operator>>(std::istream& is, word_counter& wc) {
    entry ent;
    while (is >> ent) {
        wc.add_entry(ent);
    }
    return is;
}
