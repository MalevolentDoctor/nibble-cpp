#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)
#include "raylib/raylib.h"

#pragma warning(pop)

#include "Helper.hpp"
#include "MainMenu.h"

int main() {
    // initialises program state, initially "starting"
    ProgramState program_state;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1600, 900, "Nibble - A Microcomputer Simulator");

    SetExitKey(KEY_NULL);

    MainMenu main_menu(&program_state);
    

    while (!(program_state.state == PROGRAM_STATE_SHOULD_CLOSE)) {

        if (WindowShouldClose()) {
            program_state.state = PROGRAM_STATE_SHOULD_CLOSE;
        }

        if (program_state.state == PROGRAM_STATE_STARTING) {
            // Perform startup procedure

            program_state.state = PROGRAM_STATE_RUNNING;
        }

        if (program_state.state == PROGRAM_STATE_RUNNING) {

            BeginDrawing();
            ClearBackground(RAYWHITE);

            main_menu.draw();

            EndDrawing();
        }
    }

    CloseWindow();

    return 0;
}