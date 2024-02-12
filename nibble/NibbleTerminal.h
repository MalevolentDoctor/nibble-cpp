#ifndef NIBBLETERMINAL_H
#define NIBBLETERMINAL_H

#include "raylib/raylib.h"
#include<vector>
#include<string>

#include "NibbleKeyboard.h"
#include "NibbleGUI.h"

struct Cursor {
	int x;
	int y;
};

class NibbleTerminal {
	public:
		NibbleTerminal(RenderTexture2D screen);
		NibbleTerminal() = default;

		void input();
		void update(float dt);
		void draw();

	private:
		void moveCursorLeft(int amount);
		void moveCursorRight(int amount);

		void keyBackspace();
		void keyDelete();
		void keyEnter();
		void keyUp();
		void keyDown();

		std::string getCommand(std::vector<std::string> split_input);
		std::vector<std::string> getArguments(std::vector<std::string> split_input);
		std::vector<std::string> getFlags(std::vector<std::string> split_input);

		void commandBuild();
		void commandClearTerminal();
		void commandDeleteFile();
		void commandOpenEditor();
		void commandFlashRom();
		void commandHelp();
		void commandListFiles();
		void commandLoadFile();
		void commandNewFile();
		void commandDisplayRam();
		void commandDisplayRom();
		void commandSaveFile();

		void printToTerminal(std::string string);
		void printToTerminal(std::vector<std::string> strings);
		void scrollToCursor();


		RenderTexture2D screen;
		NibbleGUI ngui;
		NibbleKeyboard nkeyboard;

		Rectangle screen_border;
		Rectangle screen_buffer;

		int vspacing = 1;
		int screen_text_height;
		int screen_text_width;

		std::vector<std::string> text;
		std::vector<std::string> command_buffer;

		int screen_scroll = 0;			// First line to draw to the console

		// Command buffer
		int buffer_selector = 0;	// Index to go through command buffer

		Cursor cursor = { 0, 0 };

		std::string pre_line;
		int pre_line_offset;

		Font font;
		Vector2 font_size;
		
};

#endif