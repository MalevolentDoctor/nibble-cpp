#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)

#include<string>
#include<vector>

#include "raylib/raylib.h"

#pragma warning(pop)


#include "Editor.h"
#include "Computer.h"

NibbleEditor::NibbleEditor(NibbleComputer* _computer) {
	computer = _computer;

	ngui = NibbleGUI();
	nkeyboard = NibbleKeyboard();

	ngui.setGUIFont(ngui.fonts.pixel_mono_8, 0.0f);

	text.push_back("");

	border = { 24, 24, 24, 24 };
	buffer = { 4, 4, 4, 4 };

	screen_text_width = 
		(int)((computer->getScreenWidth() - (border.x + buffer.x + border.width + buffer.width)) / (ngui.getFontWidth() + ngui.getFontSpacing()));
	screen_text_height = 
		(int)((computer->getScreenHeight() - (border.y + buffer.y + border.height + buffer.height)) / (ngui.getFontHeight() + vspacing)) + 1;

}

void NibbleEditor::input() {
	nkeyboard.update(GetFrameTime());

	int keycode = 0;

	while ((keycode = nkeyboard.getKeyPressed())) {
		if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) { // Modifier Key


		} else if (keycode >= 32 && keycode <= 126) { // Writable characters
			std::string string = nkeyboard.getStringFromKeycode(keycode, true);
			if (string != "") {
				if (term_active) {
					term_text.at(term_cursor.y).insert(term_cursor.x, string);
				}
				else {
					text.at(cursor.y).insert(cursor.x, string);
					cursor.x++;
					cursor_x_cache = cursor.x;
					updateScrollPosition();
				}
			}
		}
		// Action characters
		else {
			// Navigation keys
			if (keycode == KEY_LEFT) keyLeftArrow();
			if (keycode == KEY_RIGHT) keyRightArrow();
			if (keycode == KEY_UP) keyUpArrow();
			if (keycode == KEY_DOWN) keyDownArrow();
			if (keycode == KEY_END) keyEnd();
			if (keycode == KEY_HOME) keyHome();
			if (keycode == KEY_PAGE_DOWN) keyPageDown();
			if (keycode == KEY_PAGE_UP) keyPageUp();

			// Edit keys
			if (keycode == KEY_BACKSPACE) keyBackspace();
			if (keycode == KEY_DELETE) keyDelete();
			if (keycode == KEY_ENTER) keyEnter();

			if (keycode == KEY_ESCAPE) keyEscape();
		}
	}


}

void NibbleEditor::update() {
	line_indent = (int)std::to_string(text.size() - 1).size() + 1;
}


void NibbleEditor::draw() {
	// Draw backgound
	DrawRectangle(0, 0, computer->getScreenWidth(), computer->getScreenHeight(), GRAY);
	DrawRectangle(
		border.x,
		border.y,
		computer->getScreenWidth() - border.width - border.x,
		computer->getScreenHeight() - border.height - border.y,
		LIGHTGRAY
	);
	// Draw cursor
	drawCursor();

	// Draw text to screen
	drawText();

	if (term_active) {
		int y = border.y + buffer.y + (screen_text_height) * (ngui.getFontHeight() + vspacing);
		DrawRectangle(
			border.x, y,
			computer->getScreenWidth() - border.width - border.x,
			computer->getScreenHeight() - y - border.height,
			BLACK
		);
	}
}

void NibbleEditor::drawText() {
	int rows_to_draw = std::min(screen_text_height, (int)text.size() - screen_scroll);

	int x = border.x + buffer.x;
	int xx = x + line_indent * ngui.getFontWidth();
	int y = border.y + buffer.y;
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
		int x = border.x + buffer.x + (cursor.x + line_indent) * ngui.getFontWidth();
		int y = border.y + buffer.y + (cursor.y - screen_scroll) * (ngui.getFontHeight() + vspacing) - 1;
		DrawRectangle(x, y, cursor.w, cursor.h, YELLOW);
	}
}

void NibbleEditor::keyEnter() {

	text.insert(text.begin() + cursor.y + 1, text.at(cursor.y).substr(cursor.x));	// Insert right of cursor (inlcusive) to next line
	text.at(cursor.y) = text.at(cursor.y).substr(0, cursor.x); // remove right of cursor (inclusive) from curren line

	// update the cursor position
	cursor.y++;
	cursor.x = 0;
	cursor_x_cache = cursor.x;
	updateScrollPosition();
}

#pragma region Navigation Keys

// Arrow Keys
void NibbleEditor::keyUpArrow() {
	if (cursor.y > 0) {
		cursor.y--;
		cursor.x = (cursor_x_cache > (int)text.at(cursor.y).length()) ? (int)text.at(cursor.y).length() : cursor_x_cache;
	}
	updateScrollPosition();
}

void NibbleEditor::keyDownArrow() {
	if (cursor.y < text.size() - 1) {
		cursor.y++;
		cursor.x = (cursor_x_cache > (int)text.at(cursor.y).length()) ? (int)text.at(cursor.y).length() : cursor_x_cache;
	}
	updateScrollPosition();
}

void NibbleEditor::keyLeftArrow() {
	cursor.x--;

	// If pressing left at the start of a line go to the previous line, otherwise, don't move.
	if (cursor.x < 0) {
		if (cursor.y > 0) {
			cursor.y--;
			cursor.x = (int)text.at(cursor.y).length();
		}
		else {
			cursor.x = 0;
		}
	}

	cursor_x_cache = cursor.x;
	updateScrollPosition();
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
	updateScrollPosition();
}

void NibbleEditor::keyEnd() {
	cursor.x = text.at(cursor.y).length();
}

void NibbleEditor::keyHome() {
	cursor.x = 0;
}

void NibbleEditor::keyPageDown() {
	cursor.y += screen_text_height - 1;
	if (cursor.y >= text.size()) cursor.y = text.size() - 1;
	updateScrollPosition();
}

void NibbleEditor::keyPageUp() {
	cursor.y -= screen_text_height - 1;
	if (cursor.y < 0) cursor.y = 0;
	updateScrollPosition();
}

#pragma endregion

void NibbleEditor::updateScrollPosition() {
	if (cursor.y < screen_scroll) {
		screen_scroll = cursor.y;
	}

	if (cursor.y >= screen_scroll + screen_text_height) {
		screen_scroll = cursor.y - screen_text_height + 1;
	}
}

void NibbleEditor::keyBackspace() {
	// inline backspace
	if (cursor.x > 0) {
		text.at(cursor.y).erase((size_t)(cursor.x - 1), 1);
		cursor.x--;
	}
	// cross line backspace
	else if (cursor.y > 0) {
		cursor.x = (int)text.at(cursor.y - 1).length();
		text.at(cursor.y - 1).append(text.at(cursor.y));
		text.erase(text.begin() + cursor.y);
		cursor.y--;
	}

	updateScrollPosition();
}

void NibbleEditor::keyDelete() {
	// inline delete
	if (cursor.x < text.at(cursor.y).length()) {
		text.at(cursor.y).erase(cursor.x, 1);
	}
	// cross line delete
	else if (cursor.y < text.size() - 1) {
		text.at(cursor.y).append(text.at(cursor.y + 1));
		text.erase(text.begin() + cursor.y + 1);
	}

	updateScrollPosition();
}

void NibbleEditor::keyEscape() {
	term_active = !term_active;
	screen_text_height += term_height * ((term_active * -2) + 1);
	updateScrollPosition();
}