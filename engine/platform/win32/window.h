#ifndef PLATFORM_WIN32_WINDOW_H
#define PLATFORM_WIN32_WINDOW_H

#include <eventhandler.h>
#include <windows.h>
#include <gl/gl.h>

namespace machinist {

class exception {};

class Window : virtual public EventHandler {
protected:
	Window();
	~Window();
	
	bool handle_events();
	
	void swap_buffers() { SwapBuffers(hDC); }

private:
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	
	HWND hWnd;
	HGLRC hRC;
};

}

#endif
