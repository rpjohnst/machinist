#ifndef GRAPHICS_SPRITE_H
#define GRAPHICS_SPRITE_H

#if GRAPHICS_OPENGL
#	include <graphics/opengl/image.h>
#elif GRAPHICS_DIRECTX
#	include <graphics/directx/image.h>
#endif

namespace machinist {

class Sprite {
public:
	Sprite(Image& i);
	void draw();

private:
	Image& image;
	Rect<int> pos; // implicitly contains the origin
	/* frame */
	
	int x, y, angle;
};

}

#endif
