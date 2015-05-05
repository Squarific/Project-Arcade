#include "Room.h"

class UserInterface {
private:
	Room room;
public:
	UserInterface(){};
	~UserInterface(){};
	
	/*
	 *	Enters the user interface menu in a blocking way
	 */
	void enterMenu (istream& in, ostream& out);
	void parseCommand (ostream& out, string command);
	void printHelp (ostream& out);
};