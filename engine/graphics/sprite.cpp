#include "sprite.h"

namespace machinist {

Sprite::Sprite(Image& image) :
	image(image), pos(0, 0, image.get_width(), image.get_height()),
	x(0), y(0), angle(0) {

}

void Sprite::draw() {
	glPushMatrix();	
	
	glTranslatef(x, y, 0);
	glRotatef(angle, 0, 0, -1);
	
	image.draw(pos/*, texcoords*/);
	
	glPopMatrix();
}

}
