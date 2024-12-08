#include "inizializzazioniGL.h"
#include "Scena.h"
#include "Geometry.h"
#include "Mesh.h"
#include "lib.h"

void loadShaders();

// Strutture locali a questa scena
static struct {
	GLint  time;
	GLint  Model;
	GLint  View;
	GLint  Projection;
	GLint  ViewPos;
} uni_trans;

static struct {
	GLint  shadingType;
	GLint  textureSiNo;
	GLint  textureLoc;
} uni_shading;

static struct {
	GLint  position;
	GLint  color;
	GLint  power;
} uni_light;

static struct {
	GLint  diffuse;
	GLint  ambient;
	GLint  specular;
	GLint  shininess;
} uni_material;

static GLuint skyboxProgramId;
static GLuint modelsProgramId;

// implementazioni della scena
void Scena::initScene() {
	loadShaders();
	this->camera = new Camera();
	this->light = new Light();

	Model* cubo = new Model();
	cubo->createFromGeometry(Geometry::CUBO, vec4(1.,0.,0.,1.), ShadingType::PASS_THROUGH);
	cubo->loadUniforms(uni_material.ambient, uni_material.diffuse, uni_material.specular, uni_material.shininess,
		uni_shading.textureSiNo, uni_shading.textureLoc, uni_trans.Model, uni_shading.shadingType);
	cubo->goToPos(vec3(0., 0., 0.));
	this->models.push_back(cubo);

	cubo = new Model();
	cubo->createFromGeometry(Geometry::CUBO, vec4(1., 0., 0., 1.), ShadingType::PASS_THROUGH);
	cubo->loadUniforms(uni_material.ambient, uni_material.diffuse, uni_material.specular, uni_material.shininess,
		uni_shading.textureSiNo, uni_shading.textureLoc, uni_trans.Model, uni_shading.shadingType);
	cubo->goToPos(vec3(4.,0.,0.));
	this->models.push_back(cubo);

	cubo = new Model();
	cubo->createFromGeometry(Geometry::CUBO, vec4(1., 0., 0., 1.), ShadingType::PASS_THROUGH);
	cubo->loadUniforms(uni_material.ambient, uni_material.diffuse, uni_material.specular, uni_material.shininess,
		uni_shading.textureSiNo, uni_shading.textureLoc, uni_trans.Model, uni_shading.shadingType);
	cubo->goToPos(vec3(0., 4., 0.));
	this->models.push_back(cubo);
	
	this->resetScene();
}

void Scena::resetScene() {
	this->camera->initCamera();
	this->light->initLight();
}

vector<Model*> Scena::getModels() {
	return this->models;
}

Camera* Scena::getCamera() {
	return this->camera;
}

void Scena::render(double time, bool flagWireFrame, bool flagAnchorPoints) {
	// pulizia del buffer
	glClearColor(0.305f, 0.329f, 0.651f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Elaborazione matrici di Proiezione e Vista
	mat4 Projection = perspective(radians(this->camera->fovY), this->camera->aspect, this->camera->near_plane, this->camera->far_plane);
	mat4 View = lookAt(vec3(this->camera->position), vec3(this->camera->target), vec3(this->camera->upVector));

	// stampa della skybox
	/*
	glDepthMask(GL_FALSE);
	glUseProgram(programId1);
	glUniform1i(glGetUniformLocation(programId1, "skybox"), 0);
	glUniformMatrix4fv(uniform.MatProjS, 1, GL_FALSE, value_ptr(Projection));
	glUniformMatrix4fv(uniform.MatViewS, 1, GL_FALSE, value_ptr(View));
	glBindVertexArray(sky.VAO);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawElements(GL_TRIANGLES, sky.indices.size() * sizeof(GLuint), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glDepthMask(GL_TRUE);
	*/

	/* preparazione program shader per i modelli
	* - tempo
	* - matrici di proiezione e vista
	* - modalità wireframe
	* - luci della scena
	* - telecamera
	*/
	glUseProgram(modelsProgramId);
	glUniform1f(uni_trans.time, (float)time);
	glUniformMatrix4fv(uni_trans.View, 1, GL_FALSE, value_ptr(View));
	glUniformMatrix4fv(uni_trans.Projection, 1, GL_FALSE, value_ptr(Projection));
	if (flagWireFrame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glUniform3f(uni_trans.ViewPos, this->camera->position.x, this->camera->position.y, this->camera->position.z);
	glUniform3f(uni_light.position, this->light->position.x, this->light->position.y, this->light->position.z);
	glUniform3f(uni_light.color, this->light->color.x, this->light->color.y, this->light->color.z);
	glUniform1f(uni_light.power, this->light->power);

	// renderign dei singoli modelli -> delle singole mesh
	unsigned int nModels = (unsigned int)this->models.size();
	for (unsigned int i = 0; i < nModels; i++) {
		this->models[i]->renderModel(flagAnchorPoints);
	}
}

void loadShaders() {
	// Carica e crea i programmi
	modelsProgramId = INIT_shaderProg("model_vertex.glsl","model_fragment.glsl");
	
	glUseProgram(modelsProgramId);
	// ottiene gli indici delle variabili uniform
	
	uni_trans.time = glGetUniformLocation(modelsProgramId, "time");
	uni_trans.Model = glGetUniformLocation(modelsProgramId, "Model");
	uni_trans.View = glGetUniformLocation(modelsProgramId, "View");
	uni_trans.Projection = glGetUniformLocation(modelsProgramId, "Projection");
	uni_trans.ViewPos = glGetUniformLocation(modelsProgramId, "ViewPos");
	
	uni_shading.shadingType = glGetUniformLocation(modelsProgramId, "shadingType");
	uni_shading.textureSiNo = glGetUniformLocation(modelsProgramId, "textureSi");
	uni_shading.textureLoc = glGetUniformLocation(modelsProgramId, "textureLoc");

	uni_light.position = glGetUniformLocation(modelsProgramId, "light.position");
	uni_light.color = glGetUniformLocation(modelsProgramId, "light.color");
	uni_light.power = glGetUniformLocation(modelsProgramId, "light.power");

	uni_material.diffuse = glGetUniformLocation(modelsProgramId, "material.diffuse");
	uni_material.ambient = glGetUniformLocation(modelsProgramId, "material.ambient");
	uni_material.specular = glGetUniformLocation(modelsProgramId, "material.specular");
	uni_material.shininess = glGetUniformLocation(modelsProgramId, "material.shininess");
}

void Scena::cleanStructure() {
	delete(this->camera);
	for (int i = 0; i < this->models.size(); i++) {
		delete(this->models[i]);
	}
}

