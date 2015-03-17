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
	
  public:
	Instance(){}
	Instance(int t, bool m) {
		type = t;
		movable = m;
	}
	
	// Get and set for the type
	int get_type();
	void set_type(int t);
	
	// Get and set for the name
	std::string get_name();
	void set_name(std::string n);
	
	// Get and set for moveable
	bool get_movable();
	void set_movable(bool m);
	
	// Prints basic information about the instance. To be used for testing purposes only.
	void print_instance();
};