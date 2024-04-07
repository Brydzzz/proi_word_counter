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
