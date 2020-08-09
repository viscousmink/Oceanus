#ifndef OBJECT
#define OBJECT

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <vector>
#include "shaders.h"
#include "loader.h"

class Object
{
public:
	glm::mat4 getModelMatrix();
	void translateModelMatrix(float x, float y, float z);
	void genVao();
	void init(const char* objPath, const char* textPath);
	GLuint getProgramID();
	GLuint getMatrixID();
	GLuint getTextureID();
	GLuint getTexture();
	void bindBuffers();
	GLuint getVerticesSize();

private:
	glm::mat4 Model;
	GLuint vaoID;
	GLuint ProgramID;
	GLuint MatrixID;
	GLuint Texture;
	GLuint TextureID;
	GLuint vertexBuffer;
	GLuint uvbuffer;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
};

#endif