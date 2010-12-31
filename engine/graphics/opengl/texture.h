#ifndef GRAPHICS_OPENGL_TEXTURE_H
#define GRAPHICS_OPENGL_TEXTURE_H

#include <GL/gl.h>

namespace machinist {

class Texture {
public:
	Texture(int width, int height, void* data);
	void bind() { glBindTexture(GL_TEXTURE_2D, texture); }

private:
	GLuint texture;
};

}

#endif
