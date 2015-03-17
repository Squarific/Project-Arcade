#include <iostream>
#include "Room.h"
#include "XMLParser.cpp"

int main(int argc, char *argv[]) {
	Room current_room;
	
	current_room.loadFromXMLFile(argv[1]);
	current_room.loadMovesFromXMLFile(argv[2]);
	
	current_room.executeAllMoves("HuidigSpeelveld.txt", "ResterendeBewegingen.txt");
	
	return 0;
}