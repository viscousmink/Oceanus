#include "Renderer.h"

void Renderer::render(Object obj, glm::mat4 Project, glm::mat4 View)
{
	glUseProgram(obj.getProgramID());
	glm::mat4 MVP = Project * View * obj.getModelMatrix();
	glUniformMatrix4fv(obj.getMatrixID(), 1, GL_FALSE, &MVP[0][0]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, obj.getTexture());
	glUniform1i(obj.getTextureID(), 0);
	obj.bindBuffers();
	glDrawElements(GL_TRIANGLES, obj.getIndicesSize(), GL_UNSIGNED_SHORT, (void*)0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}
