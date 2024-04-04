#ifndef NIBBLEEDITORTERMINAL_H
#define NIBBLEEDITORTERMINAL_H

#include "Terminal.h"

class NibbleEditor;

class NibbleEditorTerminal: public NibbleTerminal {
	public:
		NibbleEditorTerminal(NibbleEditor* _editor, float size);

	protected:

		void interpretCommand(std::string command, std::vector<std::string> args, std::vector<std::string> flags) override;

		void commandClearTerminal();

		NibbleEditor* editor;
};

#endif

