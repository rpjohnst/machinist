#ifndef PLATFORM_XLIB_WINDOW_H
#define PLATFORM_XLIB_WINDOW_H

// this file should not be included by the user; use <platform/window.h>

#include <platform/window.h>
#include <X11/Xlib.h>
#include <GL/glx.h>

namespace machinist {

class exception {};

class Window : protected WindowBase {
protected:
	Window(int width, int height);
	~Window();
	
	bool handle_events();
	
	void swap_buffers() { glXSwapBuffers(display, window); }

private:
	int width, height;
	
	Display *display;
	::Window window;
	GLXContext glc;
};

}

#endif
