#include "window.h"

namespace machinist {

Window::Window() {
	// window class
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "Machinist";
	RegisterClass(&wc);
	
	// window
	RECT wr;
	wr.left = 0;
	wr.right = 640;
	wr.top = 0;
	wr.bottom = 480;
	DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	AdjustWindowRectEx(&wr, WS_OVERLAPPEDWINDOW, FALSE, dwExStyle);
	hWnd = CreateWindowEx(
		dwExStyle, wc.lpszClassName, "Game",
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW,
		0, 0, wr.right - wr.left, wr.bottom - wr.top,
		NULL, NULL, GetModuleHandle(NULL), NULL
	);
	SetWindowLong(hWnd, GWL_USERDATA, reinterpret_cast<LONG>(this));
	
	// device context
	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR), 1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER | PFD_TYPE_RGBA,
		32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		16, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
	};
	HDC hDC = GetDC(hWnd);
	GLuint pf = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, pf, &pfd);
	
	// rendering context
	hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hRC);
	ReleaseDC(hWnd, hDC);
	
	// show
	ShowWindow(hWnd, SW_SHOW);
}

Window::~Window() {
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	
	DestroyWindow(hWnd);
	UnregisterClass("Machinist", GetModuleHandle(NULL));
}

bool Window::handle_events() {
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	if (msg.message == WM_QUIT)
		return false;
	else
		return true;
}

LRESULT CALLBACK Window::WndProc(
	HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam
) {
	LONG udata = GetWindowLong(hWnd, GWL_USERDATA);
	Window *handler = reinterpret_cast<Window*>(udata);
	
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	
	case WM_KEYDOWN:
		handler->key_press(wParam);
		break;
	case WM_KEYUP:
		handler->key_release(wParam);
		break;
	
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	
	return 0;
}

}
