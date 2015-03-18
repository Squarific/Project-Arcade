// DUMMY TEST
TEST(movetests, dummytest) {
	EXPECT_TRUE(true);
	EXPECT_EQ(1, 1);
}

// GET DIRECTIONS
TEST(movetests, directioncheck) {
	Room testroom;
	testroom.loadFromXMLFile("xmlfiles/Speelveld1.0.xml");
	testroom.loadMovesFromXMLFile("xmlfiles/Bewegingen1.0.xml");
	
	EXPECT_EQ(testroom.moves[0].get_direction(), 1);
	EXPECT_EQ(testroom.moves[1].get_direction(), 1);
	EXPECT_EQ(testroom.moves[2].get_direction(), 2);
	EXPECT_EQ(testroom.moves[3].get_direction(), 1);
	EXPECT_EQ(testroom.moves[4].get_direction(), 2);
	EXPECT_EQ(testroom.moves[5].get_direction(), 1);
	EXPECT_EQ(testroom.moves[6].get_direction(), 0);
}

// GET NAMES
TEST(movetests, namecheck) {
	Room testroom;
	testroom.loadFromXMLFile("xmlfiles/Speelveld1.0.xml");
	testroom.loadMovesFromXMLFile("xmlfiles/Bewegingen1.0.xml");
	
	for (int i = 0; i < 7; i++) {
		EXPECT_EQ(testroom.moves[0].get_name(), "Chip");
	}
}

// EXECUTE MOVES - CHECK PLAYER LOCATION
TEST(movetests, playermovecheck) {
	Room testroom;
	testroom.loadFromXMLFile("xmlfiles/Speelveld1.0.xml");
	testroom.loadMovesFromXMLFile("xmlfiles/Bewegingen1.0.xml");
	testroom.executeAllMoves("HuidigSpeelveld.txt", "ResterendeBewegingen.txt");
	
	EXPECT_EQ(testroom.get_instance(2, 8).get_type(), 1);
	EXPECT_EQ(testroom.get_player_width(), 2);
	EXPECT_EQ(testroom.get_player_height(), 8);
}

// EXECUTE MOVES - CHECK BARREL LOCATIONS
TEST(movetests, playermovecheck) {
	Room testroom;
	testroom.loadFromXMLFile("xmlfiles/Speelveld1.0.xml");
	testroom.loadMovesFromXMLFile("xmlfiles/Bewegingen1.0.xml");
	testroom.executeAllMoves("HuidigSpeelveld.txt", "ResterendeBewegingen.txt");
	
	EXPECT_EQ(testroom.get_instance(5, 1).get_type(), 3);
	EXPECT_EQ(testroom.get_instance(5, 2).get_type(), 3);
	EXPECT_EQ(testroom.get_instance(3, 4).get_type(), 3);
}