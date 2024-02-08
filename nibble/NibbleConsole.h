#ifndef NIBBLECONSOLE_H
#define NIBBLECONSOLE_H

#include "raylib/raylib.h"
#include<vector>
#include<string>

#include "NibbleKeyboard.h"
#include "NibbleGUI.h"

class NibbleConsole {
	public:
		NibbleConsole(RenderTexture2D screen);
		NibbleConsole() = default;

		void input();
		void update(float dt);
		void draw();

	private:
		RenderTexture2D screen;
		NibbleGUI ngui;
		NibbleKeyboard nkeyboard;

		Rectangle internal_border = { 10.0f, 10.0f, 10.0f, 10.0f };
		Rectangle internal_buffer = { 5.0f, 5.0f, 5.0f, 5.0f };

		std::vector<std::string> text;
		std::vector<std::string> command_buffer;

		int top_line = 1;
		bool buffer_moved = false;

		int cursor_x;
		int cursor_y;

		int vspacing = 1;
		int max_lines;
		int max_chars;
		
};

#endif