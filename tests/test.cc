#include <gtest/gtest.h>

int add(int a, int b) {
    return a + b;
}

TEST(AddTest, AddFunctionTest) {
    ASSERT_EQ(add(1, 2), 3);
    ASSERT_EQ(add(1, 2), 4);
}

int main() {
    return RUN_ALL_TESTS();
}
