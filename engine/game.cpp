#include "game.h"
#include <IL/il.h>

namespace machinist {

Game::Game() : Window(640, 480) {
	glEnable(GL_TEXTURE_2D);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 640, 480, 0, -1, 1);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glClearColor(1.0, 0.0, 0.0, 1.0);
	
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

Game::~Game() {
	delete sprite;
	delete image;
}

void Game::run() {
	running = true;
	while (running) {
		if (!handle_events())
			running = false;
		
		draw();
		swap_buffers();
	}
}

void Game::draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	sprite->draw();
}

}
