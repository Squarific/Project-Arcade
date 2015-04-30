#include <string>
#include <iostream>
#include "DesignByContract.h"

class Instance {
  protected:
	int type;
	bool movable;
	std::string name;
	/*
		The following ints are used to define which type the instance is:
		0: Player
		1: Wall
		2: Barrel
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
	~Instance();
	
	int get_type();
	void set_type(int t);
	
	std::string get_name();
	void set_name(std::string n);
	
	bool get_movable();
	void set_movable(bool m);
	
	void print_instance();
};

class Player: public Instance {
  public:
  	Player(){
  		movable = false;
  		type = 0;
  		properly_init = true;
  	}
  	Player(std::string n) {
  		movable = false;
  		type = 0;
  		properly_init = true;
  		name = n;
  	}
  	~Player();
};

class Wall: public Instance {
  public:
  	Wall(){
  		movable = false;
  		type = 1;
  		properly_init = true;
  	}
  	~Wall();
};

class Barrel: public Instance {
  public:
  	Barrel(){
  		movable = true;
  		type = 2;
  		properly_init = true;
  	}
  	~Barrel();
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

Instance::~Instance(){}

Player::~Player(){}

Wall::~Wall(){}

Barrel::~Barrel(){}