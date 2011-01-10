#ifndef PLATFORM_KEYBOARD_H
#define PLATFORM_KEYBOARD_H

#include <graphics/vector.h>
#include <algorithm>

namespace machinist {

namespace Mouse {
enum Button {
	NoButton,
	
	Left, Right, Middle,
	
	Count // keep last
};
}

/*
 * these keys follow Win32's convention of mapping to ASCII values that are either
 * not available without shift or need a name (e.g. backspace)
 */
namespace Key {
enum Code {
	NoKey, // note: I would use None but XLib has a macro with that name >(
	
	Left = 37, Up, Right, Down,
	
	Tab = 9,
	Enter = 13,
	Shift = 16,
	Control = 17,
	Alt = 18,
	Space = 32,
	
	Num0 = 96,
	Num1 = 97,
	Num2 = 98,
	Num3 = 99,
	Num4 = 100,
	Num5 = 101,
	Num6 = 102,
	Num7 = 103,
	Num8 = 104,
	Num9 = 105,
	
	Multiply = 106,
	Add = 107,
	Subtract = 109,
	Decimal = 110,
	Divide = 111,
	
	F1 = 112, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
	
	Backspace = 8,
	Escape = 27,
	PageUp = 33,
	PageDown = 34,
	End = 35,
	Home = 36,
	Insert = 45,
	Delete = 46,
	
	LControl = 162,
	RControl = 163,
	LAlt = 164,
	RAlt = 165,
	
	Count // keep last
};
}

class Input {
	friend class Window;
	
public:
	Input();
	
	void swap_buffers();
	
	bool key_down(int key);
	bool key_pressed(int key);
	bool key_released(int key);
	
	bool button_down(int button);
	bool button_pressed(int button);
	bool button_released(int button);
	
	int mouse_x();
	int mouse_y();

private:
	bool keystate[Key::Count], last_keystate[Key::Count];
	bool mousestate[Mouse::Count], last_mousestate[Mouse::Count];
	
	Vector<int> mouse;
};

inline bool Input::key_down(int key) {
	return keystate[key];
}

inline bool Input::key_pressed(int key) {
	return keystate[key] == true && last_keystate[key] == false;
}

inline bool Input::key_released(int key) {
	return keystate[key] == false && last_keystate[key] == true;
}

inline bool Input::button_down(int button) {
	return mousestate[button];
}

inline bool Input::button_pressed(int button) {
	return mousestate[button] == true && last_mousestate[button] == false;
}

inline bool Input::button_released(int button) {
	return mousestate[button] == false && last_mousestate[button] == true;
}

inline int Input::mouse_x() {
	return mouse.x;
}

inline int Input::mouse_y() {
	return mouse.y;
}

}

#endif
