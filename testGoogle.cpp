#include <gtest/gtest.h>

#include <sstream>

#include "entry.h"
#include "word_counter.h"
TEST(entry_test, default_ctor) {
    entry entry;
    ASSERT_EQ(*entry, "");
    ASSERT_EQ(int(entry), 0);
}

TEST(entry_test, custom_ctor) {
    entry entry("żabka", 5);
    ASSERT_EQ(*entry, "żabka");
    ASSERT_EQ(int(entry), 5);
}

TEST(entry_test, custom_ctor_negative_count) {
    ASSERT_THROW(entry("żabka", -1), std::exception);
}

TEST(entry_test, operator_pp) {
    entry entry("żabka", 5);
    ASSERT_EQ(int(entry), 5);
    entry++;
    ASSERT_EQ(int(entry), 6);
}

TEST(entry_test, operator_plus_equals_for_int) {
    entry entry("żabka", 5);
    ASSERT_EQ(int(entry), 5);
    entry += 8;
    ASSERT_EQ(int(entry), 13);
}

TEST(entry_test, operator_plus_equals_for_negative_int) {
    entry entry("żabka", 5);
    ASSERT_EQ(int(entry), 5);
    ASSERT_THROW(entry += -9, std::exception);
}

TEST(entry_test, operator_out) {
    entry entry("żabka", 5);
    std::stringstream ss;
    ss << entry;
    ASSERT_EQ(ss.str(), "[żabka 5]");
}

TEST(entry_test, operator_in) {
    std::stringstream ss("[żabka 5]");
    entry entry;
    ss >> entry;
    ASSERT_EQ(*entry, "żabka");
    ASSERT_EQ(int(entry), 5);
}

TEST(word_counter_test, add_word_typical) {
    word_counter wc;
    wc.add_word("hello");
    wc.add_word("world");
    wc.add_word("auto");
    ASSERT_EQ(*(wc.get_counter()[0]), "auto");
    ASSERT_EQ(*(wc.get_counter()[1]), "hello");
    ASSERT_EQ(*(wc.get_counter()[2]), "world");
    ASSERT_EQ(int(wc.get_counter()[0]), 1);
    ASSERT_EQ(int(wc.get_counter()[1]), 1);
    ASSERT_EQ(int(wc.get_counter()[2]), 1);
}

TEST(word_counter_test, add_word_empty_counter) {
    word_counter wc;
    wc.add_word("hello");
    ASSERT_EQ(*(wc.get_counter()[0]), "hello");
    ASSERT_EQ(int(wc.get_counter()[0]), 1);
}

TEST(word_counter_test, add_entry) {
    word_counter wc;
    entry ent("hello", 5);
    wc.add_entry(ent);
    wc.add_entry(ent);
    ASSERT_EQ(*(wc.get_counter())[0], "hello");
    ASSERT_EQ(int(wc.get_counter()[0]), 10);
}

TEST(word_counter_test, add_word_repetition) {
    word_counter wc;
    wc.add_word("hello");
    wc.add_word("world");
    wc.add_word("auto");
    wc.add_word("hello");
    ASSERT_EQ(*(wc.get_counter()[0]), "auto");
    ASSERT_EQ(*(wc.get_counter()[1]), "hello");
    ASSERT_EQ(*(wc.get_counter()[2]), "world");
    ASSERT_EQ(int(wc.get_counter()[0]), 1);
    ASSERT_EQ(int(wc.get_counter()[1]), 2);
    ASSERT_EQ(int(wc.get_counter()[2]), 1);
}

TEST(word_counter_test, add_words_typical) {
    word_counter wc;
    std::stringstream ss("hello world auto");
    wc.add_words(ss);
    ASSERT_EQ(*(wc.get_counter()[0]), "auto");
    ASSERT_EQ(*(wc.get_counter()[1]), "hello");
    ASSERT_EQ(*(wc.get_counter()[2]), "world");
    ASSERT_EQ(int(wc.get_counter()[0]), 1);
    ASSERT_EQ(int(wc.get_counter()[1]), 1);
    ASSERT_EQ(int(wc.get_counter()[2]), 1);
}

