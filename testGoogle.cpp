#include <gtest/gtest.h>

#include <sstream>

#include "entry.h"
TEST(EntryTest, default_ctor) {
    Entry entry;
    ASSERT_EQ(*entry, "");
    ASSERT_EQ(int(entry), 0);
}

TEST(EntryTest, custom_ctor) {
    Entry entry("żabka", 5);
    ASSERT_EQ(*entry, "żabka");
    ASSERT_EQ(int(entry), 5);
}

TEST(EntryTest, custom_ctor_negative_count) {
    ASSERT_THROW(Entry("żabka", -1), std::exception);
}

TEST(EntryTest, operator_pp) {
    Entry entry("żabka", 5);
    ASSERT_EQ(int(entry), 5);
    entry++;
    ASSERT_EQ(int(entry), 6);
}

TEST(EntryTest, operator_out) {
    Entry entry("żabka", 5);
    std::stringstream ss;
    ss << entry;
    ASSERT_EQ(ss.str(), "[żabka 5]");
}

TEST(EntryTest, operator_in) {
    std::stringstream ss("[żabka 5]");
    Entry entry;
    ss >> entry;
    ASSERT_EQ(*entry, "żabka");
    ASSERT_EQ(int(entry), 5);
}