#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include "./TinyXML/tinyxml.h"

using namespace std;

map <string, int> instanceTypes = {{"MUUR", 1}, {"TON", 2}, {"WATER", 4}, {"DOEL", 7}};
map <string, int> instanceTypesWithId = {{"SPELER", 0}, {"MONSTER", 3}, {"POORT", 5}, {"KNOP", 6}};

bool Room::loadFromXMLFile (const char* filename) {
	// Create xml dom
	TiXmlDocument doc(filename);

	bool success = doc.LoadFile();

	REQUIRE(success, "File " + filename + " not found");

	// Get root element
	TiXmlElement* root = doc.FirstChildElement();

	REQUIRE(root != NULL, "XML Error: No root element");
	REQUIRE(string(root->Value()) == "VELD", "XML Error: Root element has to be called 'VELD' but was '" + root->Value() + "'");

	vector < vector <int>> instances;
	vector < tuple <int, int, int, string>> instancesWithId;
	
	// Parse all tags under the root
	for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
		string elemName = elem->Value();

		if (elemName == "NAAM" || elemName == "LENGTE" || elemName == "BREEDTE") this->parseRoomInfo(elem);
		if (instanceTypes.count(elemName) == 1) instances.push_back(this->parseInstance(elem));
		if (instanceTypesWithId.count(elemName) == 1) instancesWithId.push_back(this->parseInstanceWithId(elem));
	}

	// The room settings have been parsed, init room and add instances and players
	this->init();

	for (auto instance : instances) {
		this->set_instance(instance[0], instance[1], instance[2]);
	}

	for (auto instance : instancesWithId) {
		this->set_instance(get<0>(instance), get<1>(instance), get<2>(instance), get<3>(instance));
	}

	return true;
}

void Room::parseRoomInfo (TiXmlElement* elem) {
	// Get the text between the name, length and width tags
	TiXmlNode* node = elem->FirstChild();
	TiXmlText* text = node->ToText();

	string str = text->Value();
	string elemName = elem->Value();

	REQUIRE(elemName == "NAAM" || elemName == "LENGTE" || elemName == "BREEDTE", "PARSE ERROR: room info element has to be NAAM, LENGTE OR BREEDTE but was: " + elemName);
	
	if (elemName == "NAAM") {
		this->set_name(str);
	}
	
	if (elemName == "LENGTE") this->set_height(atoi(str.c_str()));
	if (elemName == "BREEDTE") this->set_width(atoi(str.c_str()));
}

vector <int> Room::parseInstance (TiXmlElement* elem) {
	string elemName = elem->Value();
	vector <int> instance;

	REQUIRE(instanceTypes.count(elemName) == 1, "PARSE ERROR: Invalid instance type. Type was: " + elemName);

	int x = 0;
	int y = 0;

	elem->Attribute("x", &x);
	elem->Attribute("y", &y);

	instance.push_back(x);
	instance.push_back(y);
	instance.push_back(instanceTypes[elemName]);

	return instance;
}

tuple <int, int, int, string> Room::parseInstanceWithId (TiXmlElement* elem) {
	string elemName = elem->Value();
	const char *id = elem->Attribute("id");
	TiXmlNode* node = elem->FirstChild();
	string name;

	REQUIRE(instanceTypesWithId.count(elemName) == 1, "PARSE ERROR: Invalid instance type. Type was: " + elemName);
	REQUIRE(id != NULL || node != NULL, "PARSE ERROR: No id in attribute or in tags for element " + elemName);

	if (id != NULL) {
		name = string(id);
	} else {
		node = node->FirstChild();
		TiXmlText* text = node->ToText();
		name = text->Value();
	}
	
	int x = 0;
	int y = 0;

	elem->Attribute("x", &x);
	elem->Attribute("y", &y);

	tuple <int, int, int, string> player (x, y, instanceTypesWithId[elemName], name);
	return player;
}

bool Room::loadMovesFromXMLFile(const char* filename) {
	// Create xml dom
	TiXmlDocument doc(filename);
	
	bool success = doc.LoadFile();
	REQUIRE(success, "File " + filename + " not found while trying to parse moves from xml file");

	// Get root element
	TiXmlElement* root = doc.FirstChildElement();

	REQUIRE(root != NULL, "XML Error: No root XML element!")
	REQUIRE(string(root->Value()) == "ACTIES" || string(root->Value()) == "BEWEGINGEN", "XML Error: Root element has to be called 'BEWEGINGEN' or 'ACTIES' but was '" + root->Value() + "'");

	// Parse the tags 'BEWEGING'
	for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
		string elemName = elem->Value();
		
		if (elemName == "BEWEGING" || elemName == "AANVAL") {
			TiXmlElement* playernameElem = elem->FirstChildElement();
			TiXmlElement* directionElem = playernameElem->NextSiblingElement();

			if (playernameElem == NULL || directionElem == NULL) {
				cerr << "XML Error: BEWEGING tags need to contain 2 tags, the first is a playername, the second a direction" << endl;
			}

			if (string(playernameElem->Value()) != "ID" || string(directionElem->Value()) != "RICHTING") {
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

			this->moves.push_back(new Move(directionint, playername, elemName == "AANVAL"));
		}
	}
	return true;
}