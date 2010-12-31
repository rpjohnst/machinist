#include "sprite.h"

namespace machinist {

void Sprite::draw() {
	texture.bind();
	
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex2i(0, 0);
		
		glTexCoord2f(1, 0);
		glVertex2i(64, 0);
		
		glTexCoord2f(1, 1);
		glVertex2i(64, 64);
		
		glTexCoord2f(0, 1);
		glVertex2i(0, 64);
	glEnd();
	
	/*static GLfloat vertices[] = {
		0, 0,
		64, 0,
		64, 64,
		0, 64
	};
	static GLfloat texcoords[] = {
		0, 0,
		1, 0,
		1, 1,
		0, 1
	};
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
	glDrawArrays(GL_QUADS, 0, 8);
	glDisableClientState(GL_VERTEX_ARRAY);*/
}

}
