#include "NibbleGUI.h"

NibbleGUI::NibbleGUI() {

}

bool NibbleGUI::button(Rectangle bounds, std::string text) {

	bool pressed = false;
	GuiColours btn_colours = { 255, 255, 255, 255 };

	btn_colours = palette.normal;

	// Check user input
	Vector2 mouse_pos = GetMousePosition();
	Rectangle collision_bounds = { bounds.x + offset.x, bounds.y + offset.y, bounds.width * scale.x, bounds.height * scale.y };
	if (CheckCollisionPointRec(mouse_pos, collision_bounds)) {
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			// If pressing the button
			btn_colours = palette.pressed;
		}
		else {
			// If hovering over, but not pressing, the button
			btn_colours = palette.hover;
		}

		// Send pressed event when mouse button is released
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
			pressed = true;
		}
	}

	// Background
	DrawRectangleRounded(bounds, btn_params.corner_roundness, btn_params.corner_segments, btn_colours.background);

	// Border
	Rectangle bd_bounds = { 
		bounds.x + btn_params.border_w / 2,
		bounds.y + btn_params.border_w / 2, 
		bounds.width - btn_params.border_w, 
		bounds.height - btn_params.border_w 
	};
	DrawRectangleRoundedLines(bd_bounds, btn_params.corner_roundness, btn_params.corner_segments, btn_params.border_w, btn_colours.border);

	// Text
	DrawTextAligned(
		text.c_str(),
		bounds,
		btn_params.text_padding,
		btn_params.text_align,
		btn_colours.text
	);

	return pressed;

}

void NibbleGUI::DrawTextAligned(const char* text, Rectangle bounds, Rectangle padding, int alignment, Color colour) {
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

void NibbleGUI::drawText(std::string text_str, float x, float y, Color colour) {
	DrawTextEx(font, text_str.c_str(), { x, y }, font.baseSize, font_spacing, colour);
}

void NibbleGUI::setGUIColourPalette(GuiPalette gui_palette) { palette = gui_palette; }
void NibbleGUI::setButtonParams(ButtonParams button_params) { btn_params = button_params; }

void NibbleGUI::setGUIFont(Font _font, float _font_spacing) {
	font = _font;
	font_spacing = _font_spacing;
}

void NibbleGUI::setGUIOffset(float x, float y) { offset = { x, y }; }
void NibbleGUI::setGUIScale(float x, float y) { scale = { x, y }; }

Font NibbleGUI::getFont() { return font; }
float NibbleGUI::getFontSpacing() { return font_spacing; }

int NibbleGUI::getFontHeight() { return font.baseSize; }
int NibbleGUI::getFontWidth() {
	Vector2 fontSize = MeasureTextEx(font, "W", font.baseSize, font_spacing);
	return fontSize.x;
}