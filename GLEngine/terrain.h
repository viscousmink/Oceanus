#pragma once
#include <cstdint>
#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <vector>
#include "shaders.h"
#include "loader.h"
#include <cmath>
#include <ctime>

class terrain
{
public:
	void init(const char* vert, const char* frag);
	GLuint getProgramID();
	void bindBuffers();
	GLuint getVertexSize();
	GLuint getVaoID();
	GLuint getMatrixID();
	
private:
	const uint16_t SIZE = 800;
	const uint16_t VERTEX_COUNT = 128;
	float x;
	float z;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> uvs;
	GLuint ProgramID;
	GLuint vertexBuffer;
	void genVAO();
	GLuint vaoID;
	GLuint MatrixID;
	void genTerrain();
};

