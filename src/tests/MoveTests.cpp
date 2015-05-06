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
	
	EXPECT_EQ(testroom.moves[0]->get_direction(), 1);
	EXPECT_EQ(testroom.moves[1]->get_direction(), 1);
	EXPECT_EQ(testroom.moves[2]->get_direction(), 2);
	EXPECT_EQ(testroom.moves[3]->get_direction(), 1);
	EXPECT_EQ(testroom.moves[4]->get_direction(), 2);
	EXPECT_EQ(testroom.moves[5]->get_direction(), 1);
	EXPECT_EQ(testroom.moves[6]->get_direction(), 0);
}

// GET NAMES
TEST(movetests, namecheck) {
	Room testroom;
	testroom.loadFromXMLFile("xmlfiles/Speelveld1.0.xml");
	testroom.loadMovesFromXMLFile("xmlfiles/Bewegingen1.0.xml");
	
	for (int i = 0; i < 7; i++) {
		EXPECT_EQ(testroom.moves[0]->get_name(), "Chip");
	}
}

// EXECUTE MOVES - CHECK PLAYER LOCATION
TEST(movetests, playermovecheck) {
	Room testroom;
	testroom.loadFromXMLFile("xmlfiles/Level3.xml");
	testroom.loadMovesFromXMLFile("xmlfiles/Level3Complete.xml");
	testroom.executeAllMoves("HuidigSpeelveld.txt", "ResterendeBewegingen.txt");
	
	EXPECT_EQ(testroom.get_instance(5, 8)->get_type(), 0);
	EXPECT_EQ(testroom.get_player_width(), 5);
	EXPECT_EQ(testroom.get_player_height(), 8);
}

// EXECUTE MOVES - CONFIRM BARREL LOCATION
TEST(movetests, barrelmovecheck) {
	Room testroom;
	testroom.loadFromXMLFile("xmlfiles/Level3.xml");
	testroom.loadMovesFromXMLFile("xmlfiles/Level3Complete.xml");
	testroom.executeAllMoves("HuidigSpeelveld.txt", "ResterendeBewegingen.txt");
	
	EXPECT_EQ(testroom.get_instance(2, 7)->get_type(), 2);
}

// EXECUTE N MOVES - CHECK PLAYER LOCATION
TEST(movetests, playermovecheck2) {
	Room testroom;
	testroom.loadFromXMLFile("xmlfiles/Level3.xml");
	testroom.loadMovesFromXMLFile("xmlfiles/Level3Complete.xml");
	testroom.executeMoves("HuidigSpeelveld.txt", "ResterendeBewegingen.txt", 10);
	
	EXPECT_EQ(testroom.get_instance(1, 2)->get_type(), 0);
	EXPECT_EQ(testroom.get_player_width(), 1);
	EXPECT_EQ(testroom.get_player_height(), 2);
}

// EXECUTE N MOVES - CHECK PLAYER LOCATION
TEST(movetests, playermovecheck3) {
	Room testroom;
	testroom.loadFromXMLFile("xmlfiles/Level3.xml");
	testroom.loadMovesFromXMLFile("xmlfiles/Level3Complete.xml");
	testroom.executeMoves("HuidigSpeelveld.txt", "ResterendeBewegingen.txt", 10);
	
	EXPECT_EQ(testroom.get_instance(3, 4)->get_type(), 3);
}

// EXECUTE N MOVES - CONFIRM BARREL LOCATION
TEST(movetests, barrelmovecheck2) {
	Room testroom;
	testroom.loadFromXMLFile("xmlfiles/Level3.xml");
	testroom.loadMovesFromXMLFile("xmlfiles/Level3Complete.xml");
	testroom.executeMoves("HuidigSpeelveld.txt", "ResterendeBewegingen.txt", 10);
	
	EXPECT_EQ(testroom.get_instance(2, 7)->get_type(), 2);
}

// EXECUTE MOVES - CHECK DROWNING
TEST(movetests, drowncheck) {
	Room testroom;
	testroom.loadFromXMLFile("xmlfiles/Level2.xml");
	testroom.loadMovesFromXMLFile("xmlfiles/Level2Drown.xml");
	testroom.executeAllMoves("HuidigSpeelveld.txt", "ResterendeBewegingen.txt", );
	
	EXPECT_EQ(testroom.get_instance(2, 7)->get_type(), 2);
}