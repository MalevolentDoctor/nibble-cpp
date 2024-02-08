#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)

#include<vector>
#include<string>
#include<iostream> // for some debugging

#pragma warning(pop)

#include "Helper.hpp"
#include "NibbleConsole.h"
#include "NibbleGUI.h"



NibbleConsole::NibbleConsole(RenderTexture2D screen) : screen(screen) {
	ngui = NibbleGUI();
	nkeyboard = NibbleKeyboard();

	ngui.setGUIFont(ngui.fonts.kong_text_8, 0.0f);

	cursor_x = 0;
	cursor_y = 0;

	Font _font = ngui.getFont();
	Vector2 font_size = MeasureTextEx(_font, "M", _font.baseSize, 0.0f);

	max_lines = (int)((screen.texture.height - (internal_border.y + internal_buffer.y + internal_border.height + internal_buffer.height)) / (font_size.y + vspacing));
	max_chars = (int)((screen.texture.width - (internal_border.x + internal_buffer.x + internal_border.width + internal_buffer.width)) / (font_size.x + ngui.getFontSpacing()));
}

void NibbleConsole::input() {
	nkeyboard.update(GetFrameTime());

	int keycode = 0;

	while ((keycode = nkeyboard.getKeyPressed())) {
		// Writable characters
		if (keycode >= 32 && keycode <= 126) {
			std::string string = nkeyboard.getStringFromKeycode(keycode, true);
			if (string != "") {
				std::cout << string << std::endl;
			}

		}
		// Action characters
		else {
			
		}
	}

	// Directional input
	if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT)) { cursor_x--; }
	if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT)) { cursor_x++; }
	if (IsKeyPressed(KEY_UP)  || IsKeyPressedRepeat(KEY_UP)) { cursor_y--; }
	if (IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN)) { cursor_y++; }

}




void NibbleConsole::draw() {
	// Draw cursor
	DrawRectangle(cursor_x * 8 + 1, cursor_y * 8, 6, 8, YELLOW);

	ngui.drawText("12345678901234567890123456789012345678901234567890123456789012345678901234567890", 0, 0, BLACK);
}