#ifndef PLATFORM_XLIB_WINDOW_H
#define PLATFORM_XLIB_WINDOW_H

#include <eventhandler.h>
#include <X11/Xlib.h>
#include <GL/glx.h>

namespace machinist {

class exception {};

class Window : virtual public EventHandler {
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
