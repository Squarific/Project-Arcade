#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Move.h"
#include "Instance.h"

class Room {
  private:
	std::string name;
	int width;
	int height;
	std::vector< std::vector< Instance > > instances;
	std::vector< Move> moves;
	bool is_initialized;
  public:
	
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
	
	// Prints the room's dimensions. Used for testing purposes only.
	void print_dimensions();
	
	// Prints an ascii representation of the room in the console. Used for testing purposes only.
	void print_ascii();
	
	// Fills the room width empty instances. (type = 0, movable = false)
	void init();
	
	// Get and set for height
	void set_height(int h);
	int get_height();
	
	// Get and set for width
	void set_width(int w);
	int get_width();
	
	// Get and set for name
	void set_name(std::string str);
	std::string get_name();
	
	// Get and set for instances
	void set_instance(int width, int height, int type, bool movable);
	Instance get_instance(int width, int height); // ! RETURNS A COPY !
	
	// Sets an instance's name at position (width, height)
	void set_instance_name(int width, int height, std::string str);
	
	// Moves an instance from location 'from', to location 'to'
	// The previous location will be filled with an empty instance.
	void move_instance(int from_width, int from_height, int to_width, int to_height);
	
	// Executes a move command, moving the player and other adjacent objects depending on their movable status.
	// Returns true if the move was succesfully executed, otherwise returns false.
	bool execute_move(Move& move);
	
	// Tries to execute all moves in the vector<move> moves.
	// Should any of the moves return an error, the function will stop and write the room properties and remaining moves to an ascii file.
	// If all moves are finished, the room properties will be written to an ascii file, as well as a file saying there are no remaining moves.
	void executeAllMoves(const char* roomfilename, const char* movesfilename);

	// These functions are used to get the player's location on the field
	// In later development stages, a name argument could be added to support multiple players
	int get_player_width();
	int get_player_height();

	// Load the contents of the room using an XML file as input.
	// All non-specified cells in the room are automatically filled with "air" (nothing)
	bool loadFromXMLFile(const char* filename);
	
	// Load to-be-executed moves from an XML file into the vector<Move> moves
	// Use executeAllMoves() to execute the loaded moves.
	bool loadMovesFromXMLFile(const char* filename);
	
	// Writes the current room state to a file
	void writeToFile(const char* filename);
	
	// Write the remaining moves to a file
	void writeMovesToFile(const char* filename);
};