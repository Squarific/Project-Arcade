#include "Room.h"

class UserInterface {
private:
	Room room;
public:
	UserInterface(){};
	~UserInterface(){};
	
	/**
	 * Enters the user interface menu in a blocking way
	 */
	void enterMenu (istream& in, ostream& out);

	/**
	 * Executes the given command (if it is valid)
	 */
	void parseCommand (ostream& out, string command);

	/**
	 * Prints the help menu, displaying all available commands and how to use them.
	 */
	void printHelp (ostream& out);
};