#ifndef PLATFORM_KEYBOARD_H
#define PLATFORM_KEYBOARD_H

namespace machinist {

/*
 * these keys follow Win32's convention of mapping to ASCII values that are either
 * not available without shift or need a name (e.g. backspace)
 */
namespace Key {
enum Sym {
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
	
	Count, // keep last
};
}

}

#endif
