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
	
	int get_type();
	void set_type(int t);
	
	std::string get_name();
	void set_name(std::string n);
	
	bool get_movable();
	void set_movable(bool m);
	
	void print_instance();
};

int Instance::get_type() {
	return type;
}

void Instance::set_type(int t) {
	type = t;
}

std::string Instance::get_name() {
	return name;
}

void Instance::set_name(std::string n) {
	name = n;
}

bool Instance::get_movable() {
	return movable;
}

void Instance::set_movable(bool m) {
	movable = m;
}

void Instance::print_instance() {
	std::cout << "INSTANCE: Type: " << type << std::endl;
}