#include "sprite.h"

namespace machinist {

Sprite::Sprite(Image& image, const Rect<int>& sub, int frames) :
	image(image),
	pos(0, 0, sub.width / frames, sub.height),
	frame(
		0, 0,
		(float)pos.width / image.get_width(),
		(float)pos.height / image.get_height()
	),
	x(0), y(0), angle(0) {

}

void Sprite::draw() {
	glPushMatrix();	
	
	glTranslatef(x, y, 0);
	glRotatef(angle, 0, 0, -1);
	
	image.draw(pos, frame);
	
	glPopMatrix();
	
	frame.left += (float)pos.width / image.get_width();
	if (frame.left > (float)(image.get_width() - pos.width) / image.get_width())
		frame.left = 0;
}

}
