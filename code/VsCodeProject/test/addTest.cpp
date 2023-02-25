#include <gtest/gtest.h>
#include <add.hpp>

TEST(add, first_google_test_addition)
{
    int expected = 2 + 3;
    int result = add(2, 3);
    ASSERT_EQ(expected, result);
}

TEST(add, second_google_test_addition)
{
    int expected = 2 + 3;
    int c;
    int result = add(2, 3);
    EXPECT_EQ(expected, result)<<"Message";
}

TEST(add, three_google_test_addition)
{
    int expected = 2 + 3;
    int result = add(2, 3);
    ASSERT_EQ(expected, result);
}
