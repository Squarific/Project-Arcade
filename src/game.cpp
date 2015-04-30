#include <iostream>
#include "Room.h"
#include "XMLParser.cpp"

int main(int argc, char *argv[]) {
	Room current_room;

	if (argc < 3) {
		if (argc == 1) {
			std::cout << "No arguments given. Entering the developer testing grounds..." << std::endl;

			current_room.set_height(10);
			current_room.set_width(10);
			current_room.init();

			current_room.set_instance(3, 3, 0);

			current_room.print_ascii();

			std::cout << "Leaving developer testing grounds!\nCYA" << std::endl;

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