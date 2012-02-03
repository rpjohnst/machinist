#include "sprite.h"

namespace machinist {

Sprite::Sprite(Image& image, const Rect<int>& sub, int frames) :
	image(image),
	pos(0, 0, sub.width / frames, sub.height),
	x(sub.left), y(sub.top), frames(frames) {

}

void Sprite::draw(int x, int y, int angle, int frame) {
	glPushMatrix();	
	
	glTranslatef(x, y, 0);
	glRotatef(angle, 0, 0, -1);
	
	Rect<float> sub(
		(float)(x + frame % frames * pos.width) / image.get_width(),
		(float)y / image.get_width(),
		(float)pos.width / image.get_width(),
		(float)pos.height / image.get_height()
	);
	image.draw(pos, sub);
	
	glPopMatrix();
	
	frame = frame + 1 % frames;
}

}
