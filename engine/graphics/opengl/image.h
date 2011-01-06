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
	
	int get_width() { return width; }
	int get_height() { return height; }

private:
	int width, height;
	GLuint texture;
};

}

#endif
