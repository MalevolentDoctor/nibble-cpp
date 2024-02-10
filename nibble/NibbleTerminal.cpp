#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)

#include<vector>
#include<string>
#include<algorithm>
#include<cstdio> // for some debugging

#pragma warning(pop)

#include "Helper.hpp"
#include "NibbleTerminal.h"
#include "NibbleGUI.h"



NibbleTerminal::NibbleTerminal(RenderTexture2D screen) : screen(screen) {
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

	screen_text_height = (int)((screen.texture.height - (screen_border.y + screen_buffer.y + screen_border.height + screen_buffer.height)) / (font_size.y + vspacing)) + 1;
	screen_text_width = (int)((screen.texture.width - (screen_border.x + screen_buffer.x + screen_border.width + screen_buffer.width)) / (font_size.x + ngui.getFontSpacing()));
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

		printf("Command Buffer Size = %d\n", command_buffer.size());
		printf("Buffer Selector = %d\n", buffer_selector);
	}
}

void NibbleTerminal::draw() {
	// Draw backgound
	DrawRectangle(0, 0, screen.texture.width, screen.texture.height, GRAY);
	DrawRectangle(
		screen_border.x,
		screen_border.y,
		screen.texture.width - screen_border.width - screen_border.x,
		screen.texture.height - screen_border.height - screen_border.y,
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
		ngui.drawText(text.at(i + screen_scroll), screen_border.x + screen_buffer.x, screen_border.y + screen_buffer.y + (font_size.y + vspacing) * i, BLACK);
	}

}

void NibbleTerminal::keyEnter() {
	// Add command to the command buffer
	if (text.at(cursor.y) != "") {
		if (command_buffer.size() == 0) {
			command_buffer.push_back(text.at(cursor.y));
		}
		else {
			if (command_buffer.back() != text.at(cursor.y)) {
				command_buffer.push_back(text.at(cursor.y));
			}
		}
	}
	
	// Create new line
	text.push_back(pre_line);
	cursor.y++;
	cursor.x = pre_line_offset;

	// Update scroll position
	if (cursor.y >= screen_text_height) screen_scroll++;
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