TEST(userinterfacetest, printHelp) {
	UserInterface ui;

	std::ofstream file;
	file.open("printhelp_temp_file.txt");

	ui.printHelp(file);

	FileCompare("printhelp_expected.txt", "printhelp_temp_file.txt");
}