#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Move.h"
#include "Instance.h"
#include "DesignByContract.h"

void Room::print_dimensions() {
	std::cout << width << "x" << height << std::endl;
}

void Room::print_ascii() {
	// TOP DASHES
	std::cout << std::string(2 * width + 1, '-') << std::endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (get_instance(j, height - 1 -i) == NULL) {
				std::cout << "| ";
			}
			else {
				std::cout << "|" << get_instance(j, height - 1 -i)->get_type();
			}
		}
		std::cout << "|" << std::endl;
		std::cout << std::string(2 * width + 1, '-') << std::endl;
	}
}

void Room::printRoom() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (get_instance(j, height - 1 -i) == NULL) {
				std::cout << " ";
			}
			else {
				std::cout << get_instance(j, height - 1 -i)->getSymbol();
			}
		}
		std::cout << std::endl;
	}
}

void Room::init() {
	REQUIRE(!is_initialized, "ERROR: Room was already initialized.");

	if ((width > 0) && (height > 0)) {
		instances.resize(height, std::vector< Instance*>(width, NULL));
		is_initialized = true;
	}
	else
		std::cerr << "ERROR: height and width not correctly set. Could not initialize Room." << std::endl;
}

void Room::set_height(int h) {
	REQUIRE(!is_initialized, "ERROR: Room was already initialized. Cannot change dimensions after initializing the room.");
	
	height = h;
}

int Room::get_height() {
	return height;
}

void Room::set_width(int w) {
	REQUIRE(!is_initialized, "ERROR: Room was already initialized. Cannot change dimensions after initializing the room.");

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

bool Room::set_instance(int width, int height, int type) {
	REQUIRE(is_initialized, "ERROR: Could not set instance because Room was not properly initialized.");
	REQUIRE(type >= 0, "ERROR: Instance type should be at least 0. Please refer to the header files to see which value represents which instance.")
	REQUIRE(type < 7, "ERROR: Instance type should be less than 7. Please refer to the header files to see which value represents which instance.")
	
	if (type == 0) {
		Player* instance = new Player();
		instances[height][width] = instance;
		return true;
	}
	else if (type == 1) {
		Wall* instance = new Wall();
		instances[height][width] = instance;
		return true;
	}
	else if (type == 2) {
		Barrel* instance = new Barrel();
		instances[height][width] = instance;
		return true;
	}
	else if (type == 3) {
		Monster* instance = new Monster();
		instances[height][width] = instance;
		return true;
	}
	else if (type == 4) {
		Water* instance = new Water();
		instances[height][width] = instance;
		return true;
	}
	else if (type == 5) {
		Gate* instance = new Gate();
		instances[height][width] = instance;
		return true;
	}
	else if (type == 6) {
		Button* instance = new Button();
		instances[height][width] = instance;
		return true;
	}
	else if (type == 7) {
		Target* instance = new Target();
		instances[height][width] = instance;
		return true;
	}
	else
		return false;
}

bool Room::set_instance(int width, int height, int type, std::string id) {
	REQUIRE(is_initialized, "ERROR: Could not set instance because Room was not properly initialized.");
	REQUIRE(type >= 0, "ERROR: Instance type should be at least 0. Please refer to the header files to see which value represents which instance.")
	REQUIRE(type < 8, "ERROR: Instance type should be less than 8. Please refer to the header files to see which value represents which instance.")
	REQUIRE(type != 1, "ERROR: Instance: Wall does not have an id. Please use set_instance(width, height, type).")
	REQUIRE(type != 2, "ERROR: Instance: Barrel does not have an id. Please use set_instance(width, height, type).")
	REQUIRE(type != 4, "ERROR: Instance: Water does not have an id. Please use set_instance(width, height, type).")
	REQUIRE(type != 7, "ERROR: Instance: Target does not have an id. Please use set_instance(width, height, type).")

	if (type == 0) {
		Player* instance = new Player(id);
		instances[height][width] = instance;
		return true;
	}
	else if (type == 3) {
		Monster* instance = new Monster(id);
		instances[height][width] = instance;
		return true;
	}
	else if (type == 5) {
		Gate* instance = new Gate(id);
		instances[height][width] = instance;
		return true;
	}
	else if (type == 6) {
		Button* instance = new Button(id);
		instances[height][width] = instance;
		return true;
	}
	else
		return false;	
}

Instance* Room::get_instance(int width, int height) {
	REQUIRE(is_initialized, "ERROR: Could not get_instance() because Room was not properly initialized. Returning empty instance.");
	
	return instances[height][width];
}

void Room::set_instance_name(int width, int height, std::string str) {
	REQUIRE(is_initialized, "ERROR: Could not set_instance_name() because Room was not properly initialized.");
	
	get_instance(width, height)->set_name(str);
}

void Room::move_instance(int from_width, int from_height, int to_width, int to_height) {
	REQUIRE(is_initialized, "ERROR: Could not move_instance() because Room was not properly initialized.");
	
	instances[to_height][to_width] = instances[from_height][from_width];
	instances[from_height][from_width] = NULL;
}

int Room::get_player_width() {
	REQUIRE(is_initialized, "ERROR: Could not get_player_width() because Room was not properly initialized.");
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (get_instance(j, i) == NULL)
				continue;
			if (get_instance(j, i)->get_type() == 0)
				return j;
		}
	}

	return 0;
}

