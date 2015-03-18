#include <string>
#include <iostream>

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
	if (properly_init)
		return type;
	else
		std::cerr << "ERROR: Instance was not properly initialized." << std::endl;
}

void Instance::set_type(int t) {
	if (properly_init)
		type = t;
	else
		std::cerr << "ERROR: Instance was not properly initialized." << std::endl;
}

std::string Instance::get_name() {
	if (properly_init)
		return name;
	else
		std::cerr << "ERROR: Instance was not properly initialized." << std::endl;
}

void Instance::set_name(std::string n) {
	if (properly_init)
		name = n;
	else
		std::cerr << "ERROR: Instance was not properly initialized." << std::endl;
}

bool Instance::get_movable() {
	if (properly_init)
		return movable;
	else
		std::cerr << "ERROR: Instance was not properly initialized." << std::endl;
}

void Instance::set_movable(bool m) {
	if (properly_init)
		movable = m;
	else
		std::cerr << "ERROR: Instance was not properly initialized." << std::endl;
}

void Instance::print_instance() {
	std::cout << "INSTANCE: Type: " << type << std::endl;
}