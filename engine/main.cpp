/*
 * we could just do a substitution here, but scons' dependency
 * tracker gets confused by the macros... should we write our own
 * or patch scons or something?
 */
#if PLATFORM == win32
#	include <platforms/win32/window.h>
#elif PLATFORM == xlib
#	include <platforms/xlib/window.h>
#endif

namespace machinist {

class Game : private Window {
public:
	Game() {
		glViewport(0, 0, 640, 480);
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
			handle_events();
			draw();
			swap_buffers();
		}
	}
	
private:
	void key_press(int key) {
		quit();
	}
	
	void key_release(int) {}
	
	void quit() { running = false; }
	
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
	
	bool running;
};

}

int main(int argc, char* argv[]) {
	machinist::Game().run();
}
