#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib/raylib.h"

#pragma warning(pop)

#include "Helper.hpp"
#include "MainMenu.h"
#include "Workbench.h"
#include "Keyboard.h"

NibbleKeyboard* NibbleKeyboard::instance_pointer = nullptr;

int main() {
    // initialises program state, initially "starting"
    ProgramState program_state;

    SetTraceLogLevel(4);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1920, 1080, "Nibble - A Microcomputer Simulator");

    SetExitKey(KEY_NULL);

    // Declare objects
    MainMenu main_menu(&program_state);
    NibbleWorkbench workbench(&program_state);
    NibbleKeyboard* keyboard = NibbleKeyboard::getInstance();
    

    while (!(program_state.state == PROGRAM_STATE_SHOULD_CLOSE)) {
        // Pre step
        if (WindowShouldClose()) {
            program_state.state = PROGRAM_STATE_SHOULD_CLOSE;
        }

        // Perform startup procedure
        if (program_state.state == PROGRAM_STATE_STARTING) {
            program_state.state = PROGRAM_STATE_RUNNING;
        }

        // Main loop operations
        if (program_state.state == PROGRAM_STATE_RUNNING) {
            keyboard->updateInputs();


            if (program_state.mode == PROGRAM_MODE_WORKBENCH) {
                workbench.input(); 
                workbench.update(GetFrameTime());
            }

            BeginDrawing();
            ClearBackground(RAYWHITE);

            if (program_state.mode == PROGRAM_MODE_MAIN_MENU) { main_menu.draw(); }
            if (program_state.mode == PROGRAM_MODE_WORKBENCH) { workbench.draw(); }


            EndDrawing();

            keyboard->clearInputs();
        }
    }

    CloseWindow();

    return 0;
}