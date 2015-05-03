#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Move.h"
#include "Instance.h"
#include "DesignByContract.h"
#include "./TinyXML/tinyxml.h"

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
	void print_ascii();

	/**
	 *	Prints an ascii representation of the room in the console.
	 */	
	void printRoom();
	
	/**
	 *	PRE CONDITIONS:
	 *		is_initialized == false
	 *		width > 0
	 *		height > 0
	 *
	 *	Fills the room width empty instances. (type = 0, movable = false)
	 * 	This function is used during the XML Parsing, so that before any instances are added,
	 *	every cell is set to 'empty'.
	 *	The init() function will throw an error if the room's height and width have not been set yet,
	 *	or when either of them are smaller than 1.
	 *
	 *	POST CONDITIONS:
	 *		is_initialized = true;
	 */
	void init();
	
	/**
	 *	PRE CONDITIONS:
	 *		is_initialized == false
	 *	(only for set)
	 *
	 *	Get and set functions for the 'height' attribute.
	 *	! Starts counting from 1. (so if the height = 10, the 'highest' accessible cell has a y value of 9.)
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
	 */
	void set_width(int w);
	int get_width();
	
	/**
	 *	Get and set functions for the 'name' attribute.
	 *	This attribute is used when writing the room properties to an ascii file,
	 *	to display the room's name. (e.g. 'Level 1')
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
	 */
	bool set_instance(int width, int height, int type);
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
	 */
	void move_instance(int from_width, int from_height, int to_width, int to_height);
	
	/**
	 *	PRE CONDITIONS:
	 *		is_initialized == true
	 *
	 *	Executes a move command, moving the player and other adjacent objects depending on their movable status.
	 *	Returns true if the move was succesfully executed, otherwise returns false.
	 */
	bool execute_move(Move& move);
	
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
	 *	Load the contents of the room using an XML file as input.
	 *	All non-specified cells in the room are automatically filled with "air" (nothing),
	 *	(see: Room::init())
	 *
	 *	POST CONDITIONS:
	 *		is_initialized = true;
	 */
	bool loadFromXMLFile(const char* filename);

	// Add contract




















	// Add Contract
	void parseRoomInfo (TiXmlElement* elem);
	void parseInstance (TiXmlElement* elem);
	void parsePlayer (TiXmlElement* elem);
	
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

	~Room();
};