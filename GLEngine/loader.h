#ifndef LOADER
#define LOADER

#define GLEW_STATIC
#include <GL/glew.h>

#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

bool loadObj(const char* objectPath, std::vector<glm::vec3>& out_vert, std::vector<glm::vec2>& out_uv, std::vector<glm::vec3>& out_norm);
GLuint loadDDS(const char* imagepath);

#endif