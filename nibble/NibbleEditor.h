#ifndef NIBBLEEDITOR_H
#define NIBBLEEDITOR_H

#include<string>
#include<vector>

#include "Helper.hpp"
#include "NibbleKeyboard.h"
#include "NibbleComputer.h"
#include "NibbleGUI.h"
// running ready blocked stopped ended
class NibbleEditor {
	public:
		NibbleEditor(NibbleComputer* _computer);
		NibbleEditor() = default;

		void input();
		void update();
		void draw();

	private:
		void updateScrollPosition();
		
		// Draw elements
		void drawCursor();
		void drawText();

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

		int screen_scroll = 0;			// First line to draw to the terminal
		int line_indent = 0;
		int cursor_x_cache = 0;

		Cursor cursor = { 0, 0, 6, 10 };
};

#endif

