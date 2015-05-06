TEST(metafilecompare, samefile) {
	EXPECT_TRUE(FileCompare("filecompare/SpeelveldComplete.txt", "filecompare/SpeelveldComplete.txt"));
}

TEST(metafilecompare, equal) {
	EXPECT_TRUE(FileCompare("filecompare/SpeelveldComplete.txt", "filecompare/SpeelveldCompleteCopy.txt"));
}

TEST(metafilecompare, notEqual) {
	EXPECT_FALSE(FileCompare("filecompare/SpeelveldComplete.txt", "filecompare/SpeelveldCompleteCopyWrong.txt"));
}

TEST(metafilecompare, empty) {
	EXPECT_TRUE(FileCompare("filecompare/empty.txt", "filecompare/empty2.txt"));
}

TEST(metafilecompare, oneCharacterEqual) {
	EXPECT_TRUE(FileCompare("filecompare/oneCharA.txt", "filecompare/oneCharA2.txt"));
}

TEST (metafilecompare, oneCharacterNotEqual) {
	EXPECT_FALSE(FileCompare("filecompare/oneCharA.txt", "filecompare/oneCharB.txt"));
}