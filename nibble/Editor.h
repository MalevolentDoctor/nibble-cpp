#ifndef NIBBLEEDITOR_H
#define NIBBLEEDITOR_H

#include<string>
#include<vector>

#include "Helper.hpp"
#include "Keyboard.h"
#include "Computer.h"
#include "EditorTerminal.h"
#include "GUI.h"




// running ready blocked stopped ended
class NibbleEditor {
	public:
		NibbleEditor(NibbleComputer* _computer);
		NibbleEditor() = default;

		void input();
		void update();
		void draw();

		NibbleComputer* computer;

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
		void keyPageDown();
		void keyPageUp();
		void keyEnd();
		void keyHome();
		void keyBackspace();
		void keyDelete();
		void keyEnter();
		void keyEscape();

		NibbleGUI* ngui;
		NibbleKeyboard* nkeyboard;
		NibbleEditorTerminal* terminal;

		std::string file_name = "";
		bool file_saved = false;

		std::vector<std::string> text;

		IntRectangle border;
		IntRectangle buffer;

		int vspacing = 1;
		int screen_text_height;
		int screen_text_width;

		int screen_scroll = 0;			// First line to draw to the terminal
		int line_indent = 0;
		int cursor_x_cache = 0;

		Cursor cursor = { 0, 0, 6, 10 };

		float terminal_size = 0.2f;
		bool terminal_active = false;
};

#endif

