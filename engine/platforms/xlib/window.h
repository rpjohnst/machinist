#ifndef PLATFORM_XLIB_WINDOW_H
#define PLATFORM_XLIB_WINDOW_H

#include <X11/Xlib.h>
#include <GL/glx.h>

namespace machinist {

class exception {};

template <class EventHandler>
class XWindow {
public:
	void run() {
		// event loop
		XEvent xev;
		while (true) {
			XNextEvent(display, &xev);
			
			switch (xev.type) {
			case KeyPress: return;
			}
			
			static_cast<EventHandler*>(this)->draw();
			glXSwapBuffers(display, win);
		}
	}

protected:
	XWindow(::Display *d) : display(d) {
		Window root = DefaultRootWindow(display);
		
		// set up graphics attributes
		GLint att[] = { GLX_RGBA, GLX_DOUBLEBUFFER, None };
		XVisualInfo *vi = glXChooseVisual(display, 0, att);
		if (!vi) throw exception();
		
		// create our window
		XSetWindowAttributes swa;
		swa.colormap = XCreateColormap(display, root, vi->visual, AllocNone);
		swa.event_mask = ExposureMask |
			KeyPressMask | KeyReleaseMask |
			ButtonPressMask | ButtonReleaseMask;
		win = XCreateWindow(
			display, root, 0, 0, 640, 480, 0, vi->depth, InputOutput, vi->visual,
			CWColormap | CWEventMask, &swa
		);
		
		// show the window
		XMapWindow(display, win);
		XStoreName(display, win, "machinist");
		
		// initialize gl context
		glc = glXCreateContext(display, vi, NULL, GL_TRUE);
		glXMakeCurrent(display, win, glc);
		
		// fix viewport
		// TODO: window resize, game cameras
		XWindowAttributes gwa;
		XGetWindowAttributes(display, win, &gwa);
		glViewport(0, 0, gwa.width, gwa.height);
	}
	
	~XWindow() {
		glXMakeCurrent(display, None, NULL);
		glXDestroyContext(display, glc);
		XDestroyWindow(display, win);
		XCloseDisplay(display);
	}

private:
	Display *display;
	Window win;
	GLXContext glc;
};

}

#endif
