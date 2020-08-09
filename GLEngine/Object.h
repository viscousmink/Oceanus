#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <vector>

class Object
{
public:
	glm::mat4 getModelMatrix();
	void translateModelMatrix(float x, float y, float z);
	void genVao();

private:
	glm::mat4 Model;
	GLuint vaoID;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
};

