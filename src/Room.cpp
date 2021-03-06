#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Move.h"
#include "Instance.h"
#include "DesignByContract.h"

using namespace std;

class Room {
  private:
	std::string name;
	int width;
	int height;
	std::vector< std::vector< Instance*> > instances;
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
		is_initialized = false;
	}

	~Room();
	
	// Prints
	void print_dimensions();
	void print_ascii(ostream& out);
	void printRoom(ostream& out);

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
	bool set_instance(int width, int height, int type);
	bool set_instance(int width, int height, int type, std::string id);
	Instance* get_instance(int width, int height);
	void set_instance_name(int width, int height, std::string str);
	
	// Moves an instance from location 'from', to location 'to'
	// The previous location will be filled with an empty instance.
	void move_instance(int from_width, int from_height, int to_width, int to_height);
	
	// Executes a move command, moving the player and other adjacent objects depending on their movable status.
	// Returns true if the move was succesfully executed, otherwise returns false.
	bool execute_move(Move*& move);
	bool executeAttack(Move*& move, int offset_x, int offset_y);
	
	// Tries to execute all moves in the vector<move> moves.
	// Should any of the moves return an error, the function will stop and write the room properties and remaining moves to an ascii file.
	// If all moves are finished, the room properties will be written to an ascii file, as well as a file saying there are no remaining moves.
	void executeAllMoves(const char* roomfilename, const char* movesfilename);
	// Executes n moves, or all moves if there are not enough moves.
	void executeMoves(const char* roomfilename, const char* movesfilename, int n);


	// Player Coordinates
	int get_player_width();
	int get_player_height();

	// Other Coordinates
	int get_instance_width(std::string id);
	int get_instance_height(std::string id);

	// (X)(HT)ML
	bool loadFromXMLFile(const char* filename);
	bool loadMovesFromXMLFile(const char* filename);
	void saveToXMLFile (ostream& file);
	void saveMovesToXMLFile (ostream& file);
	void saveToHTMLFile (ostream& file);
	
	// File Outpot
	void writeToFile(const char* filename);
	void writeMovesToFile(const char* filename);

	// Delete Instances
	void deleteInstances();

	// Linked gates
	Instance* getLinkedGate(int width, int height);

	// Removing instances
	void removeInstance(Instance* instance);
};

void Room::print_dimensions() {
	std::cout << width << "x" << height << std::endl;
}

void Room::print_ascii(ostream& out) {
	// TOP DASHES
	out << std::string(2 * width + 1, '-') << std::endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (get_instance(j, height - 1 -i) == NULL) {
				out << "| ";
			}
			else {
				out << "|" << get_instance(j, height - 1 -i)->get_type();
			}
		}
		out << "|" << std::endl;
		out << std::string(2 * width + 1, '-') << std::endl;
	}
}

void Room::printRoom(ostream& out) {
	REQUIRE(is_initialized, "ERROR: Room was not yet initialized.");

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (get_instance(j, height - 1 -i) == NULL) {
				out << " ";
			}
			else {
				out << get_instance(j, height - 1 -i)->getSymbol();
			}
		}
		out << std::endl;
	}
}

void Room::init() {
	REQUIRE(!is_initialized, "ERROR: Room was already initialized.");
	REQUIRE(width > 0, "ERROR: Width is less than 0. Cannot initialize.");
	REQUIRE(height > 0, "ERROR: Height is less than 0. Cannot initialize.");

	if ((width > 0) && (height > 0)) {
		instances.resize(height, std::vector< Instance*>(width, NULL));
		is_initialized = true;
	}
	else
		std::cerr << "ERROR: height and width not correctly set. Could not initialize Room." << std::endl;

	ENSURE(is_initialized, "ERROR: Room could not be initialized.");
}

void Room::set_height(int h) {
	REQUIRE(!is_initialized, "ERROR: Room was already initialized. Cannot change dimensions after initializing the room.");
	
	height = h;

	ENSURE(this->get_height() == h, "ERROR: set_height() did not work correctly.");
}

int Room::get_height() {
	return height;
}

void Room::set_width(int w) {
	REQUIRE(!is_initialized, "ERROR: Room was already initialized. Cannot change dimensions after initializing the room.");

	width = w;

	ENSURE(this->get_width() == w, "ERROR: set_width() did not work correctly.");
}

