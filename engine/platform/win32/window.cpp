#include "window.h"

namespace machinist {

Window::Window(int width, int height) {
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
	hDC = GetDC(hWnd);
	
	// pixel format
	static PIXELFORMATDESCRIPTOR pfd = { 0 };
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	int pf = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, pf, &pfd);
	
	// rendering context
	hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hRC);
	
	// show
	ShowWindow(hWnd, SW_SHOW);
}

Window::~Window() {
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(hWnd, hDC);
	DestroyWindow(hWnd);
	UnregisterClass("Machinist", GetModuleHandle(NULL));
}

bool Window::handle_events() {
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT)
			return false;
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return true;
}

LRESULT CALLBACK Window::WndProc(
	HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam
) {
	LONG udata = GetWindowLong(hWnd, GWL_USERDATA);
	Window& handler = *reinterpret_cast<Window*>(udata);
	
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	
	case WM_KEYDOWN: {
		int key = map_key(wParam);
		if (!handler.input().keystate[key]) {
			handler.input().keystate[key] = true;
			handler.key_press(key);
		}
		break;
	}
	case WM_KEYUP: {
		int key = map_key(wParam);
		if (handler.input().keystate[key]) {
			handler.input().keystate[key] = false;
			handler.key_release(key);
		}
		break;
	}
	
	case WM_LBUTTONDOWN: {
		handler.input().mousestate[Mouse::Left] = true;
		handler.button_press(
			Mouse::Left, 
			LOWORD(lParam), // don't use GET_X/Y_LPARAM because MinGW hates them
			HIWORD(lParam)
		);
		break;
	}
	case WM_RBUTTONDOWN: {
		handler.input().mousestate[Mouse::Right] = true;
		handler.button_press(
			Mouse::Right, 
			LOWORD(lParam),
			HIWORD(lParam)
		);
		break;
	}
	case WM_MBUTTONDOWN: {
		handler.input().mousestate[Mouse::Middle] = true;
		handler.button_press(
			Mouse::Middle, 
			LOWORD(lParam),
			HIWORD(lParam)
		);
		break;
	}
	
	case WM_LBUTTONUP: {
		handler.input().mousestate[Mouse::Left] = false;
		handler.button_release(
			Mouse::Left, 
			LOWORD(lParam),
			HIWORD(lParam)
		);
		break;
	}
	case WM_RBUTTONUP: {
		handler.input().mousestate[Mouse::Right] = false;
		handler.button_release(
			Mouse::Right, 
			LOWORD(lParam),
			HIWORD(lParam)
		);
		break;
	}
	case WM_MBUTTONUP: {
		handler.input().mousestate[Mouse::Middle] = false;
		handler.button_release(
			Mouse::Middle, 
			LOWORD(lParam),
			HIWORD(lParam)
		);
		break;
	}
	
	case WM_MOUSEMOVE: {
		handler.input().mouse = Vector<int>(LOWORD(lParam), HIWORD(lParam));
		handler.mouse_move(LOWORD(lParam), HIWORD(lParam));
		break;
	}
	
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	
	return 0;
}

int Window::map_key(int key) {
	switch (key) {
		case VK_LEFT: return Key::Left;
		case VK_UP: return Key::Up;
		case VK_RIGHT: return Key::Right;
		case VK_DOWN: return Key::Down;
		
		case VK_TAB: return Key::Tab;
		case VK_RETURN: return Key::Enter;
		case VK_SHIFT: return Key::Shift;
		case VK_CONTROL: return Key::Control;
		case VK_MENU: return Key::Alt;
		
		case VK_NUMPAD0: return Key::Num0;
		case VK_NUMPAD1: return Key::Num1;
		case VK_NUMPAD2: return Key::Num2;
		case VK_NUMPAD3: return Key::Num3;
		case VK_NUMPAD4: return Key::Num4;
		case VK_NUMPAD5: return Key::Num5;
		case VK_NUMPAD6: return Key::Num6;
		case VK_NUMPAD7: return Key::Num7;
		case VK_NUMPAD8: return Key::Num8;
		case VK_NUMPAD9: return Key::Num9;
		
		case VK_MULTIPLY: return Key::Multiply;
		case VK_ADD: return Key::Add;
		case VK_SUBTRACT: return Key::Subtract;
		case VK_DECIMAL: return Key::Decimal;
		case VK_DIVIDE: return Key::Divide;
		
		case VK_F1: return Key::F1;
		case VK_F2: return Key::F2;
		case VK_F3: return Key::F3;
		case VK_F4: return Key::F4;
		case VK_F5: return Key::F5;
		case VK_F6: return Key::F6;
		case VK_F7: return Key::F7;
		case VK_F8: return Key::F8;
		case VK_F9: return Key::F9;
		case VK_F10: return Key::F10;
		case VK_F11: return Key::F11;
		case VK_F12: return Key::F12;
		
		case VK_BACK: return Key::Backspace;
		case VK_ESCAPE: return Key::Escape;
		case VK_HOME: return Key::Home;
		case VK_END: return Key::End;
		case VK_PRIOR: return Key::PageUp;
		case VK_NEXT: return Key::PageDown;
		case VK_DELETE: return Key::Delete;
		case VK_INSERT: return Key::Insert;
		
		default: return key;
	}
}

}

// allow the user to write main for all platforms
int main(int, char*[]);
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	return main(__argc, __argv);
}
