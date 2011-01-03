/*
 * we could just do a substitution here, but scons' dependency
 * tracker gets confused by the macros... should we write our own
 * or patch scons or something?
 */

#if PLATFORM_WIN32
#	include <platforms/win32/window.h>
#elif PLATFORM_XLIB
#	include <platforms/xlib/window.h>
#endif

#if GRAPHICS_OPENGL
#	include <graphics/opengl/image.h>
#elif GRAPHICS_DIRECTX
#	include <graphics/directx/image.h>
#endif

#include <graphics/sprite.h>

#include <IL/il.h>
#include <iostream>

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
		
		glEnable(GL_TEXTURE_2D);
		
		ilInit();
		ILuint i;
		ilGenImages(1, &i);
		ilBindImage(i);
		ilLoadImage("test.bmp");
		image = new Image(
			ilGetInteger(IL_IMAGE_WIDTH),
			ilGetInteger(IL_IMAGE_WIDTH),
			ilGetData()
		);
		ilDeleteImage(i);
		ilShutDown();
		
		sprite = new Sprite(*image);
	}
	
	~Game() {
		delete sprite;
		delete image;
	}
	
	void run() {
		running = true;
		while (running) {
			if (!handle_events())
				running = false;
			
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
		
		sprite->draw();
	}
	
	bool running;
	Image *image;
	Sprite *sprite;
};

}

int main(int argc, char* argv[]) {
	machinist::Game().run();
}
