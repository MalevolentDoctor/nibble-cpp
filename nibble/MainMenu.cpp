#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)

#include <cstdio>

#include "raylib/raylib.h"

#pragma warning(pop)


#include "MainMenu.h"
#include "NibbleGUI.h"


MainMenu::MainMenu(ProgramState* program_state) : program_state(program_state) {
	gui = NibbleGUI();

	// Title configuration
	title_font = gui.gui_fonts.retro_gaming_99;

	// Main menu buttons configuration
	gui.btn_params.font = gui.gui_fonts.kong_text_24;
	gui.btn_params.font_spacing = 0;

	gui.palette.normal = { {120, 85, 181, 255}, {64, 49, 92, 255}, {64, 49, 92, 255} };
	gui.palette.hover = {
		ColorBrightness(gui.palette.normal.background, 0.15f),
		ColorBrightness(gui.palette.normal.border, 0.0f),
		ColorBrightness(gui.palette.normal.text, 0.15f)
	};
	gui.palette.pressed = {
		ColorBrightness(gui.palette.normal.background, -0.2f),
		ColorBrightness(gui.palette.normal.border, -0.2f),
		ColorBrightness(gui.palette.normal.text, -0.2f)
	};
}

void MainMenu::input() {

}

void MainMenu::update(float dt) {

}

void MainMenu::draw() {

	if (program_state->mode != PROGRAM_MODE_MAIN_MENU) { return; }

	// Draw Background
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), { 82, 73, 99, 255 });

	Rectangle r = { 200, -120, 30, 500 };
	DrawRectanglePro(r, { 0, 0 }, 45.0f, {228, 3, 3, 255});

	r.x += 20; r.y += 20;
	DrawRectanglePro(r, { 0, 0 }, 45.0f, { 255, 140, 0, 255 });

	r.x += 20; r.y += 20;
	DrawRectanglePro(r, { 0, 0 }, 45.0f, { 255, 237, 0, 255 });

	r.x += 20; r.y += 20;
	DrawRectanglePro(r, { 0, 0 }, 45.0f, { 0, 128, 38, 255 });

	r.x += 20; r.y += 20;
	DrawRectanglePro(r, { 0, 0 }, 45.0f, { 36, 64, 142, 255 });

	r.x += 20; r.y += 20;
	DrawRectanglePro(r, { 0, 0 }, 45.0f, { 115, 41, 130, 255 });

	float screen_centre = GetScreenWidth() * 0.5f;

	// Draw Title
	Vector2 title_size = MeasureTextEx(title_font, title_text, title_font.baseSize, 0);
	float title_x = (GetScreenWidth() - title_size.x) * 0.5f;
	float title_y = GetScreenHeight() * 0.25f;
		DrawTextEx(title_font, title_text, { title_x, title_y }, title_font.baseSize, 0, BLACK);


	Vector2 button_size = { 200.0f, 50.0f };
	Rectangle rec = { screen_centre - button_size.x * 0.5f, title_y + title_size.y + button_size.y, button_size.x, button_size.y };

	if (gui.Button(rec, "START")) {
		printf("Pressed Start\n");
	}

	rec.y += rec.height * 1.5f;

	if (gui.Button(rec, "OPTIONS")) {
		printf("Pressed Options\n");
	}

	rec.y += rec.height * 1.5f;

	if (gui.Button(rec, "QUIT")) {
		program_state->state = PROGRAM_STATE_SHOULD_CLOSE;
	}

}