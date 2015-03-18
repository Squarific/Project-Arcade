#include <string>
#include <iostream>

class Instance {
  private:
	int type;	 
	bool movable;
	std::string name;
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
	
	/**
	 *	PRE CONDITIONS:
	 *		properly_init == true
	 *
	 *	Get and set functions for the 'type' attribute.
	 *	The following ints are used to define which type the instance is:
	 *	0: Empty
	 *	1: Player
	 *	2: Wall
	 *	3: Barrel
	 */
	int get_type();
	void set_type(int t);
	
	/**
	 *	PRE CONDITIONS:
	 *		properly_init == true
	 *
	 *	Get and set for the 'name' attribute.
	 *	This is currently only used for the player.
	 * 	Barrels, Walls, ... do not use a name.
	 */
	std::string get_name();
	void set_name(std::string n);
	
	/** 
	 *	PRE CONDITIONS:
	 *		properly_init == true
	 *
	 *	Get and set for the 'moveable' attribute.
	 *	Moveable objects are able to be pushed around by the player,
	 *	as long as there is an empty space in the specified direction.
	 *	This attribute is not used for Players and Empty cells, although it is set to 'false' by default.
	 */
	bool get_movable();
	void set_movable(bool m);
	
	/**
	 *	Prints basic information about the instance. To be used for testing purposes only.
	 */
	void print_instance();
};