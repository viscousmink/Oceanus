#include "Renderable.h"

void Renderable::genVao()
{
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
}

GLuint Renderable::getVaoID()
{
	return vaoID;
}
