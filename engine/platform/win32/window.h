#ifndef PLATFORM_WIN32_WINDOW_H
#define PLATFORM_WIN32_WINDOW_H

// this file should not be included by the user; use <platform/window.h>

#include <platform/window.h>
#include <windows.h>
#include <GL/gl.h>

namespace machinist {

class exception {};

class Window : protected WindowBase {
protected:
	Window(int width, int height);
	~Window();
	
	bool handle_events();
	void swap_buffers();
	void set_caption(const std::string&);

private:
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	
	HWND hWnd;
	HDC hDC;
	HGLRC hRC;
};

inline void Window::swap_buffers() {
	SwapBuffers(hDC);
}

inline void Window::set_caption(const std::string& caption) {
	SetWindowText(hWnd, caption.c_str());
}

}

#endif
