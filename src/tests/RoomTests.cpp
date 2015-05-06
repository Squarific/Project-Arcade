// DUMMY TEST
TEST(roomtests, dummytest) {
	EXPECT_TRUE(true);
	EXPECT_EQ(1, 1);
}

// HEIGHT AND WIDTH - CORRECT
TEST(roomtests, xmlheightwidthcheck) {
	Room testroom;
	testroom.loadFromXMLFile("xmlfiles/Speelveld1.0.xml");
	
	EXPECT_EQ(testroom.get_width(), 10);
	EXPECT_EQ(testroom.get_height(), 10);
}

// ROOM NAME
TEST(roomtests, xmlnamecheck) {
	Room testroom;
	testroom.loadFromXMLFile("xmlfiles/Speelveld1.0.xml");
	
	EXPECT_EQ(testroom.get_name(), "Level 1");
}

// INSTANCE TEST 1 - TYPES
TEST(roomtests, xmlinstancecheck1) {
	Room testroom;
	testroom.loadFromXMLFile("xmlfiles/Level3.xml");
	
	EXPECT_EQ(testroom.get_instance(0, 9)->get_type(), 1);
	EXPECT_EQ(testroom.get_instance(2, 7)->get_type(), 2);
	EXPECT_EQ(testroom.get_instance(2, 8)->get_type(), 3);
	EXPECT_EQ(testroom.get_instance(5, 7)->get_type(), 5);
	EXPECT_EQ(testroom.get_instance(8, 8)->get_type(), 6);
	EXPECT_EQ(testroom.get_instance(5, 8)->get_type(), 7);
}

// INSTANCE TEST 2 - NAMES
TEST(roomtests, xmlinstancecheck2) {
	Room testroom;
	testroom.loadFromXMLFile("xmlfiles/Speelveld1.0.xml");
	
	EXPECT_EQ(testroom.get_instance(4, 5)->get_name(), "Chip");
}

// INSTANCE TEST 3 - MOVABLE
TEST(roomtests, xmlinstancecheck3) {
	Room testroom;
	testroom.loadFromXMLFile("xmlfiles/Level3.xml");

	EXPECT_FALSE(testroom.get_instance(6, 8)->get_movable());
	EXPECT_TRUE(testroom.get_instance(2, 7)->get_movable());
}

// INSTANCE TEST 4 - WATER
TEST(roomtests, xmlinstancecheck4) {
	Room testroom;
	testroom.loadFromXMLFile("xmlfiles/Level2.xml");
	
	EXPECT_EQ(testroom.get_instance(1, 5)->get_type(), 4);
	EXPECT_EQ(testroom.get_instance(2, 5)->get_type(), 4);
	EXPECT_EQ(testroom.get_instance(1, 6)->get_type(), 4);
	EXPECT_EQ(testroom.get_instance(2, 6)->get_type(), 4);
}

// PLAYER LOCATION TEST
TEST(roomtests, xmlplayerlocationcheck) {
	Room testroom;
	testroom.loadFromXMLFile("xmlfiles/Speelveld1.0.xml");
	
	EXPECT_EQ(testroom.get_player_width(), 4);
	EXPECT_EQ(testroom.get_player_height(), 5);
}