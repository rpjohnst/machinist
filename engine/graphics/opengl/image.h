#ifndef GRAPHICS_OPENGL_TEXTURE_H
#define GRAPHICS_OPENGL_TEXTURE_H

#include <GL/gl.h>

namespace machinist {

class Image {
public:
	Image(int width, int height, void* data);
	void draw(GLfloat *vertices, GLfloat *texcoords);

private:
	GLuint texture;
};

}

#endif
