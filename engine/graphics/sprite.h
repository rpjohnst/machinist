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
	Sprite(
		Image& i,
		const Rect<int>& sub = Rect<int>(0, 0, 1, 1),
		int frames = 1
	);
	void draw(int x, int y, int angle, int frame);

private:
	Image& image;
	Rect<int> pos; // implicitly contains the origin
	int x, y, frames;
};

}

#endif
