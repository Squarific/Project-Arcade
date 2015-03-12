#include <iostream>
#include <vector>
#include <string>
#include "Instance.cpp"
#include "Move.cpp"

class Room {
  private:
	std::string name;
	int width;
	int height;
	std::vector< std::vector< Instance > > instances;
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
	
	// Prints
	void print_dimensions();
	void print_ascii();
	
	// Init
	// Fills the room width empty instances. (type = 0, moveable = false)
	void init();
	
	// Height
	void set_height(int h);
	int get_height();
	
	// Width
	void set_width(int w);
	int get_width();
	
	// Name
	void set_name(std::string str);
	std::string get_name();
	
	// Instances
	void set_instance(int width, int height, int type, bool moveable);
	Instance get_instance(int width, int height);
	
	// Moves an instance from location 'from', to location 'to'
	// The previous location will be filled with an empty instance.
	void move_instance(int from_width, int from_height, int to_width, int to_height);
	
	// Uses a move instance to move to a certain location, by finding the player's location and executing the move.
	void move_player(Move& move);

	// Player Coordinates
	int get_player_width();
	int get_player_height();

	// XML
	bool loadFromXMLFile(const char* filename);
};

void Room::print_dimensions() {
	std::cout << width << "x" << height << std::endl;
}

void Room::print_ascii() {
	// TOP DASHES
	std::cout << std::string(2 * width + 1, '-') << std::endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::cout << "|" << instances[height - 1 - i][j].get_type();
		}
		std::cout << "|" << std::endl;
		std::cout << std::string(2 * width + 1, '-') << std::endl;
	}
}

void Room::init() {
	if ((width > 0) && (height > 0))
		instances.resize(height, std::vector< Instance >(width, Instance(0, false)));
	else
		std::cout << "ERROR: height and width not correctly set." << std::endl;
}

void Room::set_height(int h) {
	height = h;
}

int Room::get_height() {
	return height;
}

void Room::set_width(int w) {
	width = w;
}

int Room::get_width() {
	return width;
}

void Room::set_name(std::string str) {
	name = str;
}

std::string Room::get_name() {
	return name;
}

void Room::set_instance(int width, int height, int type, bool moveable) {
	instances[height][width].set_type(type);
	instances[height][width].set_moveable(moveable);
}

Instance Room::get_instance(int width, int height) {
	return instances[height][width];
}

void Room::move_instance(int from_width, int from_height, int to_width, int to_height) {
	this->set_instance(to_width, to_height, instances[from_height][from_width].get_type(), instances[from_height][from_width].get_moveable());
	this->set_instance(from_width, from_height, 0, false);
}

int Room::get_player_width() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (instances[i][j].get_type() == 1)
				return j;
		}
	}
}

int Room::get_player_height() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (instances[i][j].get_type() == 1)
				return i;
		}
	}
}

void Room::move_player(Move& move) {
	int player_x = this->get_player_width();
	int player_y = this->get_player_height();
	int direction = move.get_direction();
	int destination_x, destination_y;
	
	if (direction == 0) {
		destination_x = player_x + 1;
		destination_y = player_y;
	}
	else if (direction == 1) {
		destination_x = player_x;
		destination_y = player_y + 1;
	}
	else if (direction == 2) {
		destination_x = player_x - 1;
		destination_y = player_y;
	}
	else if (direction == 3) {
		destination_x = player_x;
		destination_y = player_y - 1;
	}
	
	this->move_instance(player_x, player_y, destination_x, destination_y);
}

int main() {
	Room testroom;
	Move move1(1, "Chip");
	Move move2(0, "Chip");
	
	testroom.set_height(10);
	testroom.set_width(10);
	testroom.init();
	
	testroom.set_instance(1, 1, 1, false);
	
	testroom.move_player(move1);
	testroom.move_player(move2);
	
	testroom.print_dimensions();
	testroom.print_ascii();
	
	return 0;
}