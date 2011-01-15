#include "image.h"

namespace machinist {

// TODO: adjust image data format for final usage

Image::Image(int w, int h, void* data) : width(w), height(h) {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glTexImage2D(
		GL_TEXTURE_2D, 0,
		3, width, height,
		0, GL_RGB, GL_UNSIGNED_BYTE,
		data
	);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
}

void Image::draw(const Rect<int>& pos, const Rect<float>& sub) {
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	/*
	 * these arrays need to be the same type or we confuse OpenGL into making
	 * strange white triangles and blank screens
	 */
	GLfloat vertices[] = {
		pos.left, pos.top,
		pos.left + pos.width, pos.top,
		pos.left + pos.width, pos.top + pos.height,
		pos.left, pos.top + pos.height
	};
	
	GLfloat texcoords[] = {
		sub.left, sub.top + sub.height,
		sub.left + sub.width, sub.top + sub.height,
		sub.left + sub.width, sub.top,
		sub.left, sub.top
	};
	
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
	glDrawArrays(GL_QUADS, 0, 8);
	
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

}
