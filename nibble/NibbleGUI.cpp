#include "NibbleGUI.h"

NibbleGUI::NibbleGUI() {

}

bool NibbleGUI::Button(Rectangle bounds, std::string text) {
#define palette btn_params.active_palette

	bool pressed = false;

	palette = gui_palette.normal_palette;

	// Check user input
	Vector2 mouse_pos = GetMousePosition();
	if (CheckCollisionPointRec(mouse_pos, bounds)) {
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			// If pressing the button
			palette = gui_palette.pressed_palette;
		}
		else {
			// If hovering over, but not pressing, the button
			palette = gui_palette.hover_palette;
		}

		// Send pressed event when mouse button is released
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
			pressed = true;
		}
	}

	// Background
	DrawRectangleRounded(bounds, btn_params.corner_roundness, btn_params.corner_segments, palette.background);

	// Border
	Rectangle bd_bounds = { 
		bounds.x + btn_params.border_w / 2,
		bounds.y + btn_params.border_w / 2, 
		bounds.width - btn_params.border_w, 
		bounds.height - btn_params.border_w 
	};
	DrawRectangleRoundedLines(bd_bounds, btn_params.corner_roundness, btn_params.corner_segments, btn_params.border_w, palette.border);

	// Text
	DrawTextAligned(
		text.c_str(),
		btn_params.font,
		btn_params.font_spacing,
		bounds,
		btn_params.text_padding,
		btn_params.text_align,
		palette.text
	);

	return pressed;

#undef pallete
}

void NibbleGUI::DrawTextAligned(const char* text, Font font, float font_spacing, Rectangle bounds, Rectangle padding, int alignment, Color colour) {
	int x = 0;
	int y = 0;

	Vector2 text_size = MeasureTextEx(font, text, font.baseSize, font_spacing);

	if (alignment & TEXT_ALIGN_CENTRE_H) {
		x = ((int)(bounds.x + padding.x + bounds.x + bounds.width - padding.width) >> 1) - ((int)text_size.x >> 1);
	}
	else if (alignment & TEXT_ALIGN_LEFT) {
		x = (int)(bounds.x + padding.x);
	}
	else if (alignment & TEXT_ALIGN_RIGHT) {
		x = (int)(bounds.x + bounds.width - padding.width - text_size.x);
	}

	if (alignment & TEXT_ALIGN_CENTRE_V) {
		y = ((int)(bounds.y + padding.y + bounds.y + bounds.height - padding.height) >> 1) - ((int)text_size.y >> 1);
	}
	else if (alignment & TEXT_ALIGN_TOP) {
		y = (int)(bounds.y + padding.y);
	}
	else if (alignment & TEXT_ALIGN_BOTTOM) {
		y = (int)(bounds.y + bounds.height - padding.height - text_size.y);
	}

	DrawTextEx(font, text, { (float)x, (float)y }, font.baseSize, font_spacing, colour);
}