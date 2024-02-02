#pragma once

#include "Helper.h"

class MainMenu {
	public:
		MainMenu(ProgramState* program_state);

		void input();
		void update(float dt);
		void draw();
		

	private:
		ProgramState* program_state;

};

