#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)

#include <map>
#include <vector>
#include <string>

#include "raylib/raylib.h"

#pragma warning(pop)

#include "Helper.hpp"
#include "NibbleGUI.h"
#include "NibbleComputer.h"
#include "NibbleTerminal.h"
#include "NibbleEditor.h"


NibbleComputer::NibbleComputer(ProgramState* program_state) : program_state(program_state) {
	screen = LoadRenderTexture(screen_resolution_x, screen_resolution_y);
	ngui = NibbleGUI();

	Image background_img = LoadImage("assets/sprites/spr_desk_comp.png");
	int new_h = background_img.height * zoom_scale/4.0;
	int new_w = background_img.width * zoom_scale/4.0;
		ImageResize(&background_img, new_w, new_h);
	background_texture = LoadTextureFromImage(background_img);
	UnloadImage(background_img);

	// Terminal
	printf("Number of apps is: %d\n", apps_count);
	startApplication(COMPUTER_APP_TERMINAL, {{"computer", this}});

}

void NibbleComputer::input() {
	if (computer_mode == COMPUTER_MODE_ACTIVE) {
		for (int i = 0; i < apps_count; i++) {
			appInput(apps[i]);
		}
	}
}

void NibbleComputer::update() {

}

void NibbleComputer::draw() {
	//printf("Computer (%p) Screen from computer (draw): %dx%d\n", this, this->getScreenWidth(), this->getScreenHeight());
	Rectangle src = { 0, 0, screen.texture.width, -screen.texture.height };
	Rectangle dest = {
		GetScreenWidth() / 2 - screen_resolution_x * zoom_scale / 2,
		(GetScreenHeight() - screen_resolution_y * zoom_scale) * 0.4,
		screen.texture.width * zoom_scale,
		screen.texture.height * zoom_scale
	};

	int xx = -(background_texture.width - GetScreenWidth()) / 2;
	int yy = -(background_texture.height - GetScreenHeight()) / 2 + 215;
	DrawTexture(background_texture, xx, yy, WHITE);

	// Draw screen contents
	BeginTextureMode(screen);
	ClearBackground(RAYWHITE);

	DrawRectangle(0, 0, screen.texture.width, screen.texture.height, GRAY);

	for (int i = 0; i < apps_count; i++) {
		appDraw(apps[i]);
	}

	EndTextureMode();

	DrawTexturePro(screen.texture, src, dest, { 0, 0 }, 0.0f, WHITE);
}

void NibbleComputer::startApplication(int app_type, std::map<std::string, void*> args) {
	ComputerApplication** tmp_apps = (ComputerApplication**)realloc(apps, (apps_count + 1) * sizeof(ComputerApplication*));

	// Check that the memory was reallocated successfully, if not, print an error to stderr. This should not happen in normal use.
	if (!tmp_apps) {
		// Error: failed to reallocate memory
		fprintf(stderr, "NibbleComputer::startApplication: Failed to reallocate memory for computer application array.\n");
	}
	else {
		apps = tmp_apps;

		// Check that the maximum number of applications open has not exceeded the limit
		if (apps_count < max_app_count) {

			apps[apps_count] = new ComputerApplication();

			// Check that the memory for the application itself was initialised successfully
			if (apps[apps_count]) {

				// Open the appropriate application depending on the app_type enum value
				switch (app_type) {
				case COMPUTER_APP_TERMINAL:
					apps[apps_count]->application = new NibbleTerminal((NibbleComputer*)(args["computer"]));
					break;
				case COMPUTER_APP_EDITOR:
					apps[apps_count]->application = new NibbleEditor((NibbleComputer*)(args["computer"]));
					break;
				}

				// If so, finish configuring the app data.
				if (apps[apps_count]->application) {
					apps[apps_count]->type = app_type;
					apps[apps_count]->state = COMPUTER_APP_STATE_FOCUSED;

					// If the application has been opened as focused, then minimize all other apps
					for (int i = 0; i < apps_count; i++) {
						apps[i]->state = COMPUTER_APP_STATE_MINIMIZED;
					}
					printf("Initialised new app type %d at 0x%p from 0x%p\n", app_type, apps[apps_count]->application, this);
					apps_count++;
					printf("There are %d apps open\n", apps_count);

				}
				else {
					fprintf(stderr, "NibbleComputer::startApplication: Failed to allocate memory for application class\n");
				}
			}
			else {
				fprintf(stderr, "NibbleComputer::startApplication: Failed to allocate memory for app info\n");
			}
		}
		else {
			fprintf(stderr, "NibbleComputer::startApplication: Cannot open application: too many applications open\n");
		}		
	}
}

void NibbleComputer::appInput(ComputerApplication* app) {
	if (app->state == COMPUTER_APP_STATE_FOCUSED) {
		switch (app->type) {
		case COMPUTER_APP_TERMINAL:
			((NibbleTerminal*)(app->application))->input();
			break;
		case COMPUTER_APP_EDITOR:
			((NibbleEditor*)(app->application))->input();
			break;
		}
	}
}

void NibbleComputer::appDraw(ComputerApplication* app) {
	if (app->state == COMPUTER_APP_STATE_FOCUSED || app->state == COMPUTER_APP_STATE_SUSPENDED) {
		switch (app->type) {
		case COMPUTER_APP_TERMINAL:
			((NibbleTerminal*)(app->application))->draw();
			break;
		case COMPUTER_APP_EDITOR:
			((NibbleEditor*)(app->application))->draw();
			break;
		}
	}
}

void NibbleComputer::appUpdate(ComputerApplication* app) {
	if (app->state == COMPUTER_APP_STATE_FOCUSED || app->state == COMPUTER_APP_STATE_SUSPENDED || app->state == COMPUTER_APP_STATE_MINIMIZED) {
		switch (app->type) {
		case COMPUTER_APP_TERMINAL:
			((NibbleTerminal*)(app->application))->update();
			break;
		case COMPUTER_APP_EDITOR:
			((NibbleEditor*)(app->application))->update();
			break;
		}
	}
}

void NibbleComputer::setComputerMode(int mode) { computer_mode = mode; }
void NibbleComputer::setComputerZoom(float zoom) { zoom_scale = zoom; }

int NibbleComputer::getComputerMode() { return computer_mode; }
float NibbleComputer::getComputerZoom() { return zoom_scale; }