int Room::get_player_height() {
	REQUIRE(is_initialized, "ERROR: Could not get_player_height() because Room was not properly initialized.");
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (get_instance(j, i) == NULL)
				continue;
			if (get_instance(j, i)->get_type() == 0)
				return i;
		}
	}

	return 0;
}

bool Room::execute_move(Move*& move) {
	REQUIRE(is_initialized, "ERROR: Could not execute move because Room was not properly initialized.");
	
	int player_x = this->get_player_width();
	int player_y = this->get_player_height();
	int direction = move->get_direction();
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
		std::cerr << "ERROR: Destination is out of bounds" << std::endl;
		return false;
	}
	
	// Destination is air
	if (get_instance(player_x + offset_x, player_y + offset_y) == NULL) {
		this->move_instance(player_x, player_y, player_x + offset_x, player_y + offset_y);
		return true;
	}

	// Destination is water
	if (get_instance(player_x + offset_x, player_y + offset_y)->get_type() == 4) {
		std::cerr << "GAME OVER: Destination contains water. You died!" << std::endl;
		return false;
	}

	// Destination is the target
	if (get_instance(player_x + offset_x, player_y + offset_y)->get_type() == 7) {
		std::cerr << "YOU WIN: You have reached the target. Good job!" << std::endl;
		return false;
	}

	// Destination is a non-movable instance and is not air
	if (! get_instance(player_x + offset_x, player_y + offset_y)->get_movable()) {
		std::cerr << "ERROR: Destination contains a non-movable instance" << std::endl;
		return false;
	}
	
	// Destination is a moveable instance
	if (get_instance(player_x + offset_x, player_y + offset_y)->get_movable()) {
		// Object behind destination is out of bounds -> moveable object gets pushed off the platform
		if ((player_x + 2 * offset_x > width) || (player_x + 2 * offset_x < 0) || (player_y + 2 * offset_y > height) || (player_y + 2 * offset_y < 0)) {
			this->move_instance(player_x, player_y, player_x + offset_x, player_y + offset_y);
			return true;
		}
		// Object behind destination is not air -> cannot move in that direction
		if (get_instance(player_x + 2 * offset_x, player_y + 2 * offset_y) != NULL) {
			std::cerr << "ERROR: Second non-air instance located behind moveable instance" << std::endl;
			return false;
		}
		// Object behind destination is air -> move both objects
		this->move_instance(player_x + offset_x, player_y + offset_y, player_x + 2 * offset_x, player_y + 2 * offset_y);
		this->move_instance(player_x, player_y, player_x + offset_x, player_y + offset_y);
		return true;
	}
	
	// If this pops up, the code above is not correct.
	std::cerr << "ERROR: Move not recognized" << std::endl;
	return false;
}