TEST(word_counter_test, add_words_repetition) {
    word_counter wc;
    std::stringstream ss("hello world hello auto");
    wc.add_words(ss);
    ASSERT_EQ(*(wc.get_counter()[0]), "auto");
    ASSERT_EQ(*(wc.get_counter()[1]), "hello");
    ASSERT_EQ(*(wc.get_counter()[2]), "world");
    ASSERT_EQ(int(wc.get_counter()[0]), 1);
    ASSERT_EQ(int(wc.get_counter()[1]), 2);
    ASSERT_EQ(int(wc.get_counter()[2]), 1);
}

TEST(word_counter_test, add_words_stream_with_newlines) {
    word_counter wc;
    std::stringstream ss("hello world \n hello auto");
    wc.add_words(ss);
    ASSERT_EQ(*(wc.get_counter()[0]), "auto");
    ASSERT_EQ(*(wc.get_counter()[1]), "hello");
    ASSERT_EQ(*(wc.get_counter()[2]), "world");
    ASSERT_EQ(int(wc.get_counter()[0]), 1);
    ASSERT_EQ(int(wc.get_counter()[1]), 2);
    ASSERT_EQ(int(wc.get_counter()[2]), 1);
}

TEST(word_counter_test, clear_test) {
    word_counter wc;
    std::stringstream ss("hello world \n hello auto");
    wc.add_words(ss);
    ASSERT_EQ(wc.get_counter().size(), 3);
    wc.clear();
    ASSERT_EQ(wc.get_counter().empty(), true);
}

TEST(word_counter_test, index_operator) {
    word_counter wc;
    std::stringstream ss("hello world \n hello auto");
    wc.add_words(ss);
    ASSERT_EQ(*(wc["hello"]), "hello");
    ASSERT_EQ(int(wc["hello"]), 2);
}

TEST(word_counter_test, index_operator_word_not_found) {
    word_counter wc;
    std::stringstream ss("hello world \n hello auto");
    wc.add_words(ss);
    ASSERT_THROW(wc["apple"], std::exception);
}

TEST(word_counter_test, lex_begin) {
    word_counter wc;
    std::stringstream ss("hello world dua lipa third may hello auto");
    wc.add_words(ss);
    word_counter::lex_iterator lit = wc.lex_begin();
    ASSERT_EQ(*(*lit), "auto");
}

TEST(word_counter_test, lex_iterator_test) {
    word_counter wc;
    std::stringstream ss("hello world \n hello auto");
    wc.add_words(ss);
    word_counter::lex_iterator lit = wc.lex_begin();
    ASSERT_EQ(*(*lit), "auto");
    lit++;
    ASSERT_EQ(*(*lit), "hello");
    lit++;
    ASSERT_EQ(*(*lit), "world");
}

TEST(word_counter_test, lex_iterator_test_2) {
    word_counter wc;
    std::stringstream ss("hello world dua lipa third may hello auto");
    wc.add_words(ss);
    word_counter::lex_iterator lit = wc.lex_begin();
    word_counter::lex_iterator lit_2 = wc.lex_end();
    ASSERT_EQ(lit != lit_2, true);
}

TEST(word_counter_test, freq_begin) {
    word_counter wc;
    std::stringstream ss("hello world dua lipa third may hello auto");
    wc.add_words(ss);
    word_counter::freq_iterator fit = wc.freq_begin();
    ASSERT_EQ(*(*fit), "hello");
}

TEST(word_counter_test, freq_iterator_test) {
    word_counter wc;
    std::stringstream ss("hello world dua dua lipa hello auto");
    wc.add_words(ss);
    word_counter::freq_iterator fit = wc.freq_begin();
    ASSERT_EQ(*(*fit), "dua");
    fit++;
    ASSERT_EQ(*(*fit), "hello");
    fit++;
    ASSERT_EQ(*(*fit), "auto");
    fit++;
    ASSERT_EQ(*(*fit), "lipa");
    fit++;
    ASSERT_EQ(*(*fit), "world");
}

TEST(word_counter_test, freq_iterator_test_2) {
    word_counter wc;
    std::stringstream ss("dance all night dance all night i be like ooh all");
    wc.add_words(ss);
    std::stringstream out;
    word_counter::freq_iterator fit = wc.freq_begin();
    for (; fit != wc.freq_end(); ++fit) {
        out << *fit;
    }
    out << *fit;
    ASSERT_EQ(out.str(), "[all 3][dance 2][night 2][be 1][i 1][like 1][ooh 1]");
}

