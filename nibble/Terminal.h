#ifndef NIBBLETERMINAL_H
#define NIBBLETERMINAL_H

#include "raylib/raylib.h"
#include<vector>
#include<string>

#include "Helper.hpp"
#include "Keyboard.h"
#include "GUI.h"

class NibbleTerminal {
	public:
		NibbleTerminal();

		void input();
		void update();
		void draw();

		bool active = true;
		bool visible = true;

		void setBackgroundColour(Color colour);
		void setTextColour(Color colour);
		IntRectangle getWindowRec() { return window; };
		

	protected:
		void init();
		void setWindowSize(int x, int y);
		void setWindowPosition(int w, int h);
		
		

		// Draw elements
		void drawCursor();

		// Execute key strokes
		void keyBackspace();
		void keyDelete();
		void keyEnter();
		void keyLeft();
		void keyRight();
		void keyUp();
		void keyDown();
		
		// Interpret commands
		std::string getCommand(std::vector<std::string> split_input);
		std::vector<std::string> getArguments(std::vector<std::string> split_input);
		std::vector<std::string> getFlags(std::vector<std::string> split_input);
		virtual void interpretCommand(std::string command, std::vector<std::string> args, std::vector<std::string> flags, bool override_checks);

		void printToTerminal(std::string string);
		void printToTerminal(std::vector<std::string> strings);
		void scrollToCursor();

		void setLinePrompt(std::string prompt);


		NibbleGUI* ngui;
		NibbleKeyboard* nkeyboard;
		
		IntRectangle buffer;

		IntVector2 text_res;

		IntRectangle window;

		int vspacing = 1;

		std::vector<std::string> text;
		std::vector<std::string> command_buffer;

		int screen_scroll = 0;			// First line to draw to the console

		// Command buffer
		int buffer_selector = 0;	// Index to go through command buffer

		Cursor cursor = { 0, 0, 6, 10 };

		std::string line_prompt;
		int line_prompt_offset;

		Color background_colour = LIGHTGRAY;
		Color text_colour = BLACK;
};

#endif