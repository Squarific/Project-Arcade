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

	// Root element should be 'VELD'
	if (string(root->Value()) != "VELD") {
		cerr << "XML Error: Root element has to be called 'VELD' but was '" << root->Value() << "'" << endl;
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
			if (elemName == "LENGTE") this->set_height(atoi(str.c_str()));
			if (elemName == "BREEDTE") {
				// After we set width we have to init the room
				this->set_width(atoi(str.c_str()));
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
				cerr << "Ignoring unknown type " << str << "." << endl;
			}

			bool movable;
			string movableString = elem->Attribute("beweegbaar");
			if (movableString == "true") {
				movable = true;
			} else {
				movable = false;
			}

			int x = 0;
			int y = 0;

			elem->Attribute("x", &x);
			elem->Attribute("y", &y);

			this->set_instance(x, y, type, movable);
		}

		if (elemName == "SPELER") {
			TiXmlNode* node = elem->FirstChild()->FirstChild();
			TiXmlText* text = node->ToText();
			string name = text->Value();

			int x = 0;
			int y = 0;

			elem->Attribute("x", &x);
			elem->Attribute("y", &y);

			this->set_instance(x, y, 1, false);
			this->set_instance_name(x, y, name);
		}
	}

	return true;
}

bool Room::loadMovesFromXMLFile(const char* filename) {
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

	// Root element should be 'VELD'
	if (string(root->Value()) != "BEWEGINGEN") {
		cerr << "XML Error: Root element has to be called 'BEWEGINGEN' but was '" << root->Value() << "'" << endl;
		return false;
	}

	// Parse the tags 'BEWEGING'
	for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
		string elemName = elem->Value();
		
		if (elemName == "BEWEGING") {
			TiXmlElement* playernameElem = elem->FirstChildElement();
			TiXmlElement* directionElem = playernameElem->NextSiblingElement();

			if (playernameElem == NULL || directionElem == NULL) {
				cerr << "XML Error: BEWEGING tags need to contain 2 tags, the first is a playername, the second a direction" << endl;
			}

			if (string(playernameElem->Value()) != "SPELERNAAM" || string(directionElem->Value()) != "RICHTING") {
				cerr << "XML Error: BEWEGING needs to contain a tag SPELERNAAM and a tag RICHTING but contained '" << playernameElem->Value() << "' and '" << directionElem->Value() << "'" << endl;
			}

			TiXmlNode* playernameNode = playernameElem->FirstChild();
			TiXmlNode* directionNode = directionElem->FirstChild();

			TiXmlText* playernameText = playernameNode->ToText();
			TiXmlText* directionText = directionNode->ToText();

			string playername = playernameText->Value();
			string direction = directionText->Value();

			int directionint;
			if (direction == "OMHOOG") {
				directionint = 1;
			} else if (direction == "OMLAAG") {
				directionint = 3;
			} else if (direction == "LINKS") {
				directionint = 2;
			} else if (direction == "RECHTS") {
				directionint = 0;
			} else {
				cerr << "XML ERROR: Move had wrong type, accepted: LINKS OMHOOG RECHTS OMLAAG" << endl;	
				continue;
			}

			this->moves.push_back(new Move(directionint, playername));
		}
	}
	return true;
}