int Room::get_width() {
	return width;
}

void Room::set_name(std::string str) {
	name = str;

	ENSURE(this->get_name() == str, "ERROR: set_name() did not work correctly.");
}

std::string Room::get_name() {
	return name;
}

bool Room::set_instance(int width, int height, int type) {
	REQUIRE(is_initialized, "ERROR: Could not set instance because Room was not properly initialized.");
	REQUIRE(type >= 0, "ERROR: Instance type should be at least 0. Please refer to the header files to see which value represents which instance.");
	REQUIRE(type <= 7, "ERROR: Instance type should be less than or equal 7. Please refer to the header files to see which value represents which instance.");
	REQUIRE(width >= 0, "ERROR: set_instance() coordinates out of bounds.");
	REQUIRE(height >= 0, "ERROR: set_instance() coordinates out of bounds.");
	REQUIRE(width < this->get_width(), "ERROR: set_instance() coordinates out of bounds.");
	REQUIRE(height < this->get_height(), "ERROR: set_instance() coordinates out of bounds.");

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

	ENSURE(this->get_instance(width, height) != NULL, "ERROR: set_instance did not work correctly.");
}

bool Room::set_instance(int width, int height, int type, std::string id) {
	REQUIRE(is_initialized, "ERROR: Could not set instance because Room was not properly initialized.");
	REQUIRE(type >= 0, "ERROR: Instance type should be at least 0. Please refer to the header files to see which value represents which instance.");
	REQUIRE(type < 8, "ERROR: Instance type should be less than 8. Please refer to the header files to see which value represents which instance.");
	REQUIRE(type != 1, "ERROR: Instance: Wall does not have an id. Please use set_instance(width, height, type).");
	REQUIRE(type != 2, "ERROR: Instance: Barrel does not have an id. Please use set_instance(width, height, type).");
	REQUIRE(type != 4, "ERROR: Instance: Water does not have an id. Please use set_instance(width, height, type).");
	REQUIRE(type != 7, "ERROR: Instance: Target does not have an id. Please use set_instance(width, height, type).");
	REQUIRE(width >= 0, "ERROR: set_instance() coordinates out of bounds.");
	REQUIRE(height >= 0, "ERROR: set_instance() coordinates out of bounds.");
	REQUIRE(width < this->get_width(), "ERROR: set_instance() coordinates out of bounds.");
	REQUIRE(width < this->get_height(), "ERROR: set_instance() coordinates out of bounds.");

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

	ENSURE(this->get_instance(width, height) != NULL, "ERROR: set_instance() did not work correctly.");
}

Instance* Room::get_instance(int width, int height) {
	REQUIRE(is_initialized, "ERROR: Could not get_instance() because Room was not properly initialized. Returning empty instance.");
	
	return instances[height][width];
}

void Room::set_instance_name(int width, int height, std::string str) {
	REQUIRE(is_initialized, "ERROR: Could not set_instance_name() because Room was not properly initialized.");
	
	get_instance(width, height)->set_name(str);

	ENSURE(this->get_instance(width, height)->get_name() == str, "ERROR: set_instance_name() did not work correctly.");
}

void Room::move_instance(int from_width, int from_height, int to_width, int to_height) {
	REQUIRE(is_initialized, "ERROR: Could not move_instance() because Room was not properly initialized.");
	
	instances[to_height][to_width] = instances[from_height][from_width];
	instances[from_height][from_width] = NULL;

	ENSURE(this->get_instance(from_width, from_height) == NULL, "ERROR: move_instance() did not work correctly.");
	ENSURE(this->get_instance(to_width, to_height) != NULL, "ERROR: move_instance() did not work correctly.");
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

int Room::get_instance_width(std::string id) {
	REQUIRE(is_initialized, "ERROR: Could not get_instance_width() because Room was not properly initialized.");
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (get_instance(j, i) == NULL)
				continue;
			if ((get_instance(j, i)->get_type() == 0) || (get_instance(j, i)->get_type() == 3))
				if (get_instance(j, i)->get_name() == id)
					return j;
		}
	}

	return 0;
}

