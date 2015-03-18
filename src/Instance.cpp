#include <string>
#include <iostream>
#include "DesignByContract.h"

class Instance {
  private:
	int type;
	bool movable;
	std::string name;
	/*
		The following ints are used to define which type the instance is:
		0: Empty
		1: Player
		2: Wall
		3: Barrel
	*/
	bool properly_init = false;
	
  public:
	Instance() {
		properly_init = true;
	}
	Instance(int t, bool m) {
		type = t;
		movable = m;
		properly_init = true;
	}
	
	int get_type();
	void set_type(int t);
	
	std::string get_name();
	void set_name(std::string n);
	
	bool get_movable();
	void set_movable(bool m);
	
	void print_instance();
};

int Instance::get_type() {
	REQUIRE(properly_init, "ERROR: Instance was not properly initialized.");
	
	return type;
}

void Instance::set_type(int t) {
	REQUIRE(properly_init, "ERROR: Instance was not properly initialized.");
	
	type = t;
}

std::string Instance::get_name() {
	REQUIRE(properly_init, "ERROR: Instance was not properly initialized.");
	
	return name;
}

void Instance::set_name(std::string n) {
	REQUIRE(properly_init, "ERROR: Instance was not properly initialized.");
	
	name = n;
}

bool Instance::get_movable() {
	REQUIRE(properly_init, "ERROR: Instance was not properly initialized.");
	
	return movable;
}

void Instance::set_movable(bool m) {
	REQUIRE(properly_init, "ERROR: Instance was not properly initialized.");
	
	movable = m;
}

void Instance::print_instance() {
	std::cout << "INSTANCE: Type: " << type << std::endl;
}