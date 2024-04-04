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
#include "Terminal.h"
#include "Computer.h"
#include "Keyboard.h"
#include "GUI.h"

NibbleTerminal::NibbleTerminal() {
	ngui = new NibbleGUI();
	nkeyboard = NibbleKeyboard::getInstance();
	ngui->setGUIFont(ngui->fonts.pixel_mono_8x7, 1.0f);
	buffer = { 0, 0, 0, 0 };
	window = { 0, 0, 0, 0 };
	line_prompt_offset = 0;
	text_res = { 0, 0 };
}

void NibbleTerminal::init() {
	text.push_back(line_prompt);
	cursor.x = line_prompt_offset;
}

void NibbleTerminal::input() {
	std::vector<int> input_queue = nkeyboard->getInputQueue();
	size_t input_queue_length = input_queue.size();

	int keycode = 0;
	for (size_t i = 0; i < input_queue_length; i++) {
		if (!active) continue;

		keycode = input_queue.at(i);

		// Writable characters
		if (keycode >= 32 && keycode <= 126) {
			std::string string = nkeyboard->getStringFromKeycode(keycode, true);
			if (string != "") {
				text.at(cursor.y).append(string);
				cursor.x++;
			}

		}
		// Action characters
		else {
			// Navigation keys
			if (keycode == KEY_LEFT) keyLeft();
			if (keycode == KEY_RIGHT) keyRight();

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
	if (!visible) return;

	// Draw backgound
	DrawRectangle(window.x, window.y, window.width, window.height, background_colour);

	drawCursor();

	// Draw text to screen
	int rows_to_draw = std::min(text_res.y, (int)text.size() - screen_scroll);
	for (int i = 0; i < rows_to_draw; i++) {
		ngui->drawText(
			text.at(i + screen_scroll),
			window.x + buffer.x,
			window.y + buffer.y + (ngui->getFontHeight() + vspacing) * i + 1,
			text_colour
		);
	}
}

void NibbleTerminal::drawCursor() {
	// Draw cursor
	if (cursor.y < (screen_scroll + text_res.y)) {
		DrawRectangle(
			window.x + buffer.x + cursor.x * (ngui->getFontWidth()),
			window.y + buffer.y + (cursor.y - screen_scroll) * (ngui->getFontHeight() + vspacing) - 1,
			cursor.w, cursor.h, YELLOW
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
	std::string input = text.at(cursor.y).substr(line_prompt_offset, text.at(cursor.y).size() - line_prompt_offset);
	std::vector<std::string> split_input = stringSplit(input, " ");
	std::string command = getCommand(split_input);
	if (command.substr(0, 1) == "!") override_checks = true;
	std::vector<std::string> args = getArguments(split_input);
	std::vector<std::string> flags = getFlags(split_input);

	// Interpret command
	interpretCommand(command, args, flags, override_checks);

	// Create new line
	text.push_back(line_prompt);
	cursor.y++;
	cursor.x = line_prompt_offset;

	// Update scroll position
	scrollToCursor();
}

void NibbleTerminal::interpretCommand(std::string command, std::vector<std::string> args, std::vector<std::string> flags, bool override_checks) {
	printToTerminal("Error: No command interpretation methods available");
}

void NibbleTerminal::keyBackspace() {
	if (cursor.x > line_prompt_offset) {
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
		cursor.x = (int)text.at(cursor.y).size(); // Update cursor x position
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
		cursor.x = (int)text.at(cursor.y).size(); // Update cursor x position
	}
}

void NibbleTerminal::keyLeft() {
	if (cursor.x << line_prompt_offset > line_prompt_offset) cursor.x--;
}

void NibbleTerminal::keyRight() {
	if (cursor.x < text.at(cursor.y).length() - 1) cursor.x++;
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
	if (cursor.y >= screen_scroll + text_res.y) {
		screen_scroll = cursor.y - text_res.y + 2;
	}
}

void NibbleTerminal::setWindowSize(int x, int y) {
	window.width = x;
	window.height = y;
	text_res.x = (int)((x - (buffer.x + buffer.width)) / (ngui->getFontWidth() + ngui->getFontSpacing()));
	text_res.y = (int)((y - (buffer.y + buffer.height)) / (ngui->getFontHeight() + vspacing)) + 1;
}

void NibbleTerminal::setWindowPosition(int x, int y) {
	window.x = x;
	window.y = y;
}

void NibbleTerminal::setBackgroundColour(Color colour) {
	background_colour = colour;
}

void NibbleTerminal::setTextColour(Color colour) {
	text_colour = colour;
}



void NibbleTerminal::setLinePrompt(std::string prompt) {
	line_prompt = prompt;
	line_prompt_offset = (int)prompt.length();
}