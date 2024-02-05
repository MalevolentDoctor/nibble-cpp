#ifndef NIBBLEWORKBENCH_H
#define NIBBLEWORKBENCH_H

#include "Helper.hpp"
#include "NibbleDesktop.h"

enum WorkbenchPages {
	WORKBENCH_PAGE_COMPUTER,
	WORKBENCH_PAGE_COMPUTER_IMMERSIVE,
	WORKBENCH_PAGE_MICROCOMPUTER
};

class NibbleWorkbench {
	public:
		NibbleWorkbench(ProgramState* program_state);

		void input();
		void update(float dt);
		void draw();

	private:
		int workbench_page = WORKBENCH_PAGE_COMPUTER;
		ProgramState* program_state;

		NibbleDesktop desktop;
};


#endif
