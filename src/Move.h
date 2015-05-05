#include <string>
#include "DesignByContract.h"

class Move {
  private:
	std::string name;
	int direction;
	Move* _initcheck;

  public:
  	bool isAttack;
	Move();
	Move(int d, std::string n, bool a);

	/*
	 * Returns true if initialized using one of the constructors above
	 */

	bool properlyInitialized ();

	/**
	 *	PRE CONDITIONS:
	 *		REQUIRE(this->properlyInitialized()):
	 *
	 *	Get and set functions for the 'direction' attribute.
	 *	The integers representing the directions follow the goniometric circle:	
	 *	0: Right
	 *	1: Up
	 *	2: Left
	 *	3: Down
	 */
	void set_direction(int d);
	int get_direction();
	
	/**
	 *	PRE CONDITIONS:
	 *		REQUIRE(this->properlyInitialized()):
	 *
	 *	Get and set functions for the 'name' attribute.
	 *	The name attribute determines which player executes the move.
	 *	It must have the same name as the player instance.
	 */
	void set_name(std::string str);
	std::string get_name();
};