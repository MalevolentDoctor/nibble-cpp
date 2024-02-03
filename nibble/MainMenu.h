#pragma once

#include "Helper.hpp"
#include "NibbleGUI.h"

class MainMenu {
	public:
		MainMenu(ProgramState* program_state);

		void input();
		void update(float dt);
		void draw();
		

	private:
		ProgramState* program_state;
		NibbleGUI gui;
};

