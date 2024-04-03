#include "NibbleComputerTerminal.h"
#include "NibbleComputer.h"

NibbleComputerTerminal::NibbleComputerTerminal(NibbleComputer* _computer) {
	computer = _computer;

	setWindowRes(computer->getScreenWidth(), computer->getScreenHeight());
	setLinePrompt(">> ");

	border = { 24, 24, 24, 24 };
	buffer = { 4, 4, 4, 4 };

	init();
}

void NibbleComputerTerminal::interpretCommand(std::string command, std::vector<std::string> args, std::vector<std::string> flags) {
	if (command == "build") commandBuild();
	else if (command == "clc") commandClearTerminal();
	else if (command == "delete") commandDeleteFile();
	else if (command == "edit") commandOpenEditor();
	else if (command == "flash") commandFlashRom();
	else if (command == "help") commandHelp();
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
	computer->startApplication(COMPUTER_APP_EDITOR, { {"computer", computer} });
}
void NibbleComputerTerminal::commandFlashRom() {

}
void NibbleComputerTerminal::commandHelp() {

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