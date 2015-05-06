#include <iostream>
#include <sstream>
#include <algorithm>
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
}

 void UserInterface::parseCommand (ostream& out, string command) {
	string actual_command;
	istringstream iss(command);

	// Extract the first word
	iss >> actual_command;
	std::transform(actual_command.begin(), actual_command.end(), actual_command.begin(), ::tolower);

	out << "You executed: " << actual_command << endl;

	if (actual_command == "help") {
		printHelp(out);
	}
	
	else if (actual_command == "loadlevel") {
		string filename;
		iss >> filename;
		this->room.loadFromXMLFile(filename.c_str());
	}
	
	else if (actual_command == "loadmoves") {
		string filename;
		iss >> filename;
		this->room.loadMovesFromXMLFile(filename.c_str());
	}
	
	else if (actual_command == "print") {
		out << "Printing: " << endl;
		this->room.printRoom(out);
	}

	else if (actual_command == "printtofile") {
		string filename;
		iss >> filename;
		filename = "game_board_" + filename + ".txt";

		out << "Printing to file '" << filename << "'" << endl;

		std::ofstream file;
		file.open(filename);

		this->room.printRoom(file);
	}

	else if (actual_command == "printtoxmlfile") {
		string filename;
		iss >> filename;
		filename = "xml_game_board_" + filename + ".xml";

		out << "Printing to file '" << filename << "'" << endl;

		std::ofstream file;
		file.open(filename);

		this->room.saveToXMLFile(file);
	}

	else if (actual_command == "printmovestoxmlfile") {
		string filename;
		iss >> filename;
		filename = "xml_moves_" + filename + ".xml";

		out << "Printing to file '" << filename << "'" << endl;

		std::ofstream file;
		file.open(filename);

		this->room.saveMovesToXMLFile(file);
	}

	else if (actual_command == "printtohtmlfile") {
		string filename;
		iss >> filename;
		filename = filename + ".html";

		out << "Printing to file '" << filename << "'" << endl;

		std::ofstream file;
		file.open(filename);

		this->room.saveToHTMLFile(file);
	}
	
	else if (actual_command == "run") {
		string moves;
		iss >> moves;
		this->room.executeMoves("HuidigSpeelveld.txt", "ResterendeBewegingen.txt", atoi(moves.c_str()));
	}

	else if (actual_command == "runall") {
		this->room.executeAllMoves("HuidigSpeelveld.txt", "ResterendeBewegingen.txt");
	}
}

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
	out << "\t Prints the current room to a file called game_board_[filename].txt" << endl << endl;

	out << "- printToXMLFile [filename]" << endl;
	out << "\t Prints the current room to a file called xml_game_board_[filename].xml" << endl << endl;

	out << "- printMovesToXMLFile [filename]" << endl;
	out << "\t Prints the currently left moves to a file called xml_moves_[filename].xml" << endl << endl;

	out << "- printToHTMLFile [filename]" << endl;
	out << "\t Prints the current room to a file called [filename].html" << endl << endl;

	out << "- run [maxsteps]" << endl;
	out << "\t Runs the simulation untill the end" << endl << endl;

	out << "- runAll" << endl;
	out << "\t Runs all the simulation steps" << endl << endl;
}