#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)

#include <cstdio>

#include "raylib/raylib.h"

#pragma warning(pop)


#include "NibbleWorkbench.h"
#include "NibbleDesktop.h"


NibbleWorkbench::NibbleWorkbench(ProgramState* program_state) : program_state(program_state) {
	desktop = NibbleDesktop(program_state);
}

void NibbleWorkbench::input() {
	// Keyboard input

	// View Desktop
	if (IsKeyPressed(KEY_F1)) { workbench_page = WORKBENCH_PAGE_COMPUTER; }

	// Toggle between desktop viewing modes
	if (IsKeyPressed(KEY_F2)) { 
		if (desktop.getDesktopMode() == DESKTOP_MODE_INACTIVE) {
			desktop.setDesktopMode(DESKTOP_MODE_ACTIVE);
			desktop.setDesktopZoom(2.0f);

		}
		else if (desktop.getDesktopMode() == DESKTOP_MODE_ACTIVE) {
			desktop.setDesktopMode(DESKTOP_MODE_INACTIVE);
			desktop.setDesktopZoom(1.0f);
		}
	}

	// View microcomputer
	if (IsKeyPressed(KEY_F3)) { workbench_page = WORKBENCH_PAGE_MICROCOMPUTER; }

	// Mouse input
	// using the sides of the screen
}

void NibbleWorkbench::update(float dt) {
	if (workbench_page == WORKBENCH_PAGE_COMPUTER || workbench_page == WORKBENCH_PAGE_COMPUTER_IMMERSIVE) {
		// Interact with computer
	}

	if (workbench_page == WORKBENCH_PAGE_MICROCOMPUTER) {
		// Interact with microcomputer
	}
}

void NibbleWorkbench::draw() {

	if (workbench_page == WORKBENCH_PAGE_COMPUTER) {
		// Draw computer far
		desktop.draw();
	}

	if (workbench_page == WORKBENCH_PAGE_MICROCOMPUTER) {
		// Draw microcomputer
	}
}
