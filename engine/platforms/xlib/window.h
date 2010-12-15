#ifndef PLATFORM_XLIB_WINDOW_H
#define PLATFORM_XLIB_WINDOW_H

#include <X11/Xlib.h>
#include <GL/glx.h>
#include <cstdio>

namespace machinist {

class exception {};

class XWindow {
protected:
	XWindow() {
		display = XOpenDisplay(NULL);
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
		
		wm_delete = XInternAtom(display, "WM_DELETE_WINDOW", False);
		Atom prots[] = { wm_delete };
		XSetWMProtocols(display, win, prots, 1);
		
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
	
	template <class Handler>
	void handle_message() {
		Handler& handler = *static_cast<Handler*>(this);
		
		XEvent event;
		XNextEvent(display, &event);
	
		KeySym key;
		switch (event.type) {
		case ClientMessage:
			if (event.xclient.data.l[0] == wm_delete)
				handler.close();
			break;
		
		case KeyPress:
			key = XLookupKeysym(&event.xkey, 0);
			handler.key_press(key);
			break;
		case KeyRelease:
			key = XLookupKeysym(&event.xkey, 0);
			handler.key_release(key);
			break;
		
		/*case ButtonPress:
			handler.button_press();
			break;
		case ButtonRelease:
			handler.button_release();
			break;*/
		}
	}
	
	bool message_pending() { return XPending(display); }
	
	void swap_buffers() { glXSwapBuffers(display, win); }

private:
	Atom wm_delete;
	
	Display *display;
	Window win;
	GLXContext glc;
};

}

#endif
