#pragma once

#include "Helper.hpp"

class MainMenu {
	public:
		MainMenu(ProgramState* program_state);

		void input();
		void update(float dt);
		void draw();
		

	private:
		ProgramState* program_state;

};

