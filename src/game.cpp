#include <iostream>
#include "Room.cpp"
#include "./TinyXML/tinyxml.h"
#include "XMLParser.cpp"

int main() {
	Room testroom;
	
	testroom.loadFromXmlFile("Speelveld1.0.xml")
	
	testroom.print_dimensions();
	testroom.print_ascii();
	
	return 0;
}