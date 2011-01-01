#ifndef GRAPHICS_SPRITE_H
#define GRAPHICS_SPRITE_H

#if GRAPHICS_OPENGL
#	include <graphics/opengl/image.h>
#endif

namespace machinist {

class Sprite {
public:
	Sprite(Image& i) : image(i) {}
	void draw();

private:
	Image& image;
};

}

#endif
