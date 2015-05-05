#include <iostream>
#include "UserInterface.h"
#include "Room.h"
#include "XMLParser.cpp"

int main(int argc, char *argv[]) {
	Room current_room;

	if (argc < 3) {
		if (argc == 1) {
			UserInterface ui;
			ui.enterMenu(cin, cout);

			return 0;
		}
		else {
			std::cerr << "Please provide a playing field .xml file and movement .xml file" << std::endl;
			return 1;
		}
	}
	
	current_room.loadFromXMLFile(argv[1]);
	current_room.loadMovesFromXMLFile(argv[2]);
	
	current_room.executeAllMoves("HuidigSpeelveld.txt", "ResterendeBewegingen.txt");
	
	return 0;
}