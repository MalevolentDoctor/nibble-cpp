#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib/raylib.h"

#pragma warning(pop)


#include "MainMenu.h"
#include "NibbleGUI.h"


MainMenu::MainMenu(ProgramState* program_state) : program_state(program_state) {
	gui = NibbleGUI();
}

void MainMenu::input() {

}

void MainMenu::update(float dt) {

}

void MainMenu::draw() {

	if (program_state->mode == PROGRAM_MODE_MAIN_MENU) {
		DrawText("This text is being drawn from the main menu", 190, 200, 20, LIGHTGRAY);
		Rectangle rec = { 100, 100, 200, 50};

		gui.btn_params.font = gui.gui_fonts.kong_text_16;
		gui.btn_params.font_spacing = 0;
		gui.Button(rec, "BUTTON");
	}

}