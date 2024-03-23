#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)

#include<string>
#include<vector>

#include "raylib/raylib.h"

#pragma warning(pop)


#include "NibbleEditor.h"
#include "NibbleComputer.h"

NibbleEditor::NibbleEditor(NibbleComputer* _computer) {
	computer = _computer;

	ngui = NibbleGUI();
	nkeyboard = NibbleKeyboard();

	ngui.setGUIFont(ngui.fonts.pixel_mono_8, 0.0f);

	pre_line_offset = 2;
	text.push_back("");

	screen_border = { 24.0f, 24.0f, 24.0f, 24.0f };
	screen_buffer = { 4.0f, 4.0f, 4.0f, 4.0f };

	screen_text_width = 
		(int)((computer->getScreenWidth() - (screen_border.x + screen_buffer.x + screen_border.width + screen_buffer.width)) / (ngui.getFontWidth() + ngui.getFontSpacing()));
	screen_text_height = 
		(int)((computer->getScreenHeight() - (screen_border.y + screen_buffer.y + screen_border.height + screen_buffer.height)) / (ngui.getFontHeight() + vspacing)) + 1;

}

void NibbleEditor::input() {
	nkeyboard.update(GetFrameTime());

	int keycode = 0;

	while ((keycode = nkeyboard.getKeyPressed())) {
		if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) { // Modifier Key


		} else if (keycode >= 32 && keycode <= 126) { // Writable characters
			std::string string = nkeyboard.getStringFromKeycode(keycode, true);
			if (string != "") {
				text.at(cursor.y).append(string);
				cursor.x++;
				cursor_x_cache = cursor.x;
			}

		}
		// Action characters
		else {
			// Navigation keys
			if (keycode == KEY_LEFT) keyLeftArrow();
			if (keycode == KEY_RIGHT) keyRightArrow();
			if (keycode == KEY_UP) keyUpArrow();
			if (keycode == KEY_DOWN) keyDownArrow();

			// Edit keys
			//if (keycode == KEY_BACKSPACE) keyBackspace();
			//if (keycode == KEY_DELETE) keyDelete();
			if (keycode == KEY_ENTER) keyEnter();
		}
	}


}

void NibbleEditor::update() {
	line_indent = std::to_string(text.size()).size() + 1;
}


void NibbleEditor::draw() {
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
	drawCursor();

	// Draw text to screen
	drawText();

}

void NibbleEditor::drawText() {
	int rows_to_draw = std::min(screen_text_height, (int)text.size() - screen_scroll);

	int x = screen_border.x + screen_buffer.x;
	int xx = x + line_indent * ngui.getFontWidth();
	int y = screen_border.y + screen_buffer.y;
	int dy = ngui.getFontHeight() + vspacing;

	for (int i = 0; i < rows_to_draw; i++) {
		int line_num = i + screen_scroll;
		std::string line_num_str = std::to_string(i + screen_scroll);

		int yy = y + dy * i;
		ngui.drawText(line_num_str, x, yy, DARKGRAY);
		ngui.drawText(text.at(line_num), xx, yy, BLACK);
	}
}

void NibbleEditor::drawCursor() {
	if (cursor.y < (screen_scroll + screen_text_height)) {
		int x = screen_border.x + screen_buffer.x + (cursor.x + line_indent) * ngui.getFontWidth();
		int y = screen_border.y + screen_buffer.y + (cursor.y - screen_scroll) * (ngui.getFontHeight() + vspacing) - 1;
		DrawRectangle(x, y, cursor.w, cursor.h, YELLOW);
	}
}


// temporary implementation for implementing line numbers
void NibbleEditor::keyEnter() {
	cursor.y++;
	cursor.x = 0;
	cursor_x_cache = cursor.x;

	text.push_back("");
}


// Arrow Keys
void NibbleEditor::keyUpArrow() {
	if (cursor.y > 0) {
		cursor.y--;
		cursor.x = (cursor_x_cache > text.at(cursor.y).length()) ? text.at(cursor.y).length() : cursor_x_cache;
	}
}

void NibbleEditor::keyDownArrow() {
	if (cursor.y < text.size() - 1) {
		cursor.y++;
		cursor.x = (cursor_x_cache > text.at(cursor.y).length()) ? text.at(cursor.y).length() : cursor_x_cache;
	}
}

void NibbleEditor::keyLeftArrow() {
	cursor.x--;

	// If pressing left at the start of a line go to the previous line, otherwise, don't move.
	if (cursor.x < 0) {
		if (cursor.y > 0) {
			cursor.y--;
			cursor.x = text.at(cursor.y).length();
		}
		else {
			cursor.x = 0;
		}
	}

	cursor_x_cache = cursor.x;
}

void NibbleEditor::keyRightArrow() {
	cursor.x++;

	if (cursor.x > text.at(cursor.y).length()) {
		if (cursor.y < text.size() - 1) {
			cursor.y++;
			cursor.x = 0;
		}
		else {
			cursor.x--;
		}
	}

	cursor_x_cache = cursor.x;
}