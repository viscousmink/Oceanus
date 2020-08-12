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
	glm::vec3 getPosition();
	void translateModelMatrix(float x, float y, float z);
	void genVao();
	void init(const char* objPath, const char* textPath);
	GLuint getProgramID();
	GLuint getMatrixID();
	GLuint getTextureID();
	GLuint getTexture();
	void bindBuffers();
	GLuint getVerticesSize();
	GLuint getIndicesSize();
	GLuint getVaoID();
	void vboIndex(std::vector<glm::vec3>& tempvert, std::vector<glm::vec2>& tempuv, std::vector<glm::vec3>& tempnorm);

private:
	glm::mat4 Model;
	GLuint vaoID;
	GLuint ProgramID;
	GLuint MatrixID;
	GLuint Texture;
	GLuint TextureID;
	GLuint vertexBuffer;
	GLuint elementbuffer;
	GLuint uvbuffer;
	GLuint normbuffer;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<unsigned short> indices;
};

#endif