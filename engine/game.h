#ifndef GAME_H
#define GAME_H

#include <platform/window.h>
#include <graphics/sprite.h>

namespace machinist {

class Game : private Window {
public:
	Game();
	~Game();
	
	void run();
	
private:
	void quit() { running = false; }
	void draw();
	
	bool running;
	Image *image;
	Sprite *sprite;
};

}

#endif
