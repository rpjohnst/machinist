#ifndef PLATFORM_XLIB_WINDOW_H
#define PLATFORM_XLIB_WINDOW_H

// this file should not be included by the user; use <platform/window.h> instead

#include <platform/window.h>
#include <platform/clock.h>
#include <X11/Xlib.h>
#include <GL/glx.h>

namespace machinist {

class exception {};

class Window : protected WindowBase {
protected:
	Window(int width, int height);
	~Window();
	
	bool handle_events();
	void swap_buffers();
	
	void set_framerate(int);
	double get_frame_time();

private:
	static Mouse::Button map_button(int);
	static int map_key(KeySym);
	
	Display *display;
	::Window window;
	GLXContext glc;
	
	int width, height;
	int framerate;
	Clock clock;
	
	double frame;
};

inline void Window::set_framerate(int fps) {
	framerate = fps;
}

inline double Window::get_frame_time() {
	return frame;
}

}

#endif
