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

	/*ngui = NibbleGUI();
	nkeyboard = NibbleKeyboard();

	ngui.setGUIFont(ngui.fonts.pixel_mono_8, 0.0f);

	pre_line_offset = 2;
	text.push_back("");

	font = ngui.getFont();
	font_size = MeasureTextEx(font, "M", font.baseSize, 0.0f);

	screen_border = { 24.0f, 24.0f, 24.0f, 24.0f };
	screen_buffer = { 4.0f, 4.0f, 4.0f, 4.0f };

	screen_width_px = computer->getScreenWidth();
	screen_height_px = computer->getScreenHeight();
	screen_text_height = (int)((screen_height_px - (screen_border.y + screen_buffer.y + screen_border.height + screen_buffer.height)) / (font_size.y + vspacing)) + 1;
	screen_text_width = (int)((screen_width_px - (screen_border.x + screen_buffer.x + screen_border.width + screen_buffer.width)) / (font_size.x + ngui.getFontSpacing()));*/
}

void NibbleEditor::input() {
	//nkeyboard.update(GetFrameTime());

	//int keycode = 0;

	//while ((keycode = nkeyboard.getKeyPressed())) {
	//	// Writable characters
	//	if (keycode >= 32 && keycode <= 126) {
	//		std::string string = nkeyboard.getStringFromKeycode(keycode, true);
	//		if (string != "") {
	//			text.at(cursor.y).append(string);
	//			cursor.x++;
	//		}

	//	}
	//	// Action characters
	//	else {
	//		// Navigation keys
	//		//if (keycode == KEY_LEFT) moveCursorLeft(1);
	//		//if (keycode == KEY_RIGHT) moveCursorRight(1);
	//		//if (keycode == KEY_UP) moveCursorUp(1);
	//		//if (keycode == KEY_DOWN) moveCursorDown(1);

	//		// Edit keys
	//		//if (keycode == KEY_BACKSPACE) keyBackspace();
	//		//if (keycode == KEY_DELETE) keyDelete();
	//		//if (keycode == KEY_ENTER) keyEnter();
	//	}
	//}


}

void NibbleEditor::update() {
}


void NibbleEditor::draw() {
	//// Draw backgound
	//DrawRectangle(0, 0, screen_width_px, screen_height_px, GRAY);
	//DrawRectangle(
	//	screen_border.x,
	//	screen_border.y,
	//	screen_width_px - screen_border.width - screen_border.x,
	//	screen_height_px - screen_border.height - screen_border.y,
	//	LIGHTGRAY
	//);

	//// Draw cursor
	//if (cursor.y < (screen_scroll + screen_text_height)) {
	//	DrawRectangle(
	//		screen_border.x + screen_buffer.x + cursor.x * font_size.x,
	//		screen_border.y + screen_buffer.y + (cursor.y - screen_scroll) * (font_size.y + vspacing) - 1,
	//		6, 10, YELLOW
	//	);
	//}

	//// Draw text to screen
	//int rows_to_draw = std::min(screen_text_height, (int)text.size() - screen_scroll);
	//for (int i = 0; i < rows_to_draw; i++) {
	//	ngui.drawText(text.at(i + screen_scroll), screen_border.x + screen_buffer.x, screen_border.y + screen_buffer.y + (font_size.y + vspacing) * i, BLACK);
	//}

}
