#include <iostream>
#include "./TinyXML/tinyxml.h"

using namespace std;

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
			if (elemName == "BREEDTE") {
				// After we set width we have to init the room
				this->set_width(stoi(str));
				this->init();
			}
		}

		if (elemName == "OBSTAKEL") {
			TiXmlNode* node = elem->FirstChild()->FirstChild();
			TiXmlText* text = node->ToText();
			string str = text->Value();

			int type = 0;
			if (str == "muur") {
				type = 2;
			} else if (str == "ton") {
				type = 3;
			} else {
				cout << "Ignoring unknown type " << str << "." << endl;
			}

			bool moveable;
			string moveableString = elem->Attribute("beweegbaar");
			if (mobeableString == "true") {
				moveable = true;
			} else {
				moveable = false;
			}

			int x = 0;
			int y = 0;

			elem->Attribute("x", &x);
			elem->Attribute("y", &y);

			cout << x << y << endl;

			this->set_instance(x, y, type, moveable);
		}

		if (elemName == "SPELER") {
			TiXmlNode* node = elem->FirstChild()->FirstChild();
			TiXmlText* text = node->ToText();
			string name = text->Value();

			int x = 0;
			int y = 0;

			elem->Attribute("x", &x);
			elem->Attribute("y", &y);

			cout << x << y << endl;

			this->set_instance_name(x, y, name);
		}
	}

	return true;
}