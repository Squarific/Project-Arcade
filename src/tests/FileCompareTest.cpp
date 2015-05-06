// 
TEST(filecompare, filecomparecomplete) {
	Room testroom;
	testroom.loadFromXMLFile("xmlfiles/Level3.xml");
	testroom.loadMovesFromXMLFile("xmlfiles/Level3Complete.xml");
	testroom.executeAllMoves("HuidigSpeelveld.txt", "ResterendeBewegingen.txt");

	EXPECT_TRUE(FileCompare("HuidigSpeelveld.txt", "filecompare/SpeelveldComplete.txt"));
	EXPECT_TRUE(FileCompare("ResterendeBewegingen.txt", "filecompare/BewegingenComplete.txt"));
}