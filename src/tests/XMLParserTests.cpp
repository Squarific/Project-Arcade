#include <vector>
#include <tuple>

TEST(xmlparsertests, normalInstance) {
	Room room;

	TiXmlDocument doc("xmlfiles/normalInstance.xml");
	doc.LoadFile();
	
	TiXmlElement* elem = doc.FirstChildElement()->FirstChildElement();
	vector <int> inst = room.parseInstance(elem);

	EXPECT_EQ(inst[0], 5);
	EXPECT_EQ(inst[1], 8);
	EXPECT_EQ(inst[2], 2);
}

TEST(xmlparsertests, instanceWithId) {
	Room room;

	TiXmlDocument doc("xmlfiles/instanceWithId.xml");
	doc.LoadFile();
	
	TiXmlElement* elem = doc.FirstChildElement()->FirstChildElement();
	tuple <int, int, int, string> inst = room.parseInstanceWithId(elem);

	EXPECT_EQ(get<0>(inst), 6);
	EXPECT_EQ(get<1>(inst), 7);
	EXPECT_EQ(get<2>(inst), 3);
	EXPECT_EQ(get<3>(inst), string("test_id"));
}