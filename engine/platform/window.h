#ifndef PLATFORM_WINDOW_H
#define PLATFORM_WINDOW_H

#include <platform/input.h>
#include <platform/clock.h>
#include <string>

namespace machinist {

class WindowBase {
protected:
	WindowBase();
	
	// events
	virtual void key_press(int key) {}
	virtual void key_release(int key) {}
	
	virtual void button_press(int button, int x, int y) {}
	virtual void button_release(int button, int x, int y) {}
	virtual void mouse_move(int x, int y) {}
	
	virtual void quit() {};
	
	// platform-specific functions
	virtual bool handle_events() = 0;
	virtual void swap_buffers() = 0;
	virtual void set_caption(const std::string&) = 0;
	
	// common implementation
	void display();
	
	Input& input();
	
	void set_framerate(int);
	double get_frame_time() const;

private:
	Input state;
	
	int width, height;
	
	Clock clock;
	int framerate;
	double frame;
};

inline WindowBase::WindowBase() : width(0), height(0), framerate(0) {}

inline Input& WindowBase::input() {
	return state;
}

inline void WindowBase::set_framerate(int fps) {
	framerate = fps;
}

inline double WindowBase::get_frame_time() const {
	return frame;
}

}

/*
 * these files have to include this one for their sources, but clients have to
 * include this file, which has to include these... should be fine with include
 * guards to break the loop; not sure I really like this, but nobody should be
 * manually including these anyway
 *
 * we could just do a substitution here, but scons' dependency
 * tracker gets confused by the macros... should we write our own
 * or patch scons or something?
 */

#if PLATFORM_WIN32
#	include <platform/win32/window.h>
#elif PLATFORM_XLIB
#	include <platform/xlib/window.h>
#endif

#endif
