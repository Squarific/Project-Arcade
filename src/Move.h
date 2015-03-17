#include <string>

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
  public:
	Move(){}
	Move(int d, std::string n) {
		direction = d;
		name = n;
	}

	// Get and set for direction
	void set_direction(int d);
	int get_direction();
	
	// Get and set for name
	void set_name(std::string str);
	std::string get_name();
};