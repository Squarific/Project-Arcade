#include <string>
#include <iostream>
#include "DesignByContract.h"

class Instance {
  protected:
	bool movable;
	std::string name;
	/**
	 *	The following ints are used to define which type the instance is:
	 *	0: Player
	 *	1: Wall
	 *	2: Barrel
	 *	3: Monster
	 *	4: Water
	 *	5: Gate
	 *	6: Button
	 *	7: Target
	 */
	bool properly_init = false;
	
  public:
  	int type;
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

	std::string getSymbol();
	
	void print_instance();
};

class Player: public Instance {
  public:
    Player() {
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
    Wall() {
      movable = false;
      type = 1;
      properly_init = true;
    }
    ~Wall();
};

class Barrel: public Instance {
  public:
    Barrel() {
      movable = true;
      type = 2;
      properly_init = true;
    }
    ~Barrel();
};

class Monster: public Instance {
  public:
    Monster() {
      movable = false;
      type = 3;
      properly_init = true;
    }
    Monster(std::string n) {
      movable = false;
      type = 3;
      properly_init = true;
      name = n;
    }
    ~Monster();
};

class Water: public Instance {
  public:
    Water() {
      movable = false;
      type = 4;
      properly_init = true;
    }
    ~Water();
};

class Gate: public Instance {
  public:
    Gate() {
		movable = false;
		type = 5;
		properly_init = true;
    }
    Gate(std::string n) {
		movable = false;
		type = 5;
		properly_init = true;
		name = n;
    }
    ~Gate();
};

class Button: public Instance {
  public:
    Button() {
      movable = false;
      type = 6;
      properly_init = true;
    }
    Button(std::string n) {
      movable = false;
      type = 6;
      properly_init = true;
      name = n;
    }
    ~Button();
};

class Target: public Instance {
  public:
    Target() {
      movable = false;
      type = 7;
      properly_init = true;
    }
    ~Target();
};

int Instance::get_type() {
	REQUIRE(properly_init, "ERROR: Instance was not properly initialized.");
	return type;
}

void Instance::set_type(int t) {
	REQUIRE(properly_init, "ERROR: Instance was not properly initialized.");
	
	type = t;

	ENSURE(this->get_type() == t, "ERROR: set_type() did not work correctly.");
}

std::string Instance::get_name() {
	REQUIRE(properly_init, "ERROR: Instance was not properly initialized.");
	
	return name;
}

std::string Instance::getSymbol() {
	REQUIRE(properly_init, "ERROR: Instance was not properly initialized.");
	REQUIRE(type >= 0, "ERROR: Instance type out of bounds.");
	REQUIRE(type < 8, "ERROR: Instance type out of bounds.");

	if (type == 0)
		return "Y";
	if (type == 1)
		return "#";
	if (type == 2)
		return "O";
	if (type == 3)
		return "&";
	if (type == 4)
		return "~";
	if (type == 5)
		return "=";
	if (type == 6)
		return ".";
	if (type == 7)
		return "X";
}

void Instance::set_name(std::string n) {
	REQUIRE(properly_init, "ERROR: Instance was not properly initialized.");
	
	name = n;

	ENSURE(this->get_name() == n, "ERROR: set_name() did not work correctly.");
}

bool Instance::get_movable() {
	REQUIRE(properly_init, "ERROR: Instance was not properly initialized.");
	
	return movable;
}

void Instance::set_movable(bool m) {
	REQUIRE(properly_init, "ERROR: Instance was not properly initialized.");
	
	movable = m;

	ENSURE(this->get_movable() == m, "ERROR: set_movable() did not work correctly.");
}

void Instance::print_instance() {
	std::cout << "INSTANCE: Type: " << type << std::endl;
}


/**
 * Destructors
 */ 

Instance::~Instance(){}

Player::~Player(){}

Wall::~Wall(){}

Barrel::~Barrel(){}

Monster::~Monster(){}

Water::~Water(){}

Gate::~Gate(){}

Button::~Button(){}

Target::~Target(){}