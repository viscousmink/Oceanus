#ifndef RENDERER
#define RENDERER

#include "Object.h"
#include <GL/glew.h>

class Renderer
{
public:
	void render(Object obj, glm::mat4, glm::mat4, Object light);
private:
	void bindVao(Object obj);
};

#endif
