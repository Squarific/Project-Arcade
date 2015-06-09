#include "../Googletests/include/gtest/gtest.h"
#include "../Room.h"
#include "../XMLParser.cpp"
#include "../UserInterface.h"
#include <fstream>

bool FileCompare(std::string leftFileName, std::string rightFileName) {
	std::ifstream leftFile, rightFile;
	char leftRead, rightRead;
	bool result;

	// Open the two files.
	leftFile.open(leftFileName);
	if (!leftFile.is_open()) {
		return false;
	}
	rightFile.open(rightFileName);
	if (!rightFile.is_open()) {
		leftFile.close();
		return false;
	}
	result = true; // files exist and are open; assume equality unless a counterexamples shows up.
	while (result && leftFile.good() && rightFile.good()) {
		leftFile.get(leftRead);
		rightFile.get(rightRead);
		
		if (leftFile.eof() && rightFile.eof()) {
			break;
		}
		if (leftFile.eof() || rightFile.eof()) {
			result = false;
			break;
		}
		
		result = (leftRead == rightRead);
	}
	
	if (result) {
		// last read was still equal; are we at the end of both files ?
		result = (!leftFile.good()) && (!rightFile.good());
	}
	
	leftFile.close();
	rightFile.close();
	return result;
}

#include "meta.cpp"
#include "XMLParserTests.cpp"
#include "RoomTests.cpp"
#include "MoveTests.cpp"
#include "MetaFileCompareTest.cpp"
#include "FileCompareTest.cpp"
#include "FaultyXML.cpp"
#include "UserInterfaceTests.cpp"

int main(int argc, char *argv[]) {
	::testing::FLAGS_gtest_death_test_style = "threadsafe";
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}