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
		const Rect<float>& sub = Rect<float>(0, 0, 1, 1),
		int frames = 1
	);
	void draw();

private:
	Image& image;
	Rect<int> pos; // implicitly contains the origin
	Rect<float> frame;
	
	int x, y, angle;
};

}

#endif