int Room::get_instance_height(std::string id) {
	REQUIRE(is_initialized, "ERROR: Could not get_instance_height() because Room was not properly initialized.");
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (get_instance(j, i) == NULL)
				continue;
			if ((get_instance(j, i)->get_type() == 0) || (get_instance(j, i)->get_type() == 3))
				if (get_instance(j, i)->get_name() == id)
					return i;
		}
	}

	return 0;
}

bool Room::executeAttack(Move*& move, int offset_x, int offset_y) {
	REQUIRE(is_initialized, "ERROR: Could not execute move because Room was not properly initialized.");
	REQUIRE(move->isAttack, "ERROR: Tried to executeAttack on non-attack move.");

	int instance_x = this->get_instance_width(move->get_name());
	int instance_y = this->get_instance_height(move->get_name());

	// Destination is a monster
	if (get_instance(instance_x + offset_x, instance_y + offset_y)->get_type() == 3)
		instances[instance_y + offset_y][instance_x + offset_x] = NULL;
	return true;
}


bool Room::execute_move(Move*& move) {
	REQUIRE(is_initialized, "ERROR: Could not execute move because Room was not properly initialized.");
	REQUIRE(move->get_direction() >= 0, "ERROR: Move direction out of bounds.");
	REQUIRE(move->get_direction() < 4, "ERROR: Move direction out of bounds.");

	int instance_x = this->get_instance_width(move->get_name());
	int instance_y = this->get_instance_height(move->get_name());
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
	if ((instance_x + offset_x > width) || (instance_x + offset_x < 0) || (instance_y + offset_y > height) || (instance_y + offset_y < 0)) {
		std::cerr << "ERROR: Destination is out of bounds" << std::endl;
		return false;
	}

	if (move->isAttack)
		return this->executeAttack(move, offset_x, offset_y);
	
	// Destination is air
	if (get_instance(instance_x + offset_x, instance_y + offset_y) == NULL) {
		this->move_instance(instance_x, instance_y, instance_x + offset_x, instance_y + offset_y);
		return true;
	}

	// Destination is water
	if (get_instance(instance_x + offset_x, instance_y + offset_y)->get_type() == 4) {
		std::cerr << "GAME OVER: Destination contains water. You died!" << std::endl;
		return false;
	}

	// Destination is a button
	if (get_instance(instance_x + offset_x, instance_y + offset_y)->get_type() == 6) {
		this->removeInstance(getLinkedGate(instance_x + offset_x, instance_y + offset_y));
		this->move_instance(instance_x, instance_y, instance_x + offset_x, instance_y + offset_y);
		return true;
	}

	// Destination is the target
	if (get_instance(instance_x + offset_x, instance_y + offset_y)->get_type() == 7) {
		if (get_instance(instance_x, instance_y)->get_type() == 0) {
			std::cerr << "YOU WIN: You have reached the target. Good job!" << std::endl;
		}
		else {
			std::cerr << "YOU LOSE: A monster has reached the target before you did :(" << std::endl;
		}
		this->move_instance(instance_x, instance_y, instance_x + offset_x, instance_y + offset_y);
		return false;
	}

	// Destination is a non-movable instance
	if (! get_instance(instance_x + offset_x, instance_y + offset_y)->get_movable()) {
		// Wall
		if (get_instance(instance_x + offset_x, instance_y + offset_y)->get_type() == 1)
			std::cerr << "ERROR: Destination contains a non-movable instance. (WALL)" << std::endl;
		// Gate
		if (get_instance(instance_x + offset_x, instance_y + offset_y)->get_type() == 5)
			std::cerr << "ERROR: Destination contains a non-movable instance. (GATE)" << std::endl;
		// Player walks into monster
		if (get_instance(instance_x + offset_x, instance_y + offset_y)->get_type() == 3) {
			if (get_instance(instance_x, instance_y)->get_type() == 0)
				std::cerr << "YOU DIED: You walked right into a monster!" << std::endl;
		}
		// Monster walks into player
		if (get_instance(instance_x + offset_x, instance_y + offset_y)->get_type() == 0) {
			if (get_instance(instance_x, instance_y)->get_type() == 3)
				std::cerr << "YOU DIED: A monster ate you!" << std::endl;
		}
		return false;
	}
	
	// Destination is a moveable instance
	if (get_instance(instance_x + offset_x, instance_y + offset_y)->get_movable()) {
		std::cout << "pushing barrel" << std::endl;
		// Object behind destination is out of bounds -> moveable object gets pushed off the platform
		if ((instance_x + 2 * offset_x > width) || (instance_x + 2 * offset_x < 0) || (instance_y + 2 * offset_y > height) || (instance_y + 2 * offset_y < 0)) {
			this->move_instance(instance_x, instance_y, instance_x + offset_x, instance_y + offset_y);
			return true;
		}
		// Object behind destination is not air -> cannot move in that direction
		if (get_instance(instance_x + 2 * offset_x, instance_y + 2 * offset_y) != NULL) {
			std::cerr << "ERROR: Second non-air instance located behind moveable instance" << std::endl;
			return false;
		}
		// Object behind destination is air -> move both objects
		std:: cout << "Barrel can be pushed" << std::endl;
		this->move_instance(instance_x + offset_x, instance_y + offset_y, instance_x + 2 * offset_x, instance_y + 2 * offset_y);
		this->move_instance(instance_x, instance_y, instance_x + offset_x, instance_y + offset_y);
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
				file << "Er bevindt zich een knop (gelinkt aan poort " << get_instance(j, i)->get_name() << ") op positie (" << j << ", " << i << ").\n\n";
			}

			// Target
			if (get_instance(j, i)->get_type() == 7) {
				file << "Er bevindt zich een doel op positie (" << j << ", " << i << ").\n\n";
			}
		}
	}
	
	file.close();
}

