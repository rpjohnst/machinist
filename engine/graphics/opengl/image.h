#ifndef GRAPHICS_OPENGL_TEXTURE_H
#define GRAPHICS_OPENGL_TEXTURE_H

#include <graphics/rect.h>
#include <GL/gl.h>

namespace machinist {

class Image {
public:
	Image(int width, int height, void* data);
	void draw(
		const Rect<int>& pos,
		const Rect<float>& sub = Rect<float>(0, 0, 1, 1)
	);

private:
	GLuint texture;
};

}

#endif
