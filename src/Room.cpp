#include <iostream>
#include <vector>
#include <string>
#include "Move.cpp"
#include "Instance.cpp"

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
	// Fills the room width empty instances. (type = 0, movable = false)
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
	void set_instance(int width, int height, int type, bool movable);
	Instance get_instance(int width, int height); // RETURNS A COPY!
	void set_instance_name(int width, int height, std::string str);
	
	// Moves an instance from location 'from', to location 'to'
	// The previous location will be filled with an empty instance.
	void move_instance(int from_width, int from_height, int to_width, int to_height);
	
	// Executes a move command, moving the player and other adjacent objects depending on their movable status.
	void execute_move(Move& move);

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

void Room::set_instance(int width, int height, int type, bool movable) {
	instances[height][width].set_type(type);
	instances[height][width].set_movable(movable);
}

Instance Room::get_instance(int width, int height) {
	return instances[height][width];
}

void Room::set_instance_name(int width, int height, std::string str) {
	instances[height][width].set_name(str);
}

void Room::move_instance(int from_width, int from_height, int to_width, int to_height) {
	this->set_instance(to_width, to_height, instances[from_height][from_width].get_type(), instances[from_height][from_width].get_movable());
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

void Room::execute_move(Move& move) {
	int player_x = this->get_player_width();
	int player_y = this->get_player_height();
	int direction = move.get_direction();
	int offset_x, offset_y;
	
	// Get offset
	if (direction == 0) {
		offset_x = 1;
		offset_y = 0;
	}
	else if (direction == 1) {
		offset_x = 0;
		offset_y = 1;
	}
	else if (direction == 2) {
		offset_x = -1;
		offset_y = 0;
	}
	else if (direction == 3) {
		offset_x = 0;
		offset_y = -1;
	}
	
	// Destination out of bounds
	if ((player_x + offset_x > width) || (player_x + offset_x < 0) || (player_y + offset_y > height) || (player_y + offset_y < 0)) {
		std::cout << "ERROR: Destination is out of bounds" << std::endl;
		return;
	}
	
	// Destination is air
	if (instances[player_y + offset_y][player_x + offset_x].get_type() == 0) {
		this->move_instance(player_x, player_y, player_x + offset_x, player_y + offset_y);
		return;
	}
	
	// Destination is a non-movable instance and is not air
	if (instances[player_y + offset_y][player_x + offset_x].get_movable() == false) {
		std::cout << "ERROR: Destination contains a non-movable instance" << std::endl;
		return;
	}
	
	// Destination is a moveable instance
	if (instances[player_y + offset_y][player_x + offset_x].get_movable()) {
		// Object behind destination is out of bounds -> moveable object gets pushed off the platform
		if ((player_x + 2 * offset_x > width) || (player_x + 2 * offset_x < 0) || (player_y + 2 * offset_y > height) || (player_y + 2 * offset_y < 0)) {
			this->move_instance(player_x, player_y, player_x + offset_x, player_y + offset_y);
			return;
		}
		// Object behind destination is not air -> cannot move in that direction
		if (instances[player_y + 2 * offset_y][player_x + 2 * offset_x].get_type() != 0) {
			std::cout << "ERROR: Second non-air instance located behind moveable instance" << std::endl;
			return;
		}
		// Object behind destination is air -> move both objects
		this->move_instance(player_x + offset_x, player_y + offset_y, player_x + 2 * offset_x, player_y + 2 * offset_y);
		this->move_instance(player_x, player_y, player_x + offset_x, player_y + offset_y);
		return;
	}
	
	// If this pops up, the code above is not correct.
	std::cout << "ERROR: Move not recognized" << std::endl;
}