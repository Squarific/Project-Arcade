// DUMMY TEST
TEST(filetests, dummytest) {
	EXPECT_TRUE(true);
	EXPECT_EQ(1, 1);
}

// Correct XML's
TEST(movetests, correctfiles) {
	Room testroom;
	EXPECT_TRUE(testroom.loadFromXMLFile("xmlfiles/Speelveld1.0.xml"));
	EXPECT_TRUE(testroom.loadMovesFromXMLFile("xmlfiles/Bewegingen1.0.xml"));
}

// XML's that do no exist 1
TEST(movetests, wrongxml1) {
	Room testroom;
	EXPECT_FALSE(testroom.loadFromXMLFile("xmlfiles/Idontexist.xml"));
}

// XML's that do no exist 2
TEST(movetests, wrongxml1) {
	Room testroom;
	EXPECT_TRUE(testroom.loadFromXMLFile("xmlfiles/Speelveld1.0.xml"));
	EXPECT_FALSE(testroom.loadMovesFromXMLFile("xmlfiles/NeitherdoI.xml"));
}

// Wrong ROOT 1
TEST(movetests, wrongxml2) {
	Room testroom;
	EXPECT_FALSE(testroom.loadFromXMLFile("xmlfiles/Speelveld1.0_incorrect_root.xml"));
}

// Wrong ROOT 2
TEST(movetests, wrongxml3) {
	Room testroom;
	EXPECT_TRUE(testroom.loadFromXMLFile("xmlfiles/Speelveld1.0.xml"));
	EXPECT_FALSE(testroom.loadMovesFromXMLFile("xmlfiles/Bewegingen1.0_incorrect_root.xml"));
}

// No ROOT 1
TEST(movetests, wrongxml2) {
	Room testroom;
	EXPECT_FALSE(testroom.loadFromXMLFile("xmlfiles/Speelveld1.0_no_root.xml"));
}

// No ROOT 2
TEST(movetests, wrongxml3) {
	Room testroom;
	EXPECT_TRUE(testroom.loadFromXMLFile("xmlfiles/Speelveld1.0.xml"));
	EXPECT_FALSE(testroom.loadMovesFromXMLFile("xmlfiles/Bewegingen1.0_no_root.xml"));
}