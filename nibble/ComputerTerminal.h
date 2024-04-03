#ifndef NIBBLECOMPUTERTERMINAL_H
#define NIBBLECOMPUTERTERMINAL_H

#include "NibbleTerminal.h"

class NibbleComputer;

class NibbleComputerTerminal: public NibbleTerminal {
	public:
		NibbleComputerTerminal(NibbleComputer* _computer);

	protected:

		void interpretCommand(std::string command, std::vector<std::string> args, std::vector<std::string> flags) override;

		// Execute commands
		void commandBuild();
		void commandClearTerminal();
		void commandDeleteFile();
		void commandOpenEditor();
		void commandFlashRom();
		void commandHelp();
		void commandListFiles();
		void commandLoadFile();
		void commandNewFile();
		void commandDisplayRam();
		void commandDisplayRom();
		void commandSaveFile();

		NibbleComputer* computer;
};


#endif

