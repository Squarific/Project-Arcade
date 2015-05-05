#include <iostream>
#include <sstream>
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
	string actual_command;
	istringstream iss(command);

	// Extract the first word
	iss >> actual_command;

	out << "You executed: " << actual_command << endl;

	if (actual_command == "help") {
		printHelp(out);
	}
	
	else if (actual_command == "loadlevel" || actual_command == "loadLevel") {
		string filename;
		iss >> filename;
		this->room.loadFromXMLFile(filename.c_str());
	}
	
	else if (actual_command == "loadmoves" || actual_command == "loadMoves") {
		string filename;
		iss >> filename;
		this->room.loadMovesFromXMLFile(filename.c_str());
	}
	
	else if (actual_command == "print") {
		out << "Printing: " << endl;
		this->room.printRoom(out);
	}

	else if (actual_command == "printToFile") {
		string filename;
		iss >> filename;
		filename = "game_board_" + filename;

		out << "Printing to file '" << filename << "'" << endl;

		std::ofstream file;
		file.open(filename);

		this->room.printRoom(file);
	}
	
	else if (actual_command == "run") {
		string moves;
		iss >> moves;
		this->room.executeMoves("HuidigSpeelveld.txt", "ResterendeBewegingen.txt", atoi(moves.c_str()));
	}
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

	out << "- printToFile [filename]" << endl;
	out << "\t Prints the current room to a file called game_board_[filename]" << endl << endl;

	out << "- run [maxsteps]" << endl;
	out << "\t Runs the simulation untill the end" << endl;
	out << "\t If maxsteps is a positive number the simulation is run till the end or till maxsteps steps have been executed whichever comes first." << endl << endl;
};