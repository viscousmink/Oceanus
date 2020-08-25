#include "Renderer.h"

void Renderer::render(Object obj, glm::mat4 Project, glm::mat4 View, Object light)
{
	glUseProgram(obj.getProgramID());
	bindVao(obj);
	GLuint LightID = glGetUniformLocation(obj.getProgramID(), "LightPosition_worldspace");
	GLuint ViewMatrixID = glGetUniformLocation(obj.getProgramID(), "V");
	GLuint ModelMatrixID = glGetUniformLocation(obj.getProgramID(), "M");
	glm::mat4 MVP = Project * View * obj.getModelMatrix();
	glm::mat4 M = obj.getModelMatrix();
	glUniformMatrix4fv(obj.getMatrixID(), 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &M[0][0]);
	//glm::vec3 lightPos = light.getPosition();
	glm::vec3 lightPos = glm::vec3(4, 4, 4);
	glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, obj.getTexture());
	glUniform1i(obj.getTextureID(), 0);
	obj.bindBuffers();
	glDrawElements(GL_TRIANGLES, obj.getIndicesSize(), GL_UNSIGNED_SHORT, (void*)0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void Renderer::renderTerrain(terrain terr, glm::mat4 Project, glm::mat4 View)
{
	bindVaoTerrain(terr);
	glUseProgram(terr.getProgramID());
	glm::mat4 MVP = Project * View * glm::mat4(1.0);
	terr.bindBuffers();
	glUniformMatrix4fv(terr.getMatrixID(), 1, GL_FALSE, &MVP[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, terr.getVertexSize() * 3);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Renderer::renderWater(Water water, glm::mat4 Project, glm::mat4 View)
{
	bindVaoWater(water);
	glUseProgram(water.getProgramID());
	glm::mat4 MVP = Project * View * glm::mat4(1.0);
	water.bindBuffers();
	glUniformMatrix4fv(water.getMatrixID(), 1, GL_FALSE, &MVP[0][0]);
	glUniform1f(water.gettID(), water.t);
	glDrawArrays(GL_TRIANGLES, 0, water.getVertexSize() * 3);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Renderer::bindVao(Object obj)
{
	glBindVertexArray(obj.getVaoID());
}

void Renderer::bindVaoTerrain(terrain terr)
{
	glBindVertexArray(terr.getVaoID());
}

void Renderer::bindVaoWater(Water water)
{
	glBindVertexArray(water.getVaoID());
}
