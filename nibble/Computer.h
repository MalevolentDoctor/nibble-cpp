#ifndef NIBBLE_COMPUTER_H
#define NIBBLE_COMPUTER_H

#include <map>
#include <vector>

#include "Helper.hpp"
#include "NibbleGUI.h"

enum ComputerAppTypes {
	COMPUTER_APP_TERMINAL,
	COMPUTER_APP_EDITOR
};

enum ComputerAppState {
	COMPUTER_APP_STATE_STARTING, // Initialisation process
	COMPUTER_APP_STATE_FOCUSED, // Visible AND active AND running
	COMPUTER_APP_STATE_SUSPENDED, // Visible AND NOT active AND running
	COMPUTER_APP_STATE_MINIMIZED, // NOT visible AND NOT active AND running
	COMPUTER_APP_STATE_CLOSING, // Flag app to close
};

struct ComputerApplication {
	void* application;
	int type;
	int state;
};

class NibbleComputer {
	public:
		NibbleComputer(ProgramState* program_state);
		NibbleComputer() = default;

		void input();
		void update();
		void draw();

		void appInput(ComputerApplication* app);
		void appUpdate(ComputerApplication* app);
		void appDraw(ComputerApplication* app);

		void startApplication(int app_type, std::map<std::string, void*> args);

		void setComputerMode(int mode);
		void setComputerZoom(float zoom);
		int getComputerMode();
		float getComputerZoom();

		const int getScreenWidth() { return screen.texture.width; }
		const int getScreenHeight() { return screen.texture.height; }

	private:
		//void drawComputer();

		ProgramState* program_state;
		NibbleGUI ngui;

		ComputerApplication** apps;
		int max_app_count = 50;
		int apps_count = 0;

		int computer_mode = COMPUTER_MODE_ACTIVE;

		Texture2D background_texture;

		RenderTexture2D screen;
		int screen_resolution_x = 624;
		int screen_resolution_y = 468;

		float zoom_scale = 2.0f;
};


#endif
