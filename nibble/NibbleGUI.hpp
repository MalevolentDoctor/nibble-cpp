// An immediate mode GUI for Nibble, using raylib

#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)

#include <string>

#include "raylib/raylib.h"

#pragma warning(pop)


// Define emums
enum TextAlign {
	TEXT_ALIGN_CENTRE_H = 1,
	TEXT_ALIGN_LEFT = 2,
	TEXT_ALIGN_RIGHT = 4,
	TEXT_ALIGN_CENTRE_V = 8,
	TEXT_ALIGN_TOP = 16,
	TEXT_ALIGN_BOTTOM = 32
};

// Define structs
struct GuiColourPalette {
	Color background = LIGHTGRAY;	// Primary colour
	Color border = GRAY;			// Secondary colour
	Color text = GRAY;				// Tertiary colour
};

struct ButtonParams {
	GuiColourPalette normal_palette;		// Colours under normal operation
	GuiColourPalette hover_palette = { GRAY, DARKGRAY, DARKGRAY };	// Colours when being hovered over
	GuiColourPalette pressed_palette;		// Colours when pressed
	GuiColourPalette disabled_palette;		// Colours when disabled

	GuiColourPalette active_palette;

	float corner_roundness = 0.5f;
	int corner_segments = 0;
	float border_w = 4.0f;
	float font_size = 30.0f;
	float font_spacing = 3.0f;

	int text_align = TEXT_ALIGN_CENTRE_H | TEXT_ALIGN_CENTRE_V;

	Rectangle text_padding = { 5.0f, 5.0f, 5.0f, 5.0f };
};

// Global variables
static ButtonParams btn_params;

// Declare functions
bool nbButton(Rectangle bounds, std::string text);
void nbDrawTextAligned(const char* text, int font_size, float font_spacing, Rectangle bounds, Rectangle padding, int alignment, Color colour);

// Define functions

bool nbButton(Rectangle bounds, std::string text) {
#define palette btn_params.active_palette

	bool pressed = false;

	palette = btn_params.normal_palette;

	// Check user input
	Vector2 mouse_pos = GetMousePosition();
	if (CheckCollisionPointRec(mouse_pos, bounds)) {
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			// If pressing the button
			palette = btn_params.pressed_palette;
		}
		else {
			// If hovering over, but not pressing, the button
			palette = btn_params.hover_palette;
		}

		// Send pressed event when mouse button is released
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
			pressed = true;
		}
	}

	// Background
	DrawRectangleRounded(bounds, btn_params.corner_roundness, btn_params.corner_segments, palette.background);

	// Border
	Rectangle bd_bounds = { bounds.x + btn_params.border_w / 2, bounds.y + btn_params.border_w / 2, bounds.width - btn_params.border_w, bounds.height - btn_params.border_w };
	DrawRectangleRoundedLines(bd_bounds, btn_params.corner_roundness, btn_params.corner_segments, btn_params.border_w, palette.border);

	// Text
	nbDrawTextAligned(text.c_str(), btn_params.font_size, btn_params.font_spacing, bounds, btn_params.text_padding, btn_params.text_align, palette.text);

	return pressed;
#undef pallete
}

void nbDrawTextAligned(const char* text, int font_size, float font_spacing, Rectangle bounds, Rectangle padding, int alignment, Color colour) {
	int x = 0;
	int y = 0;

	Vector2 text_size = MeasureTextEx(GetFontDefault(), text, font_size, font_spacing);

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

	DrawTextEx(GetFontDefault(), text, { (float)x, (float)y }, font_size, font_spacing, colour);
}