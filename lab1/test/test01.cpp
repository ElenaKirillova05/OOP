#include "../sol.h"
#include <gtest/gtest.h>

TEST(ClosestPairTest, BasicTest) {
    std::pair<int, int> result = closest_pair_tonum(10);
    EXPECT_EQ(result.first, 5);
    EXPECT_EQ(result.second, 4);
}

TEST(ClosestPairTest, NoPairFound) {
    std::pair<int, int> result = closest_pair_tonum(3);
    EXPECT_EQ(result.first, -1);
    EXPECT_EQ(result.second, -1);
}

TEST(ClosestPairTest, HigherLimitTest) {
    std::pair<int, int> result = closest_pair_tonum(50);
    EXPECT_EQ(result.first, 45);
    EXPECT_EQ(result.second, 36);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
