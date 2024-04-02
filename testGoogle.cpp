#include <gtest/gtest.h>

#include <sstream>

#include "entry.h"
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