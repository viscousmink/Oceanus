#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "loader.h"
#include "shaders.h"
#include "Renderable.h"
#include <cmath>
#include <ctime>
#include <cstdint>
#include <vector>

class Water : public Renderable
{
public:
	void init(const char* vert, const char* frag);
	void bindBuffers();
	GLuint getProgramID();
	GLuint getVertexSize();
	GLuint getMatrixID();
	GLuint gettID();
	float t;
private:
	void genWater();
	const uint16_t VERTEX_COUNT = 128;
	std::vector<glm::vec3> vertices;
	GLuint ProgramID;
	GLuint MatrixID;
	GLuint vertexBuffer;
	GLuint tID;
};

