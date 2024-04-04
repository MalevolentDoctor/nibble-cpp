#ifndef NIBBLECOMPUTERTERMINAL_H
#define NIBBLECOMPUTERTERMINAL_H

#include <map>

#include "Terminal.h"

class NibbleComputer;

class NibbleComputerTerminal: public NibbleTerminal {
	public:
		NibbleComputerTerminal(NibbleComputer* _computer);

	protected:

		void interpretCommand(std::string command, std::vector<std::string> args, std::vector<std::string> flags, bool override_checks) override;

	private:
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

		const std::map<std::string, std::vector<std::string>> help_text = {
			{"help", {
				"assemble  assembles assembly code to Nibble-8 machine code",
				"clc  clears the console"
			}},
			{"assemble", {
				"assemble:  assembles current code opened in editor or loaded",
				"    into the console, or loaded in from a file provided as",
				"    an optional parameter",
				"",
				"build <out file>:  assembles the code currently loaded in",
				"    the editor or console, and outputs the machine code to",
				"        <out file>",
				"build <in file, out file>:  assembles the code from",
				"    <in file> and outputs the machine code to <out file>",
				"",
				"Parameters:",
				"    <out file> file to save the machine code to, default ",
				"        extension .nib",
				"    <in file>  (optional) file to load assembly code from"
			}},
			{"clc", {
				"clc:  clears the console window of all text"
			}}
		};	
};


#endif

