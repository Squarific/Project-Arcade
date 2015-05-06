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
// TEST(roomtests, xmlinstancecheck1) {
// 	Room testroom;
// 	testroom.loadFromXMLFile("xmlfiles/Speelveld1.0.xml");
	
// 	EXPECT_EQ(testroom.get_instance(5, 5)->get_type(), 0);
// 	EXPECT_EQ(testroom.get_instance(4, 5)->get_type(), 1);
// 	EXPECT_EQ(testroom.get_instance(0, 0)->get_type(), 2);
// 	EXPECT_EQ(testroom.get_instance(5, 2)->get_type(), 3);
// }

// INSTANCE TEST 2 - NAMES
TEST(roomtests, xmlinstancecheck2) {
	Room testroom;
	testroom.loadFromXMLFile("xmlfiles/Speelveld1.0.xml");
	
	EXPECT_EQ(testroom.get_instance(4, 5)->get_name(), "Chip");
}

// INSTANCE TEST 3 - MOVABLE
// TEST(roomtests, xmlinstancecheck3) {
// 	Room testroom;
// 	testroom.loadFromXMLFile("xmlfiles/Speelveld1.0.xml");
	
// 	EXPECT_FALSE(testroom.get_instance(0, 0)->get_movable());
// 	EXPECT_TRUE(testroom.get_instance(3, 4)->get_movable());
// }

// PLAYER LOCATION TEST
TEST(roomtests, xmlplayerlocationcheck) {
	Room testroom;
	testroom.loadFromXMLFile("xmlfiles/Speelveld1.0.xml");
	
	EXPECT_EQ(testroom.get_player_width(), 4);
	EXPECT_EQ(testroom.get_player_height(), 5);
}