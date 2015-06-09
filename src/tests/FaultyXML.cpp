TEST(faultyXML, emptyActies) {
	Room testroom;
	EXPECT_DEATH(testroom.loadMovesFromXMLFile("xmlfiles/FaultyXML/empty.xml"), "empty");
}

TEST(faultyXML, emptySpeelveld) {
	Room testroom;
	EXPECT_DEATH(testroom.loadFromXMLFile("xmlfiles/FaultyXML/empty.xml"), "empty");
}

TEST(faultyXML, emptyBoth) {
	Room testroom;
	EXPECT_DEATH(testroom.loadFromXMLFile("xmlfiles/FaultyXML/empty.xml"), "empty");
	EXPECT_DEATH(testroom.loadMovesFromXMLFile("xmlfiles/FaultyXML/empty.xml"), "empty");
}

TEST(faultyXML, noFileActies) {
	Room testroom;
	EXPECT_DEATH(testroom.loadMovesFromXMLFile("xmlfiles/FaultyXML/ishouldnotexist.xml"), "not found");
}

TEST(faultyXML, noFileLevel) {
	Room testroom;
	EXPECT_DEATH(testroom.loadFromXMLFile("xmlfiles/FaultyXML/ishouldnotexist.xml"), "not found");
}

TEST(faultyXML, noFileBoth) {
	Room testroom;
	EXPECT_DEATH(testroom.loadFromXMLFile("xmlfiles/FaultyXML/ishouldnotexist.xml"), "not found");
	EXPECT_DEATH(testroom.loadMovesFromXMLFile("xmlfiles/FaultyXML/ishouldnotexist.xml"), "not found");
}

TEST(faultyXML, extraRICHTING) {
	Room testroom;
	EXPECT_TRUE(testroom.loadMovesFromXMLFile("xmlfiles/FaultyXML/Acties_extra_RICHTING_tags.xml"));
}

TEST(faultyXML, missingID) {
	Room testroom;
	EXPECT_DEATH(testroom.loadMovesFromXMLFile("xmlfiles/FaultyXML/Acties_missing_id.xml"), "MISSING TAGS");
}

TEST(faultyXML, noRoot) {
	Room testroom;
	EXPECT_DEATH(testroom.loadMovesFromXMLFile("xmlfiles/FaultyXML/Acties_no_root.xml"), "Root element has to be called 'BEWEGINGEN' or 'ACTIES'");
}

TEST(faultyXML, wrongRoot) {
	Room testroom;
	EXPECT_DEATH(testroom.loadMovesFromXMLFile("xmlfiles/FaultyXML/Acties_wrong_root.xml"), "Root element has to be called 'BEWEGINGEN' or 'ACTIES'");
}

TEST(faultyXML, brokenTags) {
	Room testroom;
	EXPECT_DEATH(testroom.loadFromXMLFile("xmlfiles/FaultyXML/Speelveld_broken_tag.xml"), "syntax error");
}

TEST(faultyXML, missingLength) {
	Room testroom;
	EXPECT_DEATH(testroom.loadFromXMLFile("xmlfiles/FaultyXML/Speelveld_missing_length.xml"), "Height is less than 0");
}

TEST(faultyXML, missingName) {
	Room testroom;
	EXPECT_TRUE(testroom.loadFromXMLFile("xmlfiles/FaultyXML/Speelveld_missing_name.xml"));
}

TEST(faultyXML, noRootField) {
	Room testroom;
	EXPECT_DEATH(testroom.loadFromXMLFile("xmlfiles/FaultyXML/Speelveld_no_root.xml"), "Root element has to be called 'VELD'");
}

TEST(faultyXML, wrongRootField) {
	Room testroom;
	EXPECT_DEATH(testroom.loadFromXMLFile("xmlfiles/FaultyXML/Speelveld_wrong_root.xml"), "Root element has to be called 'VELD'");
}

TEST(faultyXML, onlyRootField) {
	Room testroom;
	EXPECT_DEATH(testroom.loadFromXMLFile("xmlfiles/FaultyXML/Speelveld_only_root.xml"), "Width is less than 0");
}