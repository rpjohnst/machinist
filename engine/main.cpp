#include <X11/Xlib.h>
#include <GL/glx.h>
#include <cstdio>

namespace machinist {

class exception {};

class GameWindow {
public:
	GameWindow(::Display *d) : display(d) {
		Window root = DefaultRootWindow(display);
		
		// set up graphics attributes
		GLint att[] = { GLX_RGBA, GLX_DOUBLEBUFFER, None };
		XVisualInfo *vi = glXChooseVisual(display, 0, att);
		if (!vi) throw exception();
		
		// create our window
		XSetWindowAttributes swa;
		swa.colormap = XCreateColormap(display, root, vi->visual, AllocNone);
		swa.event_mask = ExposureMask | KeyPressMask;
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
	}
	
	~GameWindow() {
		glXMakeCurrent(display, None, NULL);
		glXDestroyContext(display, glc);
		XDestroyWindow(display, win);
		XCloseDisplay(display);
	}
	
	void run() {
		// event loop
		XEvent xev;
		while (true) {
			XNextEvent(display, &xev);
			
			switch (xev.type) {
			case Expose:
				XWindowAttributes gwa;
				XGetWindowAttributes(display, win, &gwa);
				glViewport(0, 0, gwa.width, gwa.height);
				glClearColor(1.0, 1.0, 1.0, 1.0);
				glClear(GL_COLOR_BUFFER_BIT);
				glXSwapBuffers(display, win);
				break;
			
			case KeyPress:
				return;
			}
		}
	}

private:
	Display *display;
	Window win;
	GLXContext glc;
};

}

int main(int argc, char* argv[]) {
	// connect to display server
	Display *display = XOpenDisplay(NULL);
	if (!display) return -1;
	machinist::GameWindow(display).run();
}
