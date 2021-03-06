#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <string>
#include "Move.h"
#include "Instance.h"
#include "DesignByContract.h"
#include "./TinyXML/tinyxml.h"

using namespace std;

class Room {
  private:
	std::string name;
	int width;
	int height;
	std::vector< std::vector< Instance > > instances;
	bool is_initialized;
	
  public:
	std::vector< Move*> moves;
	
	Room() {
		width = 0;
		height = 0;
		is_initialized = false;
	}
	
	Room(int w, int h, std::string n) {
		width = w;
		height = h;
		name = n;
	}
	
	/**
	 *	Prints the room's dimensions. Used for testing purposes only.
	 */
	void print_dimensions();
	
	/**
	 *	Prints an ascii representation of the room in the console. Used for testing purposes only.
	 *	If you want to print out the room for use in the UI, please use printRoom().
	 */
	void print_ascii(ostream& out);

	/**
	 *	Prints an ascii representation of the room in the console.
	 */	
	void printRoom(ostream& out);
	
	/**
	 *	PRE CONDITIONS:
	 *		REQUIRE(!is_initialized, "ERROR: Room was already initialized.");
	 *		REQUIRE(width > 0, "ERROR: Width is less than 0. Cannot initialize.")
	 *		REQUIRE(height > 0, "ERROR: Width is less than 0. Cannot initialize.")
	 *
	 *	Fills the room width empty instances. (type = 0, movable = false)
	 * 	This function is used during the XML Parsing, so that before any instances are added,
	 *	every cell is set to 'empty'.
	 *	The init() function will throw an error if the room's height and width have not been set yet,
	 *	or when either of them are smaller than 1.
	 *
	 *	POST CONDITIONS:
	 *		ENSURE(is_initialized, "ERROR: Room could not be initialized.");
	 */
	void init();
	
	/**
	 *	PRE CONDITIONS:
	 *		is_initialized == false
	 *		(only for set)
	 *
	 *	Get and set functions for the 'height' attribute.
	 *	! Starts counting from 1. (so if the height = 10, the 'highest' accessible cell has a y value of 9.)
	 *
	 *	POST CONDITIONS:
	 *		ENSURE(this->get_height() == h, "ERROR: set_height() did not work correctly.");
	 *		(set only)
	 */
	void set_height(int h);
	int get_height();
	
	/**
	 *	PRE CONDITIONS:
	 *		is_initialized == false
	 *	(only for set)
	 *
	 *	Get and set functions for the 'width' attribute.
	 *	! Starts counting from 1. (so if the width = 10, the 'furthest' accessible cell has an x value of 9.)
	 *
	 *	POST CONDITIONS:
	 *		ENSURE(this->get_width() == w, "ERROR: set_width() did not work correctly.");
	 *		(set only)
	 */
	void set_width(int w);
	int get_width();
	
	/**
	 *	Get and set functions for the 'name' attribute.
	 *	This attribute is used when writing the room properties to an ascii file,
	 *	to display the room's name. (e.g. 'Level 1')
	 *
	 *	POST CONDITIONS:
	 *		ENSURE(this->get_name() == str, "ERROR: set_name() did not work correctly.");
	 *		(set only)
	 */
	void set_name(std::string str);
	std::string get_name();
	
	/**
	 *	PRE CONDITIONS:
	 *		is_initialized == true
	 *
	 *	Get and set functions for the instances located in the room.
	 *	the width and height values should be between (0 ; width - 1) or (0 ; height - 1) respectively.
	 *	Note that get_instance() returns a pointer to the instance.
	 *	Since the set_instance() function creates a new object using the new operator,
	 *	it should only be used when parsing the .xml files, not to modify an instance.
	 * 	With set_instance, an optional string id can be included for instances that have an id (Player, Monster, Gate, Button).
	 *
	 *	POST CONDITIONS:
	 *		ENSURE(this->get_instance(width, height) != NULL, "ERROR: set_instance did not work correctly.");
	 *		(set only)
	 */
	bool set_instance(int width, int height, int type);
	bool set_instance(int width, int height, int type, std::string id);
	Instance* get_instance(int width, int height);
	
	/**
	 *	PRE CONDITIONS:
	 *		is_initialized == true
	 *
	 *	Sets an instance's name at a given position.
	 *	The name attribute is not specified in the set_instance() function, because it is only used for Player instances.
	 *	For this reason, a seperate function set_instance_name() was added.
	 */
	void set_instance_name(int width, int height, std::string str);
	
	/**
	 *	PRE CONDITIONS:
	 *		is_initialized == true
	 *
	 *	Moves an instance from location 'from', to location 'to'
	 *	The previous location will be filled with an empty instance.
	 *	This function is used in execute_move(), and should probably not be used anywhere else.
	 *	If you want to move the player, use execute_move().
	 *
	 *	POST CONDITIONS:
	 *		ENSURE(this->get_instance(from_width, from_height) == NULL, "ERROR: move_instance() did not work correctly.");
	 *		ENSURE(this->get_instance(to_width, to_height) != NULL, "ERROR: move_instance() did not work correctly.");
	 */
	void move_instance(int from_width, int from_height, int to_width, int to_height);
	
	/**
	 *	PRE CONDITIONS:
	 *		REQUIRE(is_initialized, "ERROR: Could not execute move because Room was not properly initialized.");
	 *
	 *	Executes a move command, moving the player and other adjacent objects depending on their movable status.
	 *	Returns true if the move was succesfully executed, otherwise returns false.
	 */
	bool execute_move(Move& move);

