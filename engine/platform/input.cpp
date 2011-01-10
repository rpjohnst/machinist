#include "input.h"

namespace machinist {

Input::Input() {
	std::fill_n(keystate, (int)Key::Count, false);
	std::fill_n(last_keystate, (int)Key::Count, false);
	std::fill_n(mousestate, (int)Mouse::Count, false);
	std::fill_n(last_mousestate, (int)Mouse::Count, false);
}

void Input::swap_buffers() {
	std::copy(keystate, keystate + Key::Count, last_keystate);
	std::copy(mousestate, mousestate + Mouse::Count, last_mousestate);
}

}
