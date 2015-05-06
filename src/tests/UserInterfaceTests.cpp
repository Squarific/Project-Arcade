TEST(userinterfacetest, printHelp) {
	UserInterface ui;

	std::ofstream file;
	file.open("filecompare/printhelp_temp_file.txt");

	ui.printHelp(file);

	file.close();

	EXPECT_TRUE(FileCompare("filecompare/printhelp_expected.txt", "filecompare/printhelp_temp_file.txt"));
}

TEST(userinterfacetest, printHelpWrong) {
	UserInterface ui;

	std::ofstream file;
	file.open("filecompare/printhelp_temp_file.txt");

	ui.printHelp(file);

	file.close();

	EXPECT_FALSE(FileCompare("filecompare/printhelp_unexpected.txt", "filecompare/printhelp_temp_file.txt"));
}