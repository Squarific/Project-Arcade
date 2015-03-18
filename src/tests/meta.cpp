TEST(Meta, assert_tests) {
	// Test that verifys the ASSERT functions and if some
	// funny person redefined true and false
	ASSERT_TRUE(true);
	ASSERT_FALSE(false);
	ASSERT_EQ(1, 1);
	ASSERT_EQ(true, true);
	ASSERT_NE(1, 5);
	ASSERT_NE(true, false);
}