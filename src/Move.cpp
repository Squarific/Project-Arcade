#include <string>
#include <iostream>
#include "DesignByContract.h"

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
	REQUIRE(properly_init, "ERROR: Move was not properly initialized.");
	
	direction = d;
}

int Move::get_direction() {
	REQUIRE(properly_init, "ERROR: Move was not properly initialized.");
	
	return direction;
}

void Move::set_name(std::string str) {
	REQUIRE(properly_init, "ERROR: Move was not properly initialized.");
	
	name = str;
}

std::string Move::get_name() {
	REQUIRE(properly_init, "ERROR: Move was not properly initialized.");
	
	return name;
}