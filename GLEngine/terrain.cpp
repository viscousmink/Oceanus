#include "terrain.h"

void terrain::init(const char* vert, const char* frag)
{
    ProgramID = LoadShaders(vert, frag);
    genVAO();
    genTerrain();

    MatrixID = glGetUniformLocation(ProgramID, "MVP");

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
}

GLuint terrain::getProgramID()
{
    return ProgramID;
}

void terrain::bindBuffers()
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

GLuint terrain::getVertexSize()
{
    return vertices.size();
}

GLuint terrain::getMatrixID()
{
    return MatrixID;
}

void terrain::genVAO()
{
    glBindVertexArray(0);
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
}

void terrain::genTerrain()
{
    srand(time(NULL));
    float** heightMap = (float**) malloc(sizeof(float*) * (1+VERTEX_COUNT));
    for (int i = 0; i < VERTEX_COUNT+1; i++)
    {
        heightMap[i] = (float*)malloc(sizeof(float) * (1+VERTEX_COUNT));
        for (int j = 0; j < VERTEX_COUNT+1; j++)
        {
            heightMap[i][j] = (float)rand() / (float) RAND_MAX;
        }
    }

	for (int i = 0; i < VERTEX_COUNT; i++)
	{
        for (int z = 0; z < VERTEX_COUNT; z++)
        {
            vertices.push_back(glm::vec3((float) i, heightMap[i][z], (float)z));
            vertices.push_back(glm::vec3((float) i + 1, heightMap[i+1][z+1], (float)z + 1));
            vertices.push_back(glm::vec3((float) i + 1, heightMap[i+1][z], (float) z));
            vertices.push_back(glm::vec3((float) i, heightMap[i][z+1], (float) z + 1));
            vertices.push_back(glm::vec3((float) i + 1, heightMap[i+1][z+1], (float) z + 1));
            vertices.push_back(glm::vec3((float) i, heightMap[i][z], (float) z));
        }
	}
}
