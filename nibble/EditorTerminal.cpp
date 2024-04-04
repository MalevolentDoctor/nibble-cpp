#include "EditorTerminal.h"
#include "Editor.h"

NibbleEditorTerminal::NibbleEditorTerminal(NibbleEditor* _editor, float size) {
	editor = _editor;

	setWindowPosition(24, 24 + (int)((1.0f - size) * (editor->computer->getScreenHeight() - 48)));
	setWindowSize(editor->computer->getScreenWidth() - 48, (int)(size * (editor->computer->getScreenHeight() - 48)));

	setLinePrompt(">> ");

	buffer = { 4, 4, 4, 4 };

	init();
}

void NibbleEditorTerminal::interpretCommand(std::string command, std::vector<std::string> args, std::vector<std::string> flags, bool override_checks) {
	if (command == "clc") commandClearTerminal();
	else {
		printToTerminal("Error: No command \"" + command + "\" found.");
	}
}

void NibbleEditorTerminal::commandClearTerminal() {
	text.clear();
	cursor.y = -1; // Will go to zero when added to
	screen_scroll = 0;
}