void Room::saveToXMLFile (ostream& file) {
	REQUIRE(is_initialized, "ERROR: Could not write room properties to file because Room was not properly initialized.");

	file << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << endl;
	file << "<VELD>" << endl;
	file << "<NAAM>" << this->get_name() << "</NAAM>"<< endl;
	file << "<LENGTE>" << this->get_width() << "</LENGTE>"<< endl;
	file << "<BREEDTE>" << this->get_height() << "</BREEDTE>"<< endl;


	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (get_instance(j, height - 1 -i) == NULL)
				continue;

			if (get_instance(j, height - 1 -i)->get_type() == 0) {
				file << "    <SPELER x=\"" << j << "\" y=\"" << height - 1 -i << "\">"<< endl;
				file << "        <NAAM>" << get_instance(j, height - 1 -i)->get_name()  << "</NAAM>"<< endl;
				file << "    </SPELER>"<< endl;
			}

			if (get_instance(j, height - 1 -i)->get_type() == 1) {
				file << "    <MUUR beweegbaar=\"false\" x=\"" << j << "\" y=\"" << height - 1 -i << "\"/>"<< endl;
			}

			// Barrel
			if (get_instance(j, height - 1 -i)->get_type() == 2) {
				file << "    <TON beweegbaar=\"true\" x=\"" << j << "\" y=\"" << height - 1 -i << "\"/>"<< endl;
			}

			// Monster
			if (get_instance(j, height - 1 -i)->get_type() == 3) {
				file << "    <MONSTER x=\"" << j << "\" y=\"" << height - 1 -i << "\">"<< endl;
				file << "        <NAAM>" << get_instance(j, height - 1 -i)->get_name()  << "</NAAM>"<< endl;
				file << "    </MONSTER>"<< endl;
			}

			// Water
			if (get_instance(j, height - 1 -i)->get_type() == 4) {
				file << "    <WATER beweegbaar=\"false\" x=\"" << j << "\" y=\"" << height - 1 -i << "\"/>"<< endl;
			}

			// Gate
			if (get_instance(j, height - 1 -i)->get_type() == 5) {
				file << "    <POORT x=\"" << j << "\" y=\"" << height - 1 -i << "\">"<< endl;
				file << "        <NAAM>" << get_instance(j, height - 1 -i)->get_name()  << "</NAAM>"<< endl;
				file << "    </POORT>"<< endl;
			}

			// Button
			if (get_instance(j, height - 1 -i)->get_type() == 6) {
				file << "    <KNOP id=\"" << get_instance(j, height - 1 -i)->get_name() << "\" beweegbaar=\"false\" x=\"" << j << "\" y=\"" << i << "\"/>"<< endl;
			}

			// Target
			if (get_instance(j, height - 1 -i)->get_type() == 7) {
				file << "    <DOEL beweegbaar=\"false\" x=\"" << j << "\" y=\"" << height - 1 -i << "\"/>"<< endl;
			}
		}
	}

	file << "</VELD>" << endl;
}

