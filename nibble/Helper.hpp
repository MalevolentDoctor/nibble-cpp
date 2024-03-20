#ifndef HELPER_HPP
#define HELPER_HPP

#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)

#include<string>
#include<vector>

#pragma warning(pop)


enum ProgramStates {
	PROGRAM_STATE_SHOULD_CLOSE,
	PROGRAM_STATE_STARTING,
	PROGRAM_STATE_RUNNING
};

enum ProgramModes {
	PROGRAM_MODE_MAIN_MENU,		// On launch
	PROGRAM_MODE_WORKBENCH	// On press start
};

enum DesktopMode {
	DESKTOP_MODE_ACTIVE,
	DESKTOP_MODE_INACTIVE
};

enum ComputerMode {
	COMPUTER_MODE_ACTIVE,
	COMPUTER_MODE_INACTIVE
};

struct ProgramState {
	int state = PROGRAM_STATE_STARTING;	// State of the program, running, suspended etc.
	int mode = PROGRAM_MODE_MAIN_MENU;	// Mode of the program, what is it currently doing.
};

struct Cursor {
	int x;
	int y;
	int w;
	int h;
};

static std::vector<std::string> stringSplit(std::string string, std::string delimeter) {
	std::vector<std::string> split_string;
	size_t pos = 0;

	while ((pos = string.find(delimeter)) != std::string::npos) {
		split_string.push_back(string.substr(0, pos));
		string.erase(0, pos + delimeter.length());
	}

	// If there are no more spaces, return append the rest of the string
	split_string.push_back(string);

	return split_string;
}

#endif