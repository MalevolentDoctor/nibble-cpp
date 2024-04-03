#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)

#include <cstdio>

#include "raylib/raylib.h"

#pragma warning(pop)


#include "NibbleWorkbench.h"
#include "NibbleComputer.h"


NibbleWorkbench::NibbleWorkbench(ProgramState* program_state) : program_state(program_state) {
	computer = new NibbleComputer(program_state);
}

void NibbleWorkbench::input() {
	// Keyboard input

	// View Desktop
	if (IsKeyPressed(KEY_F1)) { workbench_page = WORKBENCH_PAGE_COMPUTER; }

	// Toggle between desktop viewing modes
	if (IsKeyPressed(KEY_F2)) { 
		if (computer->getComputerMode() == DESKTOP_MODE_INACTIVE) {
			computer->setComputerMode(DESKTOP_MODE_ACTIVE);
			computer->setComputerZoom(2.0f);

		}
		else if (computer->getComputerMode() == DESKTOP_MODE_ACTIVE) {
			computer->setComputerMode(DESKTOP_MODE_INACTIVE);
			computer->setComputerZoom(1.0f);
		}
	}

	// View microcomputer
	if (IsKeyPressed(KEY_F3)) { workbench_page = WORKBENCH_PAGE_MICROCOMPUTER; }

	if (workbench_page == WORKBENCH_PAGE_COMPUTER) {
		computer->input();
	}

	// Mouse input
	// using the sides of the screen
}

void NibbleWorkbench::update(float dt) {
	if (workbench_page == WORKBENCH_PAGE_COMPUTER) {
		computer->update();
	}

	if (workbench_page == WORKBENCH_PAGE_MICROCOMPUTER) {
		// Interact with microcomputer
	}
}

void NibbleWorkbench::draw() {

	if (workbench_page == WORKBENCH_PAGE_COMPUTER) {
		// Draw computer far
		computer->draw();
	}

	if (workbench_page == WORKBENCH_PAGE_MICROCOMPUTER) {
		// Draw microcomputer
	}
}
