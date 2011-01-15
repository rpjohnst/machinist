#ifndef PLATFORM_XLIB_WINDOW_H
#define PLATFORM_XLIB_WINDOW_H

// this file should not be included by the user; use <platform/window.h> instead

#include <platform/window.h>
#include <X11/Xlib.h>
#include <GL/glx.h>
#include <string>

namespace machinist {

class exception {};

class Window : protected WindowBase {
protected:
	Window(int width, int height);
	~Window();
	
	bool handle_events();
	void swap_buffers();
	void set_caption(const std::string&);

private:
	static Mouse::Button map_button(int);
	static int map_key(KeySym);
	
	Display *disp;
	::Window window;
	GLXContext glc;
};

inline void Window::swap_buffers() {
	glXSwapBuffers(disp, window);
}

inline void Window::set_caption(const std::string& caption) {
	XStoreName(disp, window, caption.c_str());
}

}

#endif
