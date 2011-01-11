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
	
	sprite = new Sprite(*image, Rect<float>(0, 0, 128, 32), 4);
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
		
		if (input().key_down('D')) glTranslatef(1, 0, 0);
		if (input().key_down('A')) glTranslatef(-1, 0, 0);
		if (input().key_down('S')) glTranslatef(0, 1, 0);
		if (input().key_down('W')) glTranslatef(0, -1, 0);
		if (input().button_released(Mouse::Left)) quit();
		
		glLoadIdentity();
		glTranslatef(input().mouse_x(), input().mouse_y(), 0);
		
		draw();
		swap_buffers();
	}
}

void Game::draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	sprite->draw();
}

}
