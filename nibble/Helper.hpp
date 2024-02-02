#pragma once


enum ProgramStates {
	PROGRAM_STATE_SHOULD_CLOSE,
	PROGRAM_STATE_STARTING,
	PROGRAM_STATE_RUNNING
};

enum ProgramModes {
	PROGRAM_MODE_MAIN_MENU
};


struct ProgramState {
	int state = PROGRAM_STATE_STARTING;	// State of the program, running, suspended etc.
	int mode = PROGRAM_MODE_MAIN_MENU;	// Mode of the program, what is it currently doing.
};