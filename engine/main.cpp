#include "platforms/xlib/window.h"

namespace machinist {

class Game : public XWindow {
	friend class XWindow;
	
public:
	Game() {
		glClearColor(1.0, 0.0, 0.0, 1.0);
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, 640, 480, 0, -1, 1);
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	
	void run() {
		running = true;
		while (running) {
			while (message_pending())
				handle_message<Game>();
			
			draw();
			swap_buffers();
		}
	}
	
private:
	void key_press(int key) {
		if (key == XK_Escape)
			close();
	}
	
	void key_release(int) {}
	
	void draw() {
		glClear(GL_COLOR_BUFFER_BIT);
		
		glLoadIdentity();
		
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_QUADS);
			glVertex3f(0, 0, 0);
			glVertex3f(10, 0, 0);
			glVertex3f(10, 10, 0);
			glVertex3f(0, 10, 0);
		glEnd();
	}
	
	void close() { running = false; }
	
	bool running;
};

}

int main(int argc, char* argv[]) {
	machinist::Game().run();
}
