#pragma once

#include "Helper.hpp"
#include "GUI.h"

class MainMenu {
	public:
		MainMenu(ProgramState* program_state);

		void input();
		void update(float dt);
		void draw();
		

	private:
		ProgramState* program_state;
		NibbleGUI gui;

		Font title_font;
		const char* title_text = "NIBBLE";
};

