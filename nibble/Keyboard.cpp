#include <CodeAnalysis/Warnings.h>
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS)

#include<string>

#include "raylib/raylib.h"

#pragma warning(pop)

#include "Keyboard.h"

NibbleKeyboard* NibbleKeyboard::getInstance() {
	if (instance_pointer == nullptr) {
		instance_pointer = new NibbleKeyboard();
	}

	return instance_pointer;
}

void NibbleKeyboard::updateInputs() {
	// Update the queue, doing it this way will leave the first pressed at the end of the queue.
	int keycode = 0;
	while ((keycode = GetKeyPressed())) {
		key_pressed_queue.push_back(keycode);
	}

	repeat_timer -= GetFrameTime();

	// If we must have pressed a new key, overwriting the currently repeating key
	if (key_pressed_queue.size() > 0) {
		repeat_key = key_pressed_queue.at(0);
		repeat_timer = repeat_delay;
	}

	// Check if the repeat key was released (or use up)
	if (IsKeyReleased(repeat_key)) {
		repeat_key = 0;
	}

	// If no other key was pressed and repeat timer has reached zero
	if (repeat_timer <= 0 && repeat_key > 0) {
		key_pressed_queue.push_back(repeat_key);
		repeat_timer = repeat_interval;
	}
}

std::vector<int> NibbleKeyboard::getInputQueue() {
	return key_pressed_queue;
}

void NibbleKeyboard::clearInputs() {
	key_pressed_queue.clear();
}

std::string NibbleKeyboard::getStringFromKeycode(int keycode, bool consider_modifiers) {
	// Just return the character without consideration of modifier keys
	if (!consider_modifiers) return(std::string(1, (char)keycode));

	// Consider modifier keys
	bool caps_lock = IsKeyDown(KEY_CAPS_LOCK);
	bool shift = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
	int key_index = keycode - 32;

	// Alphabetic characters
	if ((keycode >= 65 && keycode <= 90) || (keycode >= 97 && keycode <= 122)) {
		return(std::string(1, (caps_lock != shift) ? (char)keycode : (char)(keycode + unicode_shift_offset[key_index])));
	}
	// Non-Alphabetic characters
	else {
		return(std::string(1, (shift) ? (char)(keycode + unicode_shift_offset[key_index]) : (char)keycode));
	}

	return NULL;
}