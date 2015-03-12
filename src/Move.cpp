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

	void set_direction(int d);
	int get_direction();
	
	void set_name(std::string str);
	std::string get_name();
};

void Move::set_direction(int d) {
	direction = d;
}

int Move::get_direction() {
	return direction;
}

void Move::set_name(std::string str) {
	name = str;
}

std::string Move::get_name() {
	return name;
}