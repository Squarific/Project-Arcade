#include <string>
#include <iostream>
#include "DesignByContract.h"

class Instance {
  protected:
	int type;	 
	bool movable;
	std::string name;
	bool properly_init = false;
	
  public:
  	/**
  	 *	 Although these constructors can be used for 'custom' objects, it is not advised to use this.
  	 *	 You should only use the subclasses' constructors.
  	 */
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
	 *	0: Player
	 *	1: Wall
	 *	2: Barrel
	 *	3: Monster
	 *	4: Water
	 *	5: Gate
	 *	6: Button
	 *	7: Target
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
	 *	Returns the symbol used in the printRoom() function.
	 */
	std::string getSymbol();
	
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

	~Instance();
};


/**
 *	SUBCLASSES
 */

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

class Monster: public Instance {
  public:
  	Monster(){
  		movable = false;
  		type = 3;
  		properly_init = true;
  	}
  	~Monster();
};

class Water: public Instance {
  public:
  	Water(){
  		movable = false;
  		type = 4;
  		properly_init = true;
  	}
  	~Water();
};

class Gate: public Instance {
  public:
  	Gate(){
  		movable = false;
  		type = 5;
  		properly_init = true;
  	}
  	~Gate();
};

class Button: public Instance {
  public:
  	Button(){
  		movable = false;
  		type = 6;
  		properly_init = true;
  	}
  	~Button();
};

class Target: public Instance {
  public:
  	Target(){
  		movable = false;
  		type = 7;
  		properly_init = true;
  	}
  	~Target();
};