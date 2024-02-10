#pragma once

#include "Helper.hpp"
#include "NibbleGUI.h"
#include "NibbleTerminal.h"

enum DesktopPages {
	DESKTOP_PAGE_DESKTOP,
	DESKTOP_PAGE_EDITOR,
	DESKTOP_PAGE_CONSOLE
};

class NibbleDesktop {
	public:
		NibbleDesktop(ProgramState* program_state);
		NibbleDesktop() = default;

		void input();
		void update(float dt);
		void draw();

		void setDesktopPage(int page);
		void setDesktopMode(int mode);
		void setDesktopZoom(float zoom);

		int getDesktopMode();
		float getDesktopZoom();

	private:
		void drawDesktop();

		ProgramState* program_state;
		NibbleGUI ngui;
		NibbleTerminal console;

		int desktop_page = DESKTOP_PAGE_DESKTOP;
		int desktop_mode = DESKTOP_MODE_INACTIVE;

		RenderTexture2D screen;
		int screen_resolution_x = 624;
		int screen_resolution_y = 468;

		float zoom_scale = 1.0f;

		ButtonParams desktop_icon_params;
};

