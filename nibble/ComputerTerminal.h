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
		void commandHelp(std::vector<std::string> args, std::vector<std::string> flags, bool override_checks);
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
                "-----------------------------------------",
                "(terminal) assemble command documentation",
                "-----------------------------------------",
                "INFO:",
                "    Uses the built in assembler _NAME_PENDING_ to convert",
                "    assembly code into machine code which can be run by the",
                "    Nibble microcomputer.",
                "",
                "    _NAME_PENDING_ provides some basic error checking to",
                "    ensure the argument time given for each op-code are",
                "    the expected type. If any errors are found when assembling",
                "    the errors will be printed to the terminal.",
                "",
                "USAGE:",
                "    build <in file>: Assembles the assembly code in <in file>",
                "        and outputs the assembled machine code to <in file>.bin",
                "    build <in file> <out_file>: Assembles the assembly code in",
                "        <in file> and outputs the assembled machine code to",
                "        <out file>",
                "",
                "PARAMETERS:",
                "    <in file>: file to load assembly code from",
                "    <out file> (opt): file to save the machine code to, default ",
                "        extension .nib",
                "",
                "FLAGS:",
                "    --no-warnings: suppresses all assembler warnings",
                "    --verbose: outputs info about assember steps"
            }},
            {"clc", {
                "clc:  clears the console window of all text"
            }}
		};	
};


#endif

