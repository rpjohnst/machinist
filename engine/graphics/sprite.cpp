#include "sprite.h"

namespace machinist {

void Sprite::draw() {
	static Rect<int> vertices(0, 0, 64, 64);
	static Rect<float> texcoords(0, 0, 1, 1);
	image.draw(vertices/*, texcoords*/);
}

}
