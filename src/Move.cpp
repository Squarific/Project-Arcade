#include <string>
#include <iostream>

class Move {
  private:
	std::string name;
	int direction;
	/*
		Directions follow the goniometric circle:	
		0: Right
		1: Up
		2: Left
		3: Down
	*/
	bool properly_init = false;

  public:
	Move() {
		properly_init = true;
	}
	Move(int d, std::string n) {
		direction = d;
		name = n;
		properly_init = true;
	}
	
	void set_direction(int d);
	int get_direction();
	
	void set_name(std::string str);
	std::string get_name();
};

void Move::set_direction(int d) {
	if (properly_init)
		direction = d;
	else
		std::cerr << "ERROR: Move was not properly initialized." << std::endl;
}

int Move::get_direction() {
	if (properly_init)
		return direction;
	else
		std::cerr << "ERROR: Move was not properly initialized." << std::endl;
}

void Move::set_name(std::string str) {
	if (properly_init)
		name = str;
	else
		std::cerr << "ERROR: Move was not properly initialized." << std::endl;
}

std::string Move::get_name() {
	if (properly_init)
		return name;
	else
		std::cerr << "ERROR: Move was not properly initialized." << std::endl;
}