#include "window.h"

namespace machinist {

Window::Window(int w, int h) : width(w), height(h) {
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
		ButtonPressMask | ButtonReleaseMask |
		PointerMotionMask;
	window = XCreateWindow(
		display, root, 0, 0, width, height, 0, vi->depth, InputOutput, vi->visual,
		CWColormap | CWEventMask, &swa
	);
	
	// fix the brain-dead default event setup to actually recieve quit events
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
		
		switch (event.type) {
		case ClientMessage: {
			Atom wm_delete_window = XInternAtom(display, "WM_DELETE_WINDOW", True);
			if (event.xclient.data.l[0] == wm_delete_window)
				return false;
			break;
		}
		
		case KeyPress: {
			KeySym sym = XLookupKeysym(&event.xkey, 0);
			int key = map_key(sym);
			
			if (!input().keystate[key]) {
				input().keystate[key] = true;
				key_press(key);
			}
			break;
		}
		case KeyRelease: {
			/*
			 * X gives us KeyRelease events during auto-repeat, unlike Windows
			 * which just sends WM_KEYDOWN until the key is *actually* released.
			 */
			if (XEventsQueued(display, QueuedAfterReading)) {
				XEvent next;
				XPeekEvent(display, &next);
				if (
					next.type == KeyPress &&
					next.xkey.time == event.xkey.time &&
					next.xkey.keycode == event.xkey.keycode
				)
					break;
			}
			
			KeySym sym = XLookupKeysym(&event.xkey, 0);
			int key = map_key(sym);
			
			if (input().keystate[key]) {
				input().keystate[key] = false;
				key_release(key);
			}
			break;
		}
		
		case ButtonPress: {
			Mouse::Button button = map_button(event.xbutton.button);
			input().mousestate[button] = true;
			button_press(
				button,
				event.xbutton.x,
				event.xbutton.y
			);
			break;
		}
		case ButtonRelease: {
			Mouse::Button button = map_button(event.xbutton.button);
			input().mousestate[button] = false;
			button_release(
				button, 
				event.xbutton.x,
				event.xbutton.y
			);
			break;
		}
		case MotionNotify:
			input().mouse = Vector<int>(event.xmotion.x, event.xmotion.y);
			mouse_move(event.xmotion.x, event.xmotion.y);
			break;
		}
	}
	
	return true;
}

Mouse::Button Window::map_button(int button) {
	switch (button) {
		case Button1: return Mouse::Left;
		case Button2: return Mouse::Right;
		case Button3: return Mouse::Middle;
		default: return Mouse::NoButton;
	}
}

int Window::map_key(KeySym sym) {
	if (sym < 256) {
		KeySym lower, key;
		XConvertCase(sym, &lower, &key);
		return key;
	}
	
	switch (sym) {
		case XK_Left: return Key::Left;
		case XK_Up: return Key::Up;
		case XK_Right: return Key::Right;
		case XK_Down: return Key::Down;
		
		case XK_Tab: return Key::Tab;
		case XK_Return: return Key::Enter;
		case XK_Shift_L: case XK_Shift_R: return Key::Shift;
		case XK_Control_L: case XK_Control_R: return Key::Control;
		case XK_Alt_L: case XK_Alt_R: return Key::Alt;
		
		case XK_KP_0: return Key::Num0;
		case XK_KP_1: return Key::Num1;
		case XK_KP_2: return Key::Num2;
		case XK_KP_3: return Key::Num3;
		case XK_KP_4: return Key::Num4;
		case XK_KP_5: return Key::Num5;
		case XK_KP_6: return Key::Num6;
		case XK_KP_7: return Key::Num7;
		case XK_KP_8: return Key::Num8;
		case XK_KP_9: return Key::Num9;
		
		case XK_KP_Multiply: return Key::Multiply;
		case XK_KP_Add: return Key::Add;
		case XK_KP_Subtract: return Key::Subtract;
		case XK_KP_Decimal: return Key::Decimal;
		case XK_KP_Divide: return Key::Divide;
		
		case XK_F1: return Key::F1;
		case XK_F2: return Key::F2;
		case XK_F3: return Key::F3;
		case XK_F4: return Key::F4;
		case XK_F5: return Key::F5;
		case XK_F6: return Key::F6;
		case XK_F7: return Key::F7;
		case XK_F8: return Key::F8;
		case XK_F9: return Key::F9;
		case XK_F10: return Key::F10;
		case XK_F11: return Key::F11;
		case XK_F12: return Key::F12;
		
		case XK_BackSpace: return Key::Backspace;
		case XK_Escape: return Key::Escape;
		case XK_Home: return Key::Home;
		case XK_End: return Key::End;
		case XK_Page_Up: return Key::PageUp;
		case XK_Page_Down: return Key::PageDown;
		case XK_Delete: return Key::Delete;
		case XK_Insert: return Key::Insert;
		
		default: return Key::NoKey;
	}
}

}
