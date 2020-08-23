#ifndef RENDERER
#define RENDERER

#include "Object.h"
#include "terrain.h"
#include <GL/glew.h>

class Renderer
{
public:
	void render(Object obj, glm::mat4, glm::mat4, Object light);
	void renderTerrain(terrain terr, glm::mat4 Project, glm::mat4 View);
private:
	void bindVao(Object obj);
	void bindVaoTerrain(terrain terr);
};

#endif
