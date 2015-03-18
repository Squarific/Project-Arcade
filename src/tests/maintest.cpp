#include "../Googletests/include/gtest/gtest.h"
#include "Room.h"
#include "XMLParser.cpp"

#include "meta.cpp"
#include "XMLParser.cpp"
#include "RoomTests.cpp"
#include "MoveTests.cpp"

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}