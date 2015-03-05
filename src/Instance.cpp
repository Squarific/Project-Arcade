class Instance {
  private:
	int type;
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
	Instance(int t) {
		type = t;
	}
	
	int get_type();
	void set_type(int t);
	std::string get_name();
	void set_name(std::string n);
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

void Instance::print_instance() {
	std::cout << "Instance: Type: " << type << std::endl;
}