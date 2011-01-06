#include "window.h"
#include <cstring>

namespace machinist {

Window::Window(int width, int height) : WindowBase(width, height) {
	display = XOpenDisplay(NULL);
	::Window root = DefaultRootWindow(display);
	
	// visual
	GLint att[] = { GLX_RGBA, GLX_DOUBLEBUFFER, None };
	XVisualInfo *vi = glXChooseVisual(display, 0, att);
	
	// window
	XSetWindowAttributes swa;
	swa.colormap = XCreateColormap(display, root, vi->visual, AllocNone);
	swa.event_mask = ExposureMask |
		KeyPressMask | KeyReleaseMask |
		ButtonPressMask | ButtonReleaseMask;
	window = XCreateWindow(
		display, root, 0, 0, width, height, 0, vi->depth, InputOutput, vi->visual,
		CWColormap | CWEventMask, &swa
	);
	
	// receive close event which is off by default for some reason
	Atom wm_protocols[] = { XInternAtom(display, "WM_DELETE_WINDOW", False) };
	XSetWMProtocols(display, window, wm_protocols, 1);
	
	// rendering context
	glc = glXCreateContext(display, vi, NULL, GL_TRUE);
	glXMakeCurrent(display, window, glc);
	
	// show the window
	XMapWindow(display, window);
	XWindowAttributes xwa;
	XGetWindowAttributes(display, window, &xwa);
	glViewport(0, 0, xwa.width, xwa.height);
}

Window::~Window() {
	glXMakeCurrent(display, None, NULL);
	glXDestroyContext(display, glc);
	XDestroyWindow(display, window);
	XCloseDisplay(display);
}

bool Window::handle_events() {
	while (XPending(display)) {
		XEvent event;
		XNextEvent(display, &event);
	
		KeySym key;
		switch (event.type) {
		case ClientMessage: {
			Atom wm_delete_window = XInternAtom(display, "WM_DELETE_WINDOW", True);
			if (event.xclient.data.l[0] == wm_delete_window)
				return false;
			break;
		}
		
		case KeyPress:
			key = XLookupKeysym(&event.xkey, 0);
			key_press(key);
			break;
		case KeyRelease:
			key = XLookupKeysym(&event.xkey, 0);
			key_release(key);
			break;
		
		case ButtonPress:
			button_press(
				event.xbutton.button,
				event.xbutton.x,
				event.xbutton.y
			);
			break;
		case ButtonRelease:
			button_release(
				event.xbutton.button, 
				event.xbutton.x,
				event.xbutton.y
			);
			break;
		}
	}
	
	return true;
}

}
