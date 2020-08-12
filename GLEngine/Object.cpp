#include "Object.h"

glm::mat4 Object::getModelMatrix()
{
	return Model;
}

glm::vec3 Object::getPosition()
{
	return glm::vec3(Model[3][0], Model[3][1], Model[3][2]);
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

	std::vector<glm::vec3> tempvert;
	std::vector<glm::vec2> tempuv;
	std::vector<glm::vec3> tempnorm;

	bool result = loadObj(obj, tempvert, tempuv, tempnorm);
	ProgramID = LoadShaders("Shaders/Vertex.txt", "Shaders/Fragment.txt");
	MatrixID = glGetUniformLocation(ProgramID, "MVP");
	Texture = loadDDS(text);
	TextureID = glGetUniformLocation(ProgramID, "myTextureSampler");

	vboIndex(tempvert, tempuv, tempnorm);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * uvs.size(), &uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), &normals[0], GL_STATIC_DRAW);

	
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);
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

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normbuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
}

GLuint Object::getVerticesSize()
{
	return vertices.size();
}

GLuint Object::getIndicesSize()
{
	return indices.size();
}

GLuint Object::getVaoID()
{
	return vaoID;
}

bool is_near(float v1, float v2)
{
	return fabs(v1 - v2) < 0.01f;
}

bool getSimilarVertexIndex(
	glm::vec3& in_vertex,
	glm::vec2& in_uv,
	glm::vec3& in_normal,
	std::vector<glm::vec3>& out_vertices,
	std::vector<glm::vec2>& out_uvs,
	std::vector<glm::vec3>& out_normals,
	unsigned short& result
) {
	for (unsigned int i = 0; i < out_vertices.size(); i++) {
		if (
			is_near(in_vertex.x, out_vertices[i].x) &&
			is_near(in_vertex.y, out_vertices[i].y) &&
			is_near(in_vertex.z, out_vertices[i].z) &&
			is_near(in_uv.x, out_uvs[i].x) &&
			is_near(in_uv.y, out_uvs[i].y) &&
			is_near(in_normal.x, out_normals[i].x) &&
			is_near(in_normal.y, out_normals[i].y) &&
			is_near(in_normal.z, out_normals[i].z)
			) {
			result = i;
			return true;
		}
	}
	return false;
}

void Object::vboIndex(std::vector<glm::vec3>& tempvert, std::vector<glm::vec2>& tempuv, std::vector<glm::vec3>& tempnorm)
{
	for (unsigned int i = 0; i < tempvert.size(); i++) {

		unsigned short index;
		bool found = getSimilarVertexIndex(tempvert[i], tempuv[i], tempnorm[i], vertices, uvs, normals, index);

		if (found) {
			indices.push_back(index);
		}
		else {
			vertices.push_back(tempvert[i]);
			uvs.push_back(tempuv[i]);
			normals.push_back(tempnorm[i]);
			indices.push_back((unsigned short)vertices.size() - 1);
		}
	}
}

