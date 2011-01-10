#include "window.h"
#include <algorithm>

namespace machinist {

WindowBase::WindowBase(int w, int h) : width(w), height(h) {
	std::fill_n(keystate, Key::Count, 0);
}

}
