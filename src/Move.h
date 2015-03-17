#include <string>

class Move {
  private:
	std::string name;
	int direction;

  public:
	Move(){}
	Move(int d, std::string n) {
		direction = d;
		name = n;
	}

	/**
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
	 *	Get and set functions for the 'name' attribute.
	 *	The name attribute determines which player executes the move.
	 *	It must have the same name as the player instance.
	 */
	void set_name(std::string str);
	std::string get_name();
};