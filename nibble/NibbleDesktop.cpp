#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)

#include "raylib/raylib.h"

#pragma warning(pop)

#include "NibbleDesktop.h"
#include "NibbleGUI.h"

NibbleDesktop::NibbleDesktop(ProgramState* program_state) : program_state(program_state) {
	screen = LoadRenderTexture(screen_resolution_x, screen_resolution_y);
	ngui = NibbleGUI();

	// setup desktop icon parameters
	desktop_icon_params.corner_roundness = 0.2f;
	desktop_icon_params.border_w = 2.0f;

	ngui.setGUIFont(ngui.fonts.kong_text_8, 0.0f);


	ngui.setButtonParams(desktop_icon_params);
}



void NibbleDesktop::input() {

}

void NibbleDesktop::update(float dt) {

}

void NibbleDesktop::draw() {
	// Temp Background (will be in the background texture)
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), SKYBLUE);
	DrawRectangle(0, GetScreenHeight() / 2, GetScreenWidth(), GetScreenHeight() / 2, BROWN);

	Rectangle src = { 0, 0, screen.texture.width, -screen.texture.height };
	Rectangle dest = { 
		GetScreenWidth() / 2 - screen_resolution_x * zoom_scale / 2,
		(GetScreenHeight() - screen_resolution_y * zoom_scale) * 0.4,
		screen.texture.width * zoom_scale,
		screen.texture.height * zoom_scale
	};

	// CRT border (temporary)
	float border = 90 * zoom_scale;
	DrawRectangle(dest.x - border, dest.y - border, dest.width + border * 2, dest.height + border * 2 + 40, DARKGRAY);
	ngui.setGUIOffset(dest.x, dest.y);
	ngui.setGUIScale(zoom_scale, zoom_scale);

	// Draw screen contents
	BeginTextureMode(screen);

	DrawRectangle(0, 0, screen.texture.width, screen.texture.height, GRAY);
	if (desktop_mode == DESKTOP_MODE_ACTIVE) {
		DrawTextEx(ngui.fonts.kong_text_8, "DESKTOP IS ACTIVE", { 5, 50 }, 8, 0, BLACK);
	}

	if (desktop_mode == DESKTOP_MODE_INACTIVE) {
		DrawTextEx(ngui.fonts.kong_text_8, "DESKTOP IS INACTIVE", { 5, 50 }, 8, 0, BLACK);
	}

	if (desktop_page == DESKTOP_PAGE_DESKTOP) {
		drawDesktop();
	}

	EndTextureMode();

	DrawTexturePro(screen.texture, src, dest, { 0, 0 }, 0.0f, WHITE);
}

void NibbleDesktop::drawDesktop() {
	Rectangle ui_icons = { 8, 8, 64, 64 };
	if (ngui.button(ui_icons, "EDITOR")) {

	}

	ui_icons.y += ui_icons.height * 1.2;
	if (ngui.button(ui_icons, "CONSOLE")) {

	}

	ui_icons.y += ui_icons.height * 1.2;
	if (ngui.button(ui_icons, "FILES")) {

	}
}


void NibbleDesktop::setDesktopMode(int mode) { desktop_mode = mode; }
void NibbleDesktop::setDesktopZoom(float zoom) { zoom_scale = zoom; }

int NibbleDesktop::getDesktopMode() { return desktop_mode; }
float NibbleDesktop::getDesktopZoom() { return zoom_scale; }