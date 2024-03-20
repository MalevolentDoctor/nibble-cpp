#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)

#include<vector>
#include<string>
#include<map>
#include<algorithm>

// for some debugging
#include<cstdio> 
#include<iostream>

#pragma warning(pop)

#include "Helper.hpp"
#include "NibbleTerminal.h"
#include "NibbleComputer.h"
#include "NibbleGUI.h"

NibbleTerminal::NibbleTerminal(NibbleComputer* _computer) {
	computer = _computer;

	ngui = NibbleGUI();
	nkeyboard = NibbleKeyboard();

	ngui.setGUIFont(ngui.fonts.pixel_mono_8, 0.0f);

	pre_line = ">> ";
	pre_line_offset = pre_line.length();

	text.push_back(pre_line);
	cursor.x = pre_line_offset;

	font = ngui.getFont();
	font_size = MeasureTextEx(font, "M", font.baseSize, 0.0f);

	screen_border = { 24.0f, 24.0f, 24.0f, 24.0f };
	screen_buffer = { 4.0f, 4.0f, 4.0f, 4.0f };

	screen_text_height = (int)((computer->getScreenHeight() - (screen_border.y + screen_buffer.y + screen_border.height + screen_buffer.height)) / (font_size.y + vspacing)) + 1;
	screen_text_width = (int)((computer->getScreenWidth() - (screen_border.x + screen_buffer.x + screen_border.width + screen_buffer.width)) / (font_size.x + ngui.getFontSpacing()));

	printf("Terminal 0x%p initialised from computer 0x%p\n", this, computer);
}

void NibbleTerminal::input() {
	nkeyboard.update(GetFrameTime());

	int keycode = 0;

	while ((keycode = nkeyboard.getKeyPressed())) {
		// Writable characters
		if (keycode >= 32 && keycode <= 126) {
			std::string string = nkeyboard.getStringFromKeycode(keycode, true);
			if (string != "") {
				text.at(cursor.y).append(string);
				cursor.x++;
			}

		}
		// Action characters
		else {
			// Navigation keys
			if (keycode == KEY_LEFT) moveCursorLeft(1); 
			if (keycode == KEY_RIGHT) moveCursorRight(1); 

			// Edit keys
			if (keycode == KEY_BACKSPACE) keyBackspace();
			if (keycode == KEY_DELETE) keyDelete();
			if (keycode == KEY_ENTER) keyEnter();
			if (keycode == KEY_UP) keyUp();
			if (keycode == KEY_DOWN) keyDown();
		}
	}
}

void NibbleTerminal::update() {
}

void NibbleTerminal::draw() {
	// Draw backgound
	DrawRectangle(0, 0, computer->getScreenWidth(), computer->getScreenHeight(), GRAY);






	DrawRectangle(
		screen_border.x,
		screen_border.y,
		computer->getScreenWidth() - screen_border.width - screen_border.x,
		computer->getScreenHeight() - screen_border.height - screen_border.y,
		LIGHTGRAY
	);

	// Draw cursor
	if (cursor.y < (screen_scroll + screen_text_height)) {
		DrawRectangle(
			screen_border.x + screen_buffer.x + cursor.x * font_size.x,
			screen_border.y + screen_buffer.y + (cursor.y - screen_scroll) * (font_size.y + vspacing) - 1,
			6, 10, YELLOW
		);
	}

	// Draw text to screen
	int rows_to_draw = std::min(screen_text_height, (int)text.size() - screen_scroll);
	for (int i = 0; i < rows_to_draw; i++) {
		ngui.drawText(
			text.at(i + screen_scroll),
			screen_border.x + screen_buffer.x,
			screen_border.y + screen_buffer.y + (font_size.y + vspacing) * i,
			BLACK
		);
	}
}

void NibbleTerminal::keyEnter() {
	// Add command to the command buffer
	if (text.at(cursor.y) != "") {
		if (command_buffer.size() == 0) {
			command_buffer.push_back(text.at(cursor.y));
		}
		else if (command_buffer.back() != text.at(cursor.y)) {
			command_buffer.push_back(text.at(cursor.y));
		}
	}

	// Extract command
	bool override_checks = false;
	std::string input = text.at(cursor.y).substr(pre_line_offset, text.at(cursor.y).size() - pre_line_offset);
	std::vector<std::string> split_input = stringSplit(input, " ");
	std::string command = getCommand(split_input);
	if (command.substr(0, 1) == "!") override_checks = true;
	std::vector<std::string> args = getArguments(split_input);
	std::vector<std::string> flags = getFlags(split_input);

	// Try to execute command
	if (command == "build") commandBuild();
	else if (command == "clc") commandClearTerminal();
	else if (command == "delete") commandDeleteFile();
	else if (command == "edit") commandOpenEditor();
	else if (command == "flash") commandFlashRom();
	else if (command == "help") commandHelp();
	else if (command == "list") commandListFiles();
	else if (command == "load") commandLoadFile();
	else if (command == "new") commandNewFile();
	else if (command == "ram") commandDisplayRam();
	else if (command == "rom") commandDisplayRom();
	else if (command == "save") commandSaveFile();
	else {
		printToTerminal("Error: No command \"" + command + "\" found.");
	}

	// Create new line
	text.push_back(pre_line);
	cursor.y++;
	cursor.x = pre_line_offset;

	// Update scroll position
	scrollToCursor();
}

