#include "Object.h"

glm::mat4 Object::getModelMatrix()
{
	return Model;
}

void Object::translateModelMatrix(float x, float y, float z)
{
	Model[3][0] += x;
	Model[3][1] += y;
	Model[3][2] += z;
}

void Object::genVao()
{
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
}