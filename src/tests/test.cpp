#include "../GTests/include/gtest/gtest.h"

TEST(simpletest, simpletestname) {
	EXPECT_TRUE(true);
	EXPECT_TRUE(false);
}

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}