#include <iostream>
#include <vector>
#include "Instance.cpp"

class Room {
  private:
	std::string name;
	int width;
	int height;
	std::vector< std::vector< Instance > > instances;
	bool is_initialized;
  public:
	
	Room() {
		width = 0;
		height = 0;
		is_initialized = false;
	}
	
	Room(int w, int h, std::string n) {
		width = w;
		height = h;
		name = n;
	}
	
	void print_dimensions();
	void print_instances();
	
	void init();
	
	void set_height(int h);
	int get_height();
	void set_width(int w);
	int get_width();
	void set_name(std::string str);
	std::string get_name();

	bool loadFromXMLFile(const char* filename);
};

void Room::print_dimensions() {
	std::cout << width << "x" << height << std::endl;
}

void Room::print_instances() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::cout << "at position: " << j << "," << i << std::endl;
			instances[i][j].print_instance();
		}
	}
}

void Room::init() {
	if ((width > 0) && (height > 0))
		instances.resize(height, std::vector< Instance >(width, Instance(0)));
	else
		std::cout << "ERROR: Height and width not correctly set." << std::endl;
}

void Room::set_height(int h) {
	height = h;
}

int Room::get_height() {
	return height;
}

void Room::set_width(int w) {
	width = w;
}

int Room::get_width() {
	return width;
}

void Room::set_name(std::string str) {
	name = str;
}

std::string Room::get_name() {
	return name;
}

bool Room::loadFromXMLFile (const char* filename) {
	// Create xml dom
	TiXmlDocument doc(filename);
	
	// Load the document
	if (!doc.LoadFile()) {
		cerr << "File " << filename << " not found" << endl;
		return false;
	}

	// Get root element
	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL) {
		cerr << "XML Error: No root element" << endl;
		return false;
	}

	// Root element should be 'veld'
	if (root->Value() !== "VELD") {
		cerr << "XML Error: Root element has to be called 'veld'" << endl;
		return false;
	}
	
	// Parse the tags 'NAAM', 'LENGTE', 'BREEDTE', 'SPELER', 'OBSTAKEL'
	for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
		string elemName = elem->Value();
		
		if (elemName == "NAAM" || elemName == "LENGTE" || elemName == "BREEDTE") {
			// Get the text between the name, length and width tags
			TiXmlNode* node = elem->FirstChild();
			TiXmlText* text = node->ToText();
			string str = text->Value();
			
			if (elemName == "NAAM") this->set_name(str);
			if (elemName == "LENGTE") this->set_length(stoi(str));
			if (elemName == "BREEDTE") this->set_width(stoi(str));
		}

		if (elemName == "OBSTAKEL") {

		}

		if (elemName == "SPELER") {
			
		}
	}

	return true;
}

int main() {
	Room a_room;
	
	a_room.set_height(5);
	a_room.set_width(3);

	a_room.init();
	
	a_room.print_dimensions();
	a_room.print_instances();
	
	return 0;
}