TEST(word_counter_test, freq_iterator_test_3) {
    word_counter wc;
    std::stringstream ss(
        "dance dance world world world open track track zebra zebra zebra");
    wc.add_words(ss);
    std::stringstream out;
    word_counter::freq_iterator fit = wc.freq_begin();
    for (; fit != wc.freq_end(); ++fit) {
        out << *fit;
    }
    out << *fit;
    ASSERT_EQ(out.str(), "[world 3][zebra 3][dance 2][track 2][open 1]");
}

TEST(word_counter_test, freq_iterator_test_4) {
    word_counter wc;
    std::stringstream ss("dua dua");
    wc.add_words(ss);
    word_counter::freq_iterator fit = wc.freq_begin();
    word_counter::freq_iterator fit_end = wc.freq_end();
    ASSERT_EQ(*(*fit), "dua");
    fit++;
}

TEST(word_counter_test, operator_plus_equals_no_repetition) {
    word_counter wc1;
    std::stringstream words1("hello world hello world");
    wc1.add_words(words1);
    word_counter wc2;
    std::stringstream words2("live laugh love dua lipa");
    wc2.add_words(words2);
    wc1 += wc2;
    ASSERT_EQ(*(wc1.get_counter()[0]), "dua");
    ASSERT_EQ(int(wc1.get_counter()[0]), 1);
    ASSERT_EQ(*(wc1.get_counter()[1]), "hello");
    ASSERT_EQ(int(wc1.get_counter()[1]), 2);
    ASSERT_EQ(*(wc1.get_counter()[2]), "laugh");
    ASSERT_EQ(int(wc1.get_counter()[2]), 1);
    ASSERT_EQ(*(wc1.get_counter()[3]), "lipa");
    ASSERT_EQ(int(wc1.get_counter()[3]), 1);
    ASSERT_EQ(*(wc1.get_counter()[4]), "live");
    ASSERT_EQ(int(wc1.get_counter()[4]), 1);
    ASSERT_EQ(*(wc1.get_counter()[5]), "love");
    ASSERT_EQ(int(wc1.get_counter()[5]), 1);
    ASSERT_EQ(*(wc1.get_counter()[6]), "world");
    ASSERT_EQ(int(wc1.get_counter()[6]), 2);
}

TEST(word_counter_test, operator_plus_equals_repetition) {
    word_counter wc1;
    std::stringstream words1("hello world hello world");
    wc1.add_words(words1);
    word_counter wc2;
    std::stringstream words2("hello world hello dua");
    wc2.add_words(words2);
    wc1 += wc2;
    ASSERT_EQ(*(wc1.get_counter()[0]), "dua");
    ASSERT_EQ(int(wc1.get_counter()[0]), 1);
    ASSERT_EQ(*(wc1.get_counter()[1]), "hello");
    ASSERT_EQ(int(wc1.get_counter()[1]), 4);
    ASSERT_EQ(*(wc1.get_counter()[2]), "world");
    ASSERT_EQ(int(wc1.get_counter()[2]), 3);
}

TEST(word_counter_test, operator_out) {
    word_counter wc;
    std::stringstream words("hello world \n hello auto");
    wc.add_words(words);
    std::stringstream ss;
    ss << wc;
    ASSERT_EQ(ss.str(), "[auto 1]\n[hello 2]\n[world 1]\n");
}

TEST(word_counter_test, operator_in) {
    word_counter wc;
    std::stringstream ss("[auto 1]\n[hello 2]\n[world 1]\n");
    ss >> wc;
    ASSERT_EQ(*(wc.get_counter()[0]), "auto");
    ASSERT_EQ(*(wc.get_counter()[1]), "hello");
    ASSERT_EQ(*(wc.get_counter()[2]), "world");
    ASSERT_EQ(int(wc.get_counter()[0]), 1);
    ASSERT_EQ(int(wc.get_counter()[1]), 2);
    ASSERT_EQ(int(wc.get_counter()[2]), 1);
}

TEST(word_counter_test, operator_in_2) {
    word_counter wc;
    std::stringstream ss("[auto 1][hello 2][world 1]");
    ss >> wc;
    ASSERT_EQ(*(wc.get_counter()[0]), "auto");
    ASSERT_EQ(*(wc.get_counter()[1]), "hello");
    ASSERT_EQ(*(wc.get_counter()[2]), "world");
    ASSERT_EQ(int(wc.get_counter()[0]), 1);
    ASSERT_EQ(int(wc.get_counter()[1]), 2);
    ASSERT_EQ(int(wc.get_counter()[2]), 1);
}
