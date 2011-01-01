#include "sprite.h"

namespace machinist {

void Sprite::draw() {
	static GLfloat vertices[] = {
		0, 0,
		64, 0,
		64, 64,
		0, 64
	};
	static GLfloat texcoords[] = {
		0, 0,
		1, 0,
		1, 1,
		0, 1
	};
	image.draw(vertices, texcoords);
}

}
