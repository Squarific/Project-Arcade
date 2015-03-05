#import <iostream>

class Room {
  private:
	const int width;
	const int height;
  public:
	
	Room(){}
	Room(int w, int h) {
		width = w;
		height = h;
	}
	
	void print_dimensions();
};

void Room::print_dimensions() {
	std::cout << width << "x" << height << std::endl;
}

int main() {
	Room a_room(25,25);

	a_room.print_dimensions();
	
	return 0;
}