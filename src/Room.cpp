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
	bool loadFromXMLFile();
};

void Room::print_dimensions() {
	std::cout << width << "x" << height << std::endl;
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
	Room a_room(25,25);

	a_room.print_dimensions();
	
	return 0;
}