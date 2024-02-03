#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)

#include <cstdio>

#include "raylib/raylib.h"

#pragma warning(pop)


#include "NibbleWorkbench.h"


NibbleWorkbench::NibbleWorkbench(ProgramState* program_state) : program_state(program_state) {

}

void NibbleWorkbench::input() {
	// Keyboard input
	if (IsKeyPressed(KEY_F1)) { workbench_page = WORKBENCH_PAGE_COMPUTER; }
	if (IsKeyPressed(KEY_F2)) { workbench_page = WORKBENCH_PAGE_COMPUTER_IMMERSIVE; }
	if (IsKeyPressed(KEY_F2)) { workbench_page = WORKBENCH_PAGE_MICROCOMPUTER; }

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
	}

	if (workbench_page == WORKBENCH_PAGE_COMPUTER_IMMERSIVE) {
		// Draw computer close

	}

	if (workbench_page == WORKBENCH_PAGE_MICROCOMPUTER) {
		// Draw microcomputer
	}
}