void NibbleTerminal::keyBackspace() {
	if (cursor.x > pre_line_offset) {
		text.at(cursor.y).erase((size_t)(cursor.x - 1), 1);
		cursor.x--;
	}
}

void NibbleTerminal::keyDelete() {
	if (cursor.x < text.at(cursor.y).length()) {
		text.at(cursor.y).erase(cursor.x, 1);
	}
}

void NibbleTerminal::keyUp() {
	// If control is down scroll the terminal
	if (IsKeyDown(KEY_RIGHT_CONTROL) || IsKeyDown(KEY_LEFT_CONTROL)) {
		if (screen_scroll > 0) screen_scroll--;
	}
	// Check that the command buffer is not empty, retrieve previous command
	else if (command_buffer.size() > 0) {
		// Store current command in the command buffer
		if (buffer_selector == 0) {
			command_buffer.push_back(text.at(cursor.y));
		}

		
		if (buffer_selector < command_buffer.size() - 1) buffer_selector++;	// Iterate the buffer selector
		text.at(cursor.y) = command_buffer.at(command_buffer.size() - buffer_selector - 1);	// Retrieve command from command buffer
		cursor.x = text.at(cursor.y).size(); // Update cursor x position
	}
}

void NibbleTerminal::keyDown() {
	// If control is down scroll the terminal
	if (IsKeyDown(KEY_RIGHT_CONTROL) || IsKeyDown(KEY_LEFT_CONTROL)) {
		if (screen_scroll < text.size() - 1) screen_scroll++;
	}
	if (buffer_selector > 0) {
		buffer_selector--; // Move iterator
		text.at(cursor.y) = command_buffer.at(command_buffer.size() - buffer_selector - 1); // Retrieve command from command buffer
		cursor.x = text.at(cursor.y).size(); // Update cursor x position
	}
}

void NibbleTerminal::moveCursorLeft(int amount) {
	cursor.x -= amount;
	if (cursor.x < pre_line_offset) cursor.x = pre_line_offset;
}

void NibbleTerminal::moveCursorRight(int amount) {
	cursor.x += amount;
	if (cursor.x > text.at(cursor.y).length()) cursor.x = text.at(cursor.y).length();
}

std::string NibbleTerminal::getCommand(std::vector<std::string> split_input) {
	return(split_input.at(0));
}

std::vector<std::string> NibbleTerminal::getArguments(std::vector<std::string> split_input) {
	std::vector<std::string> arguments;
	for (int i = 1; i < split_input.size(); i++) {
		if (split_input.at(i).substr(0, 2) != "--") {
			arguments.push_back(split_input.at(i));
		}
	}

	return arguments;
}

std::vector<std::string> NibbleTerminal::getFlags(std::vector<std::string> split_input) {
	std::vector<std::string> flags;
	for (int i = 1; i < split_input.size(); i++) {
		if (split_input.at(i).substr(0, 2) == "--") {
			flags.push_back(split_input.at(i).substr(2, std::string::npos));
		}
	}

	return flags;
}

void NibbleTerminal::commandBuild() {

}
void NibbleTerminal::commandClearTerminal() {
	text.clear();
	cursor.y = -1; // Will go to zero when added to
	screen_scroll = 0;
}

void NibbleTerminal::commandDeleteFile() {

}
void NibbleTerminal::commandOpenEditor() {
	computer->startApplication(COMPUTER_APP_EDITOR, {{"computer", computer}});
}
void NibbleTerminal::commandFlashRom() {

}
void NibbleTerminal::commandHelp() {

}
void NibbleTerminal::commandListFiles() {

}
void NibbleTerminal::commandLoadFile() {

}
void NibbleTerminal::commandNewFile() {

}
void NibbleTerminal::commandDisplayRam() {

}
void NibbleTerminal::commandDisplayRom() {

}
void NibbleTerminal::commandSaveFile() {

}

void NibbleTerminal::printToTerminal(std::string string) {
	text.push_back(string);
	cursor.y++;
	scrollToCursor();
}

void NibbleTerminal::printToTerminal(std::vector<std::string> strings) {
	for (int s = 0; s < strings.size(); s++) {
		text.push_back(strings[s]);
		cursor.y++;
	}
	scrollToCursor();
}

void NibbleTerminal::scrollToCursor() {
	if (cursor.y >= screen_scroll + screen_text_height) {
		screen_scroll = cursor.y - screen_text_height + 2;
	}
}