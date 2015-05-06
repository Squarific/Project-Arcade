#include <iostream>
#include <fstream>
#include <sys/stat.h>

bool FileCompare(const std::string leftFileName, const std::string rightFileName) {
	ifstream leftFile, rightFile;
	char leftRead, rightRead;
	bool result;

	// Open the two files.
	leftFile.open(leftFileName);
	if (!leftFile.is_open()) {
		return false;
	};
	rightFile.open(rightFileName);
	if (!rightFile.is_open()) {
		leftFile.close();
		return false;
	};

	result = true; // files exist and are open; assume equality unless a counterexamples shows up.
	while (result && leftFile.good() && rightFile.good()) {
		leftFile.get(leftRead);
		rightFile.get(rightRead);
		result = (leftRead == rightRead);
	};
	if (result) {
		 // last read was still equal; are we at the end of both files ?
		result = (!leftFile.good()) && (!rightFile.good());
	};

	leftFile.close();
	rightFile.close();
	return result;
}

// DUMMY TEST
TEST(filecompare, dummytest) {
	EXPECT_TRUE(true);
	EXPECT_EQ(1, 1);
}

// 
TEST(filecompare, filecomparecomplete) {
	Room testroom;
	testroom.loadFromXMLFile("xmlfiles/Level3.xml");
	testroom.loadMovesFromXMLFile("xmlfiles/Level3Complete.xml")
	testroom.executeAllMoves("HuidigSpeelveld.txt", "ResterendeBewegingen.txt");

	EXPECT_TRUE(FileCompare("HuidigSpeelveld.txt", "filecompare/SpeelveldComplete.txt"));
	EXPECT_TRUE(FileCompare("ResterendeBewegingen.txt", "filecompare/BewegingenComplete.txt"));
}