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
			}

		}
		// Action characters
		else {
			// Navigation keys
			//if (keycode == KEY_LEFT) moveCursorLeft(1);
			//if (keycode == KEY_RIGHT) moveCursorRight(1);
			//if (keycode == KEY_UP) moveCursorUp(1);
			//if (keycode == KEY_DOWN) moveCursorDown(1);

			// Edit keys
			//if (keycode == KEY_BACKSPACE) keyBackspace();
			//if (keycode == KEY_DELETE) keyDelete();
			//if (keycode == KEY_ENTER) keyEnter();
		}
	}


}

void NibbleEditor::update() {
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
	int rows_to_draw = std::min(screen_text_height, (int)text.size() - screen_scroll);
	for (int i = 0; i < rows_to_draw; i++) {
		ngui.drawText(text.at(i + screen_scroll), screen_border.x + screen_buffer.x, screen_border.y + screen_buffer.y + (ngui.getFontHeight() + vspacing) * i, BLACK);
	}

}

void NibbleEditor::drawCursor() {
	
	// Draw cursor
	if (cursor.y < (screen_scroll + screen_text_height)) {
		printf("draw_cursor\n");
		DrawRectangle(
			screen_border.x + screen_buffer.x + cursor.x * ngui.getFontWidth(),
			screen_border.y + screen_buffer.y + (cursor.y - screen_scroll) * (ngui.getFontHeight() + vspacing) - 1,
			cursor.w, cursor.h, YELLOW
		);
	}
}
