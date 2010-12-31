#include "window.h"

namespace machinist {

Window::Window() {
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
	win = XCreateWindow(
		display, root, 0, 0, 640, 480, 0, vi->depth, InputOutput, vi->visual,
		CWColormap | CWEventMask, &swa
	);
	
	wm_delete = XInternAtom(display, "WM_DELETE_WINDOW", False);
	Atom prots[] = { wm_delete };
	XSetWMProtocols(display, win, prots, 1);
	
	// rendering context
	glc = glXCreateContext(display, vi, NULL, GL_TRUE);
	glXMakeCurrent(display, win, glc);
	
	// show the window
	XMapWindow(display, win);
	glViewport(0, 0, 640, 480);
}

Window::~Window() {
	glXMakeCurrent(display, None, NULL);
	glXDestroyContext(display, glc);
	XDestroyWindow(display, win);
	XCloseDisplay(display);
}

bool Window::handle_events() {
	while (XPending(display)) {
		XEvent event;
		XNextEvent(display, &event);
	
		KeySym key;
		switch (event.type) {
		case ClientMessage:
			if (event.xclient.data.l[0] == wm_delete)
				return false;
			break;
		
		case KeyPress:
			key = XLookupKeysym(&event.xkey, 0);
			key_press(key);
			break;
		case KeyRelease:
			key = XLookupKeysym(&event.xkey, 0);
			key_release(key);
			break;
		
		/*case ButtonPress:
			button_press();
			break;
		case ButtonRelease:
			button_release();
			break;*/
		}
	}
	
	return true;
}

}
