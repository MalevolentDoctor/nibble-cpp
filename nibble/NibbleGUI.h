// An immediate mode GUI for Nibble, using raylib

#ifndef NIBBLEGUI_H
#define NIBBLEGUI_H

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
struct GuiFonts {
	Font retro_gaming_11 = LoadFontEx("assets/fonts/retro_gaming_11px.ttf", 11, 0, 250);
	Font retro_gaming_22 = LoadFontEx("assets/fonts/retro_gaming_11px.ttf", 22, 0, 250);
	Font retro_gaming_33 = LoadFontEx("assets/fonts/retro_gaming_11px.ttf", 33, 0, 250);
};

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

	GuiColourPalette active_palette;		// Palette currently being used

	float corner_roundness = 0.5f;		// Corner roundness [0,1]
	int corner_segments = 0;
	float border_w = 4.0f;

	Font font = GetFontDefault();
	float font_size = 30.0f;
	float font_spacing = 3.0f;

	int text_align = TEXT_ALIGN_CENTRE_H | TEXT_ALIGN_CENTRE_V;

	Rectangle text_padding = { 5.0f, 5.0f, 5.0f, 5.0f };		// Inner padding for text, left, top, right, bottom
};

class NibbleGUI {
	public:
		NibbleGUI();

		bool Button(Rectangle bounds, std::string text);
		
		ButtonParams btn_params;
		GuiFonts gui_fonts;

	private:
		void DrawTextAligned(const char* text, Font font, int font_size, float font_spacing, Rectangle bounds, Rectangle padding, int alignment, Color colour);

		
};

#endif