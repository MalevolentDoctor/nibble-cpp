#ifndef NIBBLEKEYBOARD_H
#define NIBBLEKEYBOARD_H

#include<vector>
#include<string>



class NibbleKeyboard {
	public:

		// Remove copy/move operators
		NibbleKeyboard(const NibbleKeyboard&) = delete;
		NibbleKeyboard& operator=(const NibbleKeyboard&) = delete;
		NibbleKeyboard(NibbleKeyboard&&) = delete;
		NibbleKeyboard& operator=(NibbleKeyboard&&) = delete;

		void updateInputs();
		void clearInputs();

		std::vector<int> getInputQueue();

		static NibbleKeyboard* getInstance();
		std::string getStringFromKeycode(int keycode, bool consider_modifiers);

	private:
		NibbleKeyboard() {};

		static NibbleKeyboard* instance_pointer;
		std::vector<int> key_pressed_queue;

		int repeat_key = 0;

		float repeat_timer = 0;
		float repeat_interval = 2.0f * 1.0f/60.0f;		// Time interval between repeated keystrokes
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