#ifndef PLATFORM_XLIB_WINDOW_H
#define PLATFORM_XLIB_WINDOW_H

#include <eventhandler.h>
#include <X11/Xlib.h>
#include <GL/glx.h>

namespace machinist {

class exception {};

class Window : virtual public EventHandler {
protected:
	Window();
	~Window();
	
	void handle_events();
	
	void swap_buffers() { glXSwapBuffers(display, win); }

private:
	Atom wm_delete;
	
	Display *display;
	::Window win;
	GLXContext glc;
};

}

#endif
