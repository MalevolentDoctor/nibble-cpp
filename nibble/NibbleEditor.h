#ifndef NIBBLEEDITOR_H
#define NIBBLEEDITOR_H

#include<string>
#include<vector>

#include "Helper.hpp"
#include "NibbleKeyboard.h"
#include "NibbleComputer.h"
#include "NibbleGUI.h"

class NibbleEditor {
	public:
		NibbleEditor(NibbleComputer* _computer);
		NibbleEditor() = default;

		void input();
		void update();
		void draw();

	private:
		// Draw elements
		void drawCursor();

		// Key strokes
		void keyLeftArrow();
		void keyRightArrow();
		void keyUpArrow();
		void keyDownArrow();

		void keyBackspace();
		void keyDelete();
		void keyEnter();

		NibbleGUI ngui;
		NibbleKeyboard nkeyboard;
		NibbleComputer* computer;

		std::string file_name = "";
		bool file_saved = false;

		std::vector<std::string> text;

		Rectangle screen_border;
		Rectangle screen_buffer;

		int vspacing = 1;
		int screen_text_height;
		int screen_text_width;

		std::vector<std::string> command_buffer;

		int screen_scroll = 0;			// First line to draw to the terminal

		Cursor cursor = { 0, 0, 6, 10 };
		int cursor_rest_x = 0;

		int pre_line_offset;
};

#endif

