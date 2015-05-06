// 
TEST(filecompare, levelRight) {
	Room testroom;
	testroom.loadFromXMLFile("xmlfiles/Level3.xml");
	testroom.loadMovesFromXMLFile("xmlfiles/Level3Complete.xml");
	testroom.executeAllMoves("HuidigSpeelveld.txt", "ResterendeBewegingen.txt");

	EXPECT_TRUE(FileCompare("HuidigSpeelveld.txt", "filecompare/SpeelveldComplete.txt"));
}

TEST(filecompare, movesRight) {
	Room testroom;
	testroom.loadFromXMLFile("xmlfiles/Level3.xml");
	testroom.loadMovesFromXMLFile("xmlfiles/Level3Complete.xml");
	testroom.executeAllMoves("HuidigSpeelveld.txt", "ResterendeBewegingen.txt");

	EXPECT_TRUE(FileCompare("ResterendeBewegingen.txt", "filecompare/BewegingenComplete.txt"));
}

TEST(filecompare, levelWrong) {
	Room testroom;
	testroom.loadFromXMLFile("xmlfiles/Level3.xml");
	testroom.loadMovesFromXMLFile("xmlfiles/Level3Complete.xml");
	testroom.executeAllMoves("HuidigSpeelveld.txt", "ResterendeBewegingen.txt");

	EXPECT_FALSE(FileCompare("HuidigSpeelveld.txt", "filecompare/SpeelveldWrong.txt"));
}

TEST(filecompare, movesWrong) {
	Room testroom;
	testroom.loadFromXMLFile("xmlfiles/Level3.xml");
	testroom.loadMovesFromXMLFile("xmlfiles/Level3Complete.xml");
	testroom.executeAllMoves("HuidigSpeelveld.txt", "ResterendeBewegingen.txt");

	EXPECT_FALSE(FileCompare("ResterendeBewegingen.txt", "filecompare/BewegingenWrong.txt"));
}