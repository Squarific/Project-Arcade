#include <iostream>
#include "Room.h"
#include "XMLParser.cpp"

int main() {
	Room current_room;
	
	current_room.loadFromXMLFile("Speelveld1.0.xml");
	current_room.loadMovesFromXMLFile("Bewegingen1.0.xml");
	
	current_room.executeAllMoves("HuidigSpeelveld.txt", "ResterendeBewegingen.txt");
	
	return 0;
}