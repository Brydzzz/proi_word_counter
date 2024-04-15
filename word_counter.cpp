#include "word_counter.h"

#include <algorithm>
std::vector<entry> word_counter::get_counter() const { return counter; }

word_counter::word_counter(std::initializer_list<entry> lst) {
    for (entry ent : lst) {
        add_entry(ent);
    }
}

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

    std::vector<entry>::iterator it =
        std::lower_bound(counter.begin(), counter.end(), *ent);
    if (**it == *ent) {
        *it += int(ent);
    } else {
        counter.insert(it, ent);
    }
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

word_counter::freq_iterator word_counter::freq_begin() const {
    std::vector<entry>::const_iterator biggest = counter.begin();
    for (auto it = counter.begin(); it < counter.end(); ++it) {
        if (int(*biggest) < int(*it)) {
            biggest = it;
        }
    }
    return freq_iterator(biggest, counter.begin(), counter.end());
}

word_counter::freq_iterator word_counter::freq_end() const {
    std::vector<entry>::const_iterator smallest = counter.begin();
    for (auto it = counter.begin(); it < counter.end(); ++it) {
        if (int(*smallest) >= int(*it)) {
            smallest = it;
        }
    }
    return freq_iterator(smallest, counter.begin(), counter.end());
}

word_counter::freq_iterator word_counter::freq_iterator::operator++(int) {
    auto retv = *this;
    operator++();
    return retv;
}

word_counter::freq_iterator& word_counter::freq_iterator::operator++() {
    std::vector<entry>::const_iterator biggest = it;
    for (auto i = counter_begin; i < counter_end; ++i) {
        if (int(*i) > int(*it) || i == it) {
            continue;
        } else if (int(*i) == int(*it)) {
            if (**i > **it) {
                it = i;
                return *this;
            }
            continue;
        } else if (int(*i) > int(*biggest) || biggest == it) {
            biggest = i;
        }
    }
    it = biggest;
    return *this;
}

entry const& word_counter::freq_iterator::operator*() const { return *it; }

bool word_counter::freq_iterator::operator!=(freq_iterator const& wcit) const {
    return it != wcit.it;
}

word_counter& word_counter::operator+=(const word_counter& other) {
    for (word_counter::lex_iterator it = other.lex_begin();
         it != other.lex_end(); ++it) {
        add_entry(*it);
    }
    return *this;
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
