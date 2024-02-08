#ifndef NIBBLEKEYBOARD_H
#define NIBBLEKEYBOARD_H

#include<vector>
#include<string>



class NibbleKeyboard {
	public:
		NibbleKeyboard();

		void update(float dt);

		std::string getStringFromKeycode(int keycode, bool consider_modifiers);
		int getKeyPressed();

	private:
		std::vector<int> key_pressed_queue;

		int repeat_key = 0;

		float repeat_timer = 0;
		float repeat_interval = 0.2;
		float repeat_delay = 0.5;

		int unicode_shift_offset[95] = {
			0, 0, 0, 0, 0, 0, 0, -5, 0, 0, 0, 0, 16, 50, 16, 16,																				// ASCII Punctuation & Symbols (1)
			-7, -16, 14, -16, -16, -16, 40, -17, -14, -17,																						// ASCII Digits 0,1,2,...
			0, -1, 0, -18, 0, 0, 0,																												// ASCII Punctuation & Symbols (2)
			32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,								// Latin Alphabet: Uppercase
			32, 32, 32, 0, 0, 30,																												// ASCII Punctuation & Symbols (3)
			-32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32,	// Latin Alphabet: Lowercase
			0, 0, 0, 0																															// ASCII Punctuation & Symbols (4)
		};

};


#endif

