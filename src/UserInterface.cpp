#include <iostream>
#include "UserInterface.h"

using namespace std;

void UserInterface::enterMenu (istream& in, ostream& out) {
	bool quit = false;

	this->printHelp(out);

	while (!quit) {
		string command;

		out << "Give a command: ";
		getline(in, command);
		out << endl;

		this->parseCommand(out, command);
	}
};

void UserInterface::parseCommand (ostream& out, string command) {
	out << "Test" << endl;
};

void UserInterface::printHelp (ostream& out) {
	out << "The following commands are available:" << endl << endl;

	out << "- help" << endl;
	out << "\t Prints this help menu" << endl << endl;

	out << "- loadLevel [filename]" << endl;
	out << "\t Parses the given xml file as a level" << endl << endl;

	out << "- loadMoves [filename]" << endl;
	out << "\t Parses the given xml file as moves" << endl << endl;

	out << "- print" << endl;
	out << "\t Prints the current room" << endl << endl;

	out << "- run [maxsteps]" << endl;
	out << "\t Runs the simulation untill the end" << endl;
	out << "\t If maxsteps is a positive number the simulation is run till the end or till maxsteps steps have been executed whichever comes first." << endl << endl;
};