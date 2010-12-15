#include "platforms/xlib/window.h"
#include <GL/gl.h>

namespace machinist {

class GameWindow : public XWindow<GameWindow> {
	friend class XWindow<GameWindow>;
	
public:
	GameWindow(::Display *display) : XWindow<GameWindow>(display) {
		glClearColor(1.0, 0.0, 0.0, 1.0);
	}
	
private:
	void draw() {
		glClear(GL_COLOR_BUFFER_BIT);
	}
};

}

int main(int argc, char* argv[]) {
	// connect to display server
	Display *display = XOpenDisplay(NULL);
	if (!display) return -1;
	machinist::GameWindow(display).run();
}
