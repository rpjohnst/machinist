#ifndef GRAPHICS_SPRITE_H
#define GRAPHICS_SPRITE_H

#if GRAPHICS_OPENGL
#	include <graphics/opengl/texture.h>
#endif

namespace machinist {

class Sprite {
public:
	Sprite(Texture& t) : texture(t) {}
	void draw();

private:
	Texture& texture;
};

}

#endif
