#include "game.h"
#include <fstream>
#include <vector>
#include <algorithm>

namespace machinist {

std::vector<char> load_bitmap(const char *filename, int& width, int& height) {
	std::ifstream file;
	file.open(filename, std::ifstream::binary);
	if (!file.good())
		throw "could not open file";
	
	int start;
	file.seekg(10).read(reinterpret_cast<char*>(&start), 4);
	
	file.seekg(18).read(reinterpret_cast<char*>(&width), 4)
		.read(reinterpret_cast<char*>(&height), 4);
	
	int depth;
	file.seekg(28).read(reinterpret_cast<char*>(&depth), 4);
	if (depth != 24)
		throw "unsupported bit depth";
	
	std::vector<char> pixels(width * height * 3);
	file.seekg(start).read(&pixels.front(), pixels.size());
	for (int i = 0; i < width * height * 3; i += 3)
		std::swap(pixels[i], pixels[i + 2]);
	
	return pixels;
}

Game::Game() : Window(640, 480) {
	set_framerate(60);
	
	glEnable(GL_TEXTURE_2D);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 640, 480, 0, -1, 1);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glClearColor(1.0, 0.0, 0.0, 1.0);
	
	int width, height;
	std::vector<char> data = load_bitmap("test.bmp", width, height);
	image = new Image(width, height, &data.front());
	sprite = new Sprite(*image, Rect<int>(0, 0, 128, 32), 4);
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
		display();
	}
}

void Game::draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	static int i = 0;
	sprite->draw(0, 0, 0, i++);
}

}
