#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)

#include <cstdio>

#include "raylib/raylib.h"

#pragma warning(pop)


#include "MainMenu.h"
#include "GUI.h"


MainMenu::MainMenu(ProgramState* program_state) : program_state(program_state) {
	gui = NibbleGUI();

	// Title configuration
	title_font = gui.fonts.retro_gaming_99;

	// Main menu buttons configuration
	gui.setGUIFont(gui.fonts.kong_text_24, 0.0f);

	GuiPalette main_menu_palette;

	main_menu_palette.normal = { {120, 85, 181, 255}, {64, 49, 92, 255}, {64, 49, 92, 255} };
	main_menu_palette.hover = {
		ColorBrightness(main_menu_palette.normal.background, 0.15f),
		ColorBrightness(main_menu_palette.normal.border, 0.0f),
		ColorBrightness(main_menu_palette.normal.text, 0.15f)
	};
	main_menu_palette.pressed = {
		ColorBrightness(main_menu_palette.normal.background, -0.2f),
		ColorBrightness(main_menu_palette.normal.border, -0.2f),
		ColorBrightness(main_menu_palette.normal.text, -0.2f)
	};
	
	gui.setGUIColourPalette(main_menu_palette);
}

void MainMenu::input() {

}

void MainMenu::update(float dt) {

}

void MainMenu::draw() {

	// Draw background
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), { 82, 73, 99, 255 });

	// Rainbow stripes
	Rectangle r = { 200, -120, 30, 500 };
	DrawRectanglePro(r, { 0, 0 }, 45.0f, {228, 3, 3, 255});			// Red

	r.x += 20; r.y += 20;
	DrawRectanglePro(r, { 0, 0 }, 45.0f, { 255, 140, 0, 255 });		// Orange

	r.x += 20; r.y += 20;
	DrawRectanglePro(r, { 0, 0 }, 45.0f, { 255, 237, 0, 255 });		// Yellow

	r.x += 20; r.y += 20;
	DrawRectanglePro(r, { 0, 0 }, 45.0f, { 0, 128, 38, 255 });		// Green

	r.x += 20; r.y += 20;
	DrawRectanglePro(r, { 0, 0 }, 45.0f, { 36, 64, 142, 255 });		// Blue

	r.x += 20; r.y += 20;
	DrawRectanglePro(r, { 0, 0 }, 45.0f, { 115, 41, 130, 255 });	// Purple

	float screen_centre = GetScreenWidth() * 0.5f;

	// Draw title
	Vector2 title_size = MeasureTextEx(title_font, title_text, (float)title_font.baseSize, 0.0f);
	float title_x = (GetScreenWidth() - title_size.x) * 0.5f;
	float title_y = GetScreenHeight() * 0.25f;
	DrawTextEx(title_font, title_text, { title_x, title_y }, (float)title_font.baseSize, 0.0f, BLACK);

	// Draw buttons
	Vector2 button_size = { 200.0f, 50.0f };
	Rectangle rec = { screen_centre - button_size.x * 0.5f, title_y + title_size.y + button_size.y, button_size.x, button_size.y };

	if (gui.button(rec, "START")) {
		program_state->state = PROGRAM_STATE_STARTING;
		program_state->mode = PROGRAM_MODE_WORKBENCH;
	}

	rec.y += rec.height * 1.5f;

	if (gui.button(rec, "OPTIONS")) {
		printf("Pressed Options\n");
	}

	rec.y += rec.height * 1.5f;

	if (gui.button(rec, "QUIT")) {
		program_state->state = PROGRAM_STATE_SHOULD_CLOSE;
	}

}