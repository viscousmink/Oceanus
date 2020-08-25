#include "Water.h"

void Water::init(const char * vert, const char * frag)
{
    t = 0.0;
    ProgramID = LoadShaders(vert, frag);
	genVao();
	genWater();

    MatrixID = glGetUniformLocation(ProgramID, "MVP");
    tID = glGetUniformLocation(ProgramID, "t");

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
}

void Water::bindBuffers()
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

GLuint Water::getProgramID()
{
    return ProgramID;
}

GLuint Water::getVertexSize()
{
    return vertices.size();
}

GLuint Water::getMatrixID()
{
    return MatrixID;
}

GLuint Water::gettID()
{
    return tID;
}

void Water::genWater()
{
    for (int i = 0; i < VERTEX_COUNT; i++)
    {
        for (int z = 0; z < VERTEX_COUNT; z++)
        {
            vertices.push_back(glm::vec3((float)i, 0, (float)z));
            vertices.push_back(glm::vec3((float)i + 1, 0, (float)z + 1));
            vertices.push_back(glm::vec3((float)i + 1, 0, (float)z));
            vertices.push_back(glm::vec3((float)i, 0, (float)z + 1));
            vertices.push_back(glm::vec3((float)i + 1, 0, (float)z + 1));
            vertices.push_back(glm::vec3((float)i, 0, (float)z));
        }
    }
}
