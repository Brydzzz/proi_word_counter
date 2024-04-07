#include "word_counter.h"

std::vector<entry> word_counter::get_counter() const { return counter; }

void word_counter::add_word(std::string const& word) {
    if (counter.size() == 0) {
        counter.push_back(entry(word, 1));
        return;
    }

    for (size_t i = 0; i < counter.size(); ++i) {
        if (*counter[i] == word) {
            counter[i]++;
            return;
        }
    }

    int insert_idx = counter.size();
    for (size_t i = counter.size() - 1; i >= 0; --i) {
        if (*counter[i] > word)
            insert_idx = i;
        else
            break;
    }
    counter.insert(counter.begin() + insert_idx, entry(word, 1));
}

void word_counter::add_words(std::istream& is) {
    std::string word;
    while (is >> word) {
        add_word(word);
    }
}

void word_counter::clear() { counter.clear(); }

std::ostream& operator<<(std::ostream& os, word_counter const& wc) {
    for (size_t i = 0; i < wc.counter.size(); ++i) {
        os << wc.counter[i];
    }
    return os;
}
