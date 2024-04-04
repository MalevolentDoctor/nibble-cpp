#include <format>

#include "ComputerTerminal.h"
#include "Computer.h"

NibbleComputerTerminal::NibbleComputerTerminal(NibbleComputer* _computer) {
	computer = _computer;

	setWindowPosition(24, 24);
	setWindowSize(computer->getScreenWidth() - 2*window.x, computer->getScreenHeight() - 2*window.y);
	
	setLinePrompt(">> ");

	//border = { 24, 24, 24, 24 };
	buffer = { 4, 4, 4, 4 };

	init();
}

void NibbleComputerTerminal::interpretCommand(std::string command, std::vector<std::string> args, std::vector<std::string> flags, bool override_checks) {
	if (command == "build") commandBuild();
	else if (command == "clc") commandClearTerminal();
	else if (command == "delete") commandDeleteFile();
	else if (command == "edit") commandOpenEditor();
	else if (command == "flash") commandFlashRom();
	else if (command == "help") commandHelp(args, flags, override_checks);
	else if (command == "list") commandListFiles();
	else if (command == "load") commandLoadFile();
	else if (command == "new") commandNewFile();
	else if (command == "ram") commandDisplayRam();
	else if (command == "rom") commandDisplayRom();
	else if (command == "save") commandSaveFile();
	else {
		printToTerminal("Error: No command \"" + command + "\" found.");
	}
}

void NibbleComputerTerminal::commandBuild() {
	
}
void NibbleComputerTerminal::commandClearTerminal() {
	text.clear();
	cursor.y = -1; // Will go to zero when added to
	screen_scroll = 0;
}

void NibbleComputerTerminal::commandDeleteFile() {

}
void NibbleComputerTerminal::commandOpenEditor() {
	nkeyboard->clearInputs(); // Don't execute anymore key presses
	computer->startApplication(COMPUTER_APP_EDITOR, { {"computer", computer} });
}
void NibbleComputerTerminal::commandFlashRom() {

}

void NibbleComputerTerminal::commandHelp(std::vector<std::string> args, std::vector<std::string> flags, bool override_checks) {
	if (args.size() == 0) {
		printToTerminal(help_text.at("help"));
	}
	else if (args.size() > 1) {
		printToTerminal("Error: Too many arguments");
	}
	else {
		std::string help_key = args.at(0);
		auto iterator = help_text.find(help_key);
		if (iterator != help_text.end()) {
			printf("%s\n", args.at(0).c_str());
			printToTerminal(help_text.at(args.at(0)));
		}
		else {
			printToTerminal(std::format("Error: No help document exists for the command \"{}\"", help_key));
		}
	}
}

void NibbleComputerTerminal::commandListFiles() {

}
void NibbleComputerTerminal::commandLoadFile() {

}
void NibbleComputerTerminal::commandNewFile() {

}
void NibbleComputerTerminal::commandDisplayRam() {

}
void NibbleComputerTerminal::commandDisplayRom() {

}
void NibbleComputerTerminal::commandSaveFile() {

}