void Room::writeToFile(const char* filename) {
	REQUIRE(is_initialized, "ERROR: Could not write room properties to file because Room was not properly initialized.");
	
	std::ofstream file;
	file.open(filename);
	
	// Room properties
	file << "Het huidige speelveld is " << name << "\n";
	file << "Eigenschappen van dit veld:\n- Breedte: " << width << "\n- Hoogte: " << height << "\n\n";
	
	// Player location
	int player_x = get_player_width();
	int player_y = get_player_height();
	file << "Speler " << get_instance(player_x, player_y)->get_name() << " bevindt zich in het speelveld op positie (" << player_x << ", " << player_y << ").\n\n";
	
	// Barrel locations
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (get_instance(j, i) == NULL)
				continue;

			// Barrel
			if (get_instance(j, i)->get_type() == 2) {
				file << "Er bevindt zich een ton op positie (" << j << ", " << i << ").\n\n";
			}

			// Monster
			if (get_instance(j, i)->get_type() == 3) {
				file << "Er bevindt zich een monster op positie (" << j << ", " << i << ").\n\n";
			}

			// Water
			if (get_instance(j, i)->get_type() == 4) {
				file << "Er bevindt zich water op positie (" << j << ", " << i << ").\n\n";
			}

			// Gate
			if (get_instance(j, i)->get_type() == 5) {
				file << "Er bevindt zich een poort (met id " << get_instance(j, i)->get_name() << ") op positie (" << j << ", " << i << ").\n\n";
			}

			// Button
			if (get_instance(j, i)->get_type() == 6) {
				file << "Er bevindt zich een knop (gelinkt aan poort" << get_instance(j, i)->get_name() << ") op positie (" << j << ", " << i << ").\n\n";
			}

			// Target
			if (get_instance(j, i)->get_type() == 7) {
				file << "Er bevindt zich een doel op positie (" << j << ", " << i << ").\n\n";
			}
		}
	}
	
	file.close();
}

void Room::writeMovesToFile(const char* filename) {
	REQUIRE(is_initialized, "ERROR: Could not write remaining moves to file because Room was not properly initialized.");
	
	std::string directionstr;
	std::ofstream file;
	file.open(filename);
	
	if (moves.size() == 0) {
		file << "Geen resterende bewegingen.";
	}
	else {
		for (std::vector< Move*>::iterator it = moves.begin(); it != moves.end(); ++it) {
			Move* tempmove = *it;
		
			if (tempmove->get_direction() == 0) {
				directionstr = "Rechts";
			}
			else if (tempmove->get_direction() == 1) {
				directionstr = "Omhoog";
			}
			else if (tempmove->get_direction() == 2) {
				directionstr = "Links";
			}
			else if (tempmove->get_direction() == 3) {
				directionstr = "Omlaag";
			}
			file << "Speler " << tempmove->get_name() << " zal volgende beweging nog uitvoeren: \n" << directionstr << "\n\n";
		}
	}
	
	file.close();
}

void Room::executeAllMoves(const char* roomfilename, const char* movesfilename) {
	REQUIRE(is_initialized, "ERROR: Could not execute any moves because Room was not initialized.");
	
	while (moves.size() != 0) {
		if (this->execute_move(*moves.begin())) {
			moves.erase(moves.begin());
		}
		else {
			std::cerr << "ERROR: Could not execute move. Writing current room state and remaining moves to ascii file." << std::endl;
			break;
		}
	}
	
	this->writeToFile(roomfilename);
	this->writeMovesToFile(movesfilename);
	
	return;
}

Room::~Room() {}