	/**
	 *	PRE CONDITIONS:
	 *		REQUIRE(is_initialized, "ERROR: Could not execute move because Room was not properly initialized.");
	 *		REQUIRE(move->isAttack, "ERROR: Tried to executeAttack on non-attack move.");
	 *
	 *	Executes an attack command, attacking adjacent objects.
	 *	Returns true if the attack was succesfully executed, otherwise returns false.
	 */
	bool executeAttack(Move*& move, int offset_x, int offset_y);
	
	/**
	 *	PRE CONDITIONS:
	 *		is_initialized == true
	 *
	 *	Tries to execute all moves in the vector<move> moves.
	 *	If a move is succesful, it is removed from the vector.
	 *	Should any of the moves return an error, the function will stop and write the room properties and remaining moves to an ascii file.
	 *	If all moves are finished, the room properties will be written to an ascii file, as well as a file saying there are no remaining moves.
	 */
	void executeAllMoves(const char* roomfilename, const char* movesfilename);
	// Executes n moves, or all moves if there are not enough moves.
	void executeMoves(const char* roomfilename, const char* movesfilename, int n);

	/**
	 *	PRE CONDITIONS:
	 *		is_initialized == true
	 *
	 *	These functions are used to get the player's location on the field.
	 *	In later development stages, a name argument could be added to support multiple players.
	 */
	int get_player_width();
	int get_player_height();

	/**
	 *	PRE CONDITIONS:
	 *		is_initialized == true
	 *
	 *	These functions are used to get an objects location on the field, given an id.
	 */
	int get_instance_width(std::string id);
	int get_instance_height(std::string id);

	/**
	 *	PRE CONDITIONS:
	 *		REQUIRE(doc.LoadFile(), "File " + filename + " not found");
	 *		REQUIRE(doc.FirstChildElement() != NULL, "XML Error: No root element");
	 *		REQUIRE(string(doc.FirstChildElement()->Value()) == "VELD", "XML Error: Root element has to be called 'VELD' but was '" + root->Value() + "'");	
	 *
	 *	Load the contents of the room using an XML file as input.
	 *	All non-specified cells in the room are automatically filled with "air" (nothing),
	 *	(see: Room::init())
	 *
	 *	POST CONDITIONS:
	 *		Room::init() is called
	 *		is_initialized = true;
	 */

	bool loadFromXMLFile(const char* filename);

	/**
	 *	PRE CONDITIONS:
	 *		elem->Value() == "NAAM" || elem->Value() == "LENGTE" || elem->Value() == "BREEDTE"
	 *	
	 *	Parses room info. And calls Room::set_name() or Room::set_height() or Room::set_width()
	 */

	void parseRoomInfo (TiXmlElement* elem);

	/**
	 *	PRE CONDITIONS:
	 *		instanceTypes.count(elem->Value()) != 0
	 *
	 *	Returns a vector <int> (width, height, type) of the parsed element
	 */

	vector <int> parseInstance (TiXmlElement* elem);

	/**
	 *	PRE CONDITIONS:
	 *		instanceTypesWithId.count(elem->Value()) != 0
	 *
	 *	Returns a tuple <int, int, int, string> (width, height, type, id/name) of the parsed element
	 */

	tuple <int, int, int, string> parseInstanceWithId (TiXmlElement* elem);

	/**
	 *	PRE CONDITIONS
	 * 		is_initialized == true
	 *	Saves the current level to an xml file
	 */

	void saveToXMLFile (ostream& file);

	/**
	 *	PRE CONDITIONS
	 * 		is_initialized == true
	 *	Saves the current moves to an xml file
	 */

	void saveMovesToXMLFile (ostream& file);

	/**
	 *	PRE CONDITIONS
	 * 		is_initialized == true
	 *	Saves the current level to an html file
	 */

	void saveToHTMLFile (ostream& file);

	
	/**
	 *	Load the to-be-executed moves from an XML file into the vector<Move> moves.
	 *	Use executeAllMoves() to execute the loaded moves.
	 */

	bool loadMovesFromXMLFile(const char* filename);
	
	/**
	 *	PRE CONDITIONS:
	 *		is_initialized == true
	 *
	 * 	Writes the current state of the room to an ascii file,
	 *	including the name, width, height, location of the player and location(s) of barrels.
	 */

	void writeToFile(const char* filename);
	
	/**
	 *	PRE CONDITIONS:
	 *		is_initialized == true
	 *
	 *	Writes the remaining moves (the moves currently in vector<Move> moves) to an ascii file.
	 *	If there are no moves in the vector, writes "Geen resterende bewegingen".
	 */
	void writeMovesToFile(const char* filename);

	/**
	 *	PRE CONDITIONS:
	 *		REQUIRE(is_initialized, "ERROR: Could not execute any moves because Room was not initialized.");
	 *		REQUIRE(this->get_instance(width, height)->get_type() == 6, "ERROR: That instance is not a button.");
	 *
	 *	Returns a pointer to the gate that is linked to the given button.
	 */
	Instance* getLinkedGate(int width, int height);

	/**
	 *	PRE CONDITIONS:
	 *		is_initialized == true
	 *		
	 *	Removes the instance pointed to by pointer instance
	 */
	void removeInstance(Instance* instance);

	~Room();
};


#endif /* ROOM_H */