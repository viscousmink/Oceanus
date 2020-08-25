#pragma once
#define GLEW_STATIC
#include "GL/glew.h"

class Renderable
{
public:
	void genVao();
	GLuint getVaoID();
protected:
	GLuint vaoID;
};

