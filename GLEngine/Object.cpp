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

void Object::init(const char* obj, const char* text)
{
	Model = glm::mat4(1.0);

	bool result = loadObj(obj, vertices, uvs, normals);
	ProgramID = LoadShaders("Shaders/Vertex.txt", "Shaders/Fragment.txt");
	MatrixID = glGetUniformLocation(ProgramID, "MVP");
	Texture = loadDDS(text);
	TextureID = glGetUniformLocation(ProgramID, "myTextureSampler");

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * uvs.size(), &uvs[0], GL_STATIC_DRAW);
}

GLuint Object::getProgramID()
{
	return ProgramID;
}

GLuint Object::getMatrixID()
{
	return MatrixID;
}

GLuint Object::getTextureID()
{
	return TextureID;
}

GLuint Object::getTexture()
{
	return Texture;
}

void Object::bindBuffers()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

GLuint Object::getVerticesSize()
{
	return vertices.size();
}

