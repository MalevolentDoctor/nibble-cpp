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
	Font retro_gaming_99 = LoadFontEx("assets/fonts/retro_gaming_11px.ttf", 99, 0, 250);

	Font kong_text_8 = LoadFontEx("assets/fonts/kongtext.ttf", 8, 0, 250);
	Font kong_text_16 = LoadFontEx("assets/fonts/kongtext.ttf", 16, 0, 250);
	Font kong_text_24 = LoadFontEx("assets/fonts/kongtext.ttf", 24, 0, 250);
	Font kong_text_32 = LoadFontEx("assets/fonts/kongtext.ttf", 32, 0, 250);

	Font pixel_mono_8 = LoadFontEx("assets/fonts/pixelmono8x8.ttf", 8, 0, 250);
};

struct GuiColours {
	Color background = LIGHTGRAY;	// Primary colour
	Color border = GRAY;			// Secondary colour
	Color text = BLACK;				// Tertiary colour
};

struct GuiPalette {
	GuiColours normal;		// Colours under normal operation
	GuiColours hover = { GRAY, DARKGRAY, DARKGRAY };	// Colours when being hovered over
	GuiColours pressed;		// Colours when pressed
	GuiColours disabled = { {176, 176, 176, 255},{122, 122, 122, 255}, {122, 122, 122, 255} };		// Colours when disabled
};

struct ButtonParams {
	float corner_roundness = 0.0f;		// Corner roundness [0,1]
	int corner_segments = 10;
	float border_w = 4.0f;



	int text_align = TEXT_ALIGN_CENTRE_H | TEXT_ALIGN_CENTRE_V;

	Rectangle text_padding = { 5.0f, 5.0f, 5.0f, 5.0f };		// Inner padding for text, left, top, right, bottom
};

class NibbleGUI {
	public:
		NibbleGUI();

		bool button(Rectangle bounds, std::string text);
		void drawText(std::string text_str, float x, float y, Color colour);

		void setGUIColourPalette(GuiPalette gui_palette);
		void setButtonParams(ButtonParams button_params);
		void setGUIFont(Font _font, float _font_spacing);
		void setGUIOffset(float x, float y);
		void setGUIScale(float x, float y);

		Font getFont();
		float getFontSpacing();

		GuiFonts fonts;

	private:
		void DrawTextAligned(const char* text, Rectangle bounds, Rectangle padding, int alignment, Color colour);

		ButtonParams btn_params;
		GuiPalette palette;

		Font font = GetFontDefault();
		float font_spacing = 3.0f;

		// UI Elements offset (for interactive elements
		Vector2 offset = { 0.0f, 0.0f };
		Vector2 scale = { 1.0f, 1.0f };

};

#endif