void Room::saveMovesToXMLFile (ostream& file) {
	REQUIRE(is_initialized, "ERROR: Could not write room properties to file because Room was not properly initialized.");

	file << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << endl;

	file << "<BEWEGINGEN>" << endl;

	for (std::vector< Move*>::iterator it = moves.begin(); it != moves.end(); ++it) {
		Move* tempmove = *it;
		string directionstr;
	
		if (tempmove->get_direction() == 0) {
			directionstr = "RECHTS";
		}
		else if (tempmove->get_direction() == 1) {
			directionstr = "OMHOOG";
		}
		else if (tempmove->get_direction() == 2) {
			directionstr = "LINKS";
		}
		else if (tempmove->get_direction() == 3) {
			directionstr = "OMLAAG";
		}

		file << "    <BEWEGING>" << endl;
		file << "         <ID>" << tempmove->get_name() << "</ID>" << endl;
		file << "         <RICHTING>" << directionstr << "</RICHTING>" << endl;
		file << "    </BEWEGING>" << endl;
	}

	file << "</BEWEGINGEN>" << endl;
}

void Room::saveToHTMLFile (ostream& file) {
	file << "<html>\n\t<head>\n\t\t<title>Project Arcade</title>\n\t</head>\n\t<body>" << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (get_instance(j, height - 1 -i) == NULL) {
				file << "<img style=\"float:left;\" src=\"images/html/air.png\">" << endl;
				continue;
			}

			file << "<img style=\"float:left;\" src=\"images/html/type_" << get_instance(j, height - 1 -i)->get_type() << ".png\">" << endl;
		}
		file << "<br style=\"clear:both;\"/>\n";
	}

	file << "\t<audio style=\"visibility:hidden;\" src=\"sound/Le Epik Song.mp3\" autoplay loop>\t\n</body>\n</html>" << endl;
};

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

			if (tempmove->isAttack)
				file << tempmove->get_name() << " zal volgende aanval nog uitvoeren: \n" << directionstr << "\n\n";
			else
				file << tempmove->get_name() << " zal volgende beweging nog uitvoeren: \n" << directionstr << "\n\n";
		}
	}
	
	file.close();
}

void Room::executeMoves(const char* roomfilename, const char* movesfilename, int n) {
	REQUIRE(is_initialized, "ERROR: Could not execute any moves because Room was not initialized.");

	if (moves.size() <= n) {
		this->executeAllMoves(roomfilename, movesfilename);
	}
	else {
		while (n-- > 0) {
			if (this->execute_move(*moves.begin())) {
				moves.erase(moves.begin());
			}
			else {
				std::cerr << "ERROR: Could not execute move. Writing current room state and remaining moves to ascii file." << std::endl;
				break;
			}
		}
	}	
}

void Room::executeAllMoves(const char* roomfilename, const char* movesfilename) {
	REQUIRE(is_initialized, "ERROR: Could not execute any moves because Room was not initialized.");

	while (moves.size() != 0) {
		if (this->execute_move(*moves.begin())) {
			moves.erase(moves.begin());
		}
		else {
			std::cerr << "END OF GAME: Writing remaining moves and room state to .txt files." << std::endl;
			break;
		}
	}

	this->writeToFile(roomfilename);
	this->writeMovesToFile(movesfilename);
	
	return;
}

Instance* Room::getLinkedGate(int width, int height) {
	REQUIRE(is_initialized, "ERROR: Could not execute any moves because Room was not initialized.");
	REQUIRE(this->get_instance(width, height)->get_type() == 6, "ERROR: That instance is not a button.");	

	std::string buttonName = this->get_instance(width, height)->get_name();

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (get_instance(j, i) == NULL)
				continue;
			if (get_instance(j, i)->get_type() == 5) {
				if (get_instance(j, i)->get_name() == buttonName) {
					return get_instance(j, i);
				}
			}
		}
	}	
}

void Room::removeInstance(Instance* instance) {
	REQUIRE(is_initialized, "ERROR: Could not execute any moves because Room was not initialized.");
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (get_instance(j, i) == instance) {
				instances[i][j] = NULL;
				break;
			}
		}
	}
}

Room::~Room() {}