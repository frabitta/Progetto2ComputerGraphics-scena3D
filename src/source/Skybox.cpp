#include "Skybox.h"
#include "inizializzazioniGL.h"
#include "Geometry.h"

void Skybox::createSkybox(string cubeMapName) {
	this->cubemap = INIT_Cubemap(cubeMapName);
	crea_cubo(this, vec4(1., 1., 1., 1.));
	this->INIT_VAO();
}

void Skybox::render() {
	glDepthMask(GL_FALSE);
	glBindVertexArray(this->VAO);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->cubemap);
	glDrawElements(GL_TRIANGLES, this->indices.size() * sizeof(GLuint), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glDepthMask(GL_TRUE);
}