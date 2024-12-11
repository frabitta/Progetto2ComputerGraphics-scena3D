#include "inizializzazioniGL.h"
#include "Scena.h"
#include "Geometry.h"
#include "Materiale.h"
#include "Skybox.h"
#include "lib.h"

void loadShaders();
/* returns true if camera collides with a model */
bool checkCollision(vec3 p, vector<Model *> models);

glm::vec3 red_plastic_ambient = { 0.1, 0.0, 0.0 }, red_plastic_diffuse = { 0.6, 0.1, 0.1 }, red_plastic_specular = { 0.7, 0.6, 0.6 }; GLfloat red_plastic_shininess = 150.0f;
Materiale mat_plasticaRossa = Materiale("Plastica rossa", red_plastic_ambient, red_plastic_diffuse, red_plastic_specular, red_plastic_shininess);

glm::vec3 brass_ambient = { 0.5, 0.06, 0.015 }, brass_diffuse = { 0.78, 0.57, 0.11 }, brass_specular = { 0.99, 0.91, 0.81 }; GLfloat brass_shininess = 27.8f;
Materiale mat_ottone = Materiale("Ottone", brass_ambient, brass_diffuse, brass_specular, brass_shininess);

glm::vec3 emerald_ambient = { 0.0215, 0.04745, 0.0215 }, emerald_diffuse = { 0.07568, 0.61424, 0.07568 }, emerald_specular = { 0.633, 0.727811, 0.633 }; GLfloat emerald_shininess = 78.8f;
Materiale mat_smeraldo = Materiale("Smeraldo", emerald_ambient, emerald_diffuse, emerald_specular, emerald_shininess);

glm::vec3 snow_white_ambient = { 0.2, 0.2, 0.2 }, snow_white_diffuse = { 0.95, 0.96, 0.98 }, snow_white_specular{ 0.8, 0.8, 0.8 }; GLfloat snow_white_shininess = 1.78125f;
Materiale mat_neve = Materiale("Neve", snow_white_ambient, snow_white_diffuse, snow_white_specular, snow_white_shininess);

glm::vec3 yellow_ambient = { 0.8,	0.8,	0.0 }, yellow_diffuse = { 1.0,1.0,0.6 }, yellow_specular{ 0.9,	0.9	,0.04 }; GLfloat yellow_shininess = 1.78125f;
Materiale mat_giallo = Materiale("Giallo", yellow_ambient, yellow_diffuse, yellow_specular, yellow_shininess);

glm::vec3 pink_ambient = { 0.05f,0.0f,0.0f }, pink_diffuse = { 0.5f,0.4f,0.4f }, pink_specular{ 0.7f,0.04f,0.04f }; GLfloat pink_shininess = 1.78125f;
Materiale mat_rosa = Materiale("Rosa", pink_ambient, pink_diffuse, pink_specular, pink_shininess);

glm::vec3 brown_ambient = { 0.19125f, 0.0735f, 0.0225f }, brown_diffuse = { 0.7038f, 0.27048f, 0.0828f }, brown_specular{ 0.256777f, 0.137622f, 0.086014f }; GLfloat brown_shininess = 12.8f;
Materiale mat_marrone = Materiale("Marrone", brown_ambient, brown_diffuse, brown_specular, brown_shininess);


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
} uni_light, uni_light2;

static struct {
	GLint  diffuse;
	GLint  ambient;
	GLint  specular;
	GLint  shininess;
	GLint ambientReflectance;
} uni_material;

static struct {
	GLint amp;
	GLint off;
	GLint speed;
} uni_wave;

static GLuint skyboxProgramId;
static GLuint modelsProgramId;

mat4 Projection = mat4(1.0);
mat4 View = mat4(1.0);

/* sky */
string skyboxCubemap = "field";
Skybox sky;
GLint skybox_uni_proj;
GLint skybox_uni_view;
const char* skyVertex = "sky_vertex.glsl";
const char* skyFragment = "sky_fragment.glsl";

/* camera movement */
extern bool navigating;
extern int mov_x;
extern int mov_y;
extern int mov_z;
extern bool rotating;
extern vec3 rotationNextPos;

void Scena::update(double deltaTime) {
	vec3 nextPos = this->camera->position;
	if (navigating) {
		float speed = 0.3;
		vec3 movementVector = vec3(0., 0., 0.);
		movementVector += normalize(this->camera->upVector) * (float)mov_y;
		movementVector += normalize(this->camera->direction) * -(float)mov_z;
		movementVector += normalize(vec3(-this->camera->direction.z, 0, this->camera->direction.x)) * (float)mov_x;
		if (movementVector != vec3(0.,0.,0.)) {
			movementVector = normalize(movementVector) * speed;
		}
		nextPos = this->camera->position + movementVector;
		
		if (!checkCollision(nextPos, this->models)) {
			this->camera->position = nextPos;
			this->camera->target = this->camera->position + this->camera->direction; //aggiorno il punto in cui guarda la telecamera
		}
	}
	else if (rotating) {
		nextPos = rotationNextPos;
		if (!checkCollision(nextPos, this->models)) {
			this->camera->position = nextPos;
			this->camera->direction = normalize(this->camera->target - this->camera->position);
		}
	}
}


// implementazioni della scena
void Scena::initScene() {
	loadShaders();
	this->camera = new Camera();
	this->light1 = new Light();
	this->light1->position = vec3(2., 1., 2.);
	this->light1->color = vec3(1., 0., 0.);
	this->light1->power = 7.;
	this->light2 = new Light();
	this->light2->position = vec3(-2., 1., -1.);
	this->light2->color = vec3(0., 1., 0.);
	this->light2->power = 7.;


	sky.createSkybox(skyboxCubemap);
	skyboxProgramId = INIT_shaderProg(skyVertex, skyFragment);
	glUseProgram(skyboxProgramId);
	skybox_uni_proj = glGetUniformLocation(skyboxProgramId, "Proj");
	skybox_uni_view = glGetUniformLocation(skyboxProgramId, "View");
	glUseProgram(modelsProgramId);
	glUniform1i(glGetUniformLocation(modelsProgramId, "skybox"),sky.cubemap);

	Model* modello = new Model();
	modello->loadFromObj("Shelby.obj", ShadingType::BLINN_PHONG, "Macchina");
	modello->loadUniforms(uni_material.ambient, uni_material.diffuse, uni_material.specular, uni_material.shininess,
		uni_shading.textureSiNo, uni_shading.textureLoc, uni_trans.Model, uni_shading.shadingType, uni_material.ambientReflectance,
		uni_wave.amp, uni_wave.off, uni_wave.speed);
	modello->goToPos(vec3(0., 0., -3.));
	modello->scale(vec3(3., 3., 3.));
	modello->setReflectance(0.8);
	this->models.push_back(modello);

	modello = new Model();
	modello->addGeometry(Geometry::PIANO_SUDDIVISO, vec4(1., 0., 0., 1.));
	modello->compileGeometry(ShadingType::PHONG, mat_marrone, "terra");
	modello->loadUniforms(uni_material.ambient, uni_material.diffuse, uni_material.specular, uni_material.shininess,
		uni_shading.textureSiNo, uni_shading.textureLoc, uni_trans.Model, uni_shading.shadingType, uni_material.ambientReflectance,
		uni_wave.amp, uni_wave.off, uni_wave.speed);
	modello->goToPos(vec3(0., -3., 0.));
	modello->scale(vec3(200., 1., 200.));
	this->models.push_back(modello);

	modello = new Model();
	modello->addGeometry(Geometry::CUBO, vec4(1., 0., 0., 1.));
	modello->compileGeometry(ShadingType::BLINN_PHONG, mat_ottone, "cubo1");
	modello->loadUniforms(uni_material.ambient, uni_material.diffuse, uni_material.specular, uni_material.shininess,
		uni_shading.textureSiNo, uni_shading.textureLoc, uni_trans.Model, uni_shading.shadingType, uni_material.ambientReflectance,
		uni_wave.amp, uni_wave.off, uni_wave.speed);
	modello->goToPos(vec3(4.,0.,0.));
	// modello->setTexture(true, texture);
	this->models.push_back(modello);
	

	modello = new Model();
	modello->addGeometry(Geometry::CUBO, vec4(1., 0., 0., 1.));
	modello->compileGeometry(ShadingType::BLINN_PHONG, mat_plasticaRossa, "cubo2");
	modello->loadUniforms(uni_material.ambient, uni_material.diffuse, uni_material.specular, uni_material.shininess,
		uni_shading.textureSiNo, uni_shading.textureLoc, uni_trans.Model, uni_shading.shadingType, uni_material.ambientReflectance,
		uni_wave.amp, uni_wave.off, uni_wave.speed);
	modello->goToPos(vec3(0., 4., 0.));
	this->models.push_back(modello);
	
	this->resetScene();
}

void Scena::resetScene() {
	this->camera->initCamera();
	this->light1->initLight();
}

vector<Model*> Scena::getModels() {
	return this->models;
}

Camera* Scena::getCamera() {
	return this->camera;
}

Light* Scena::getLight1() {
	return this->light1;
}

Light* Scena::getLight2() {
	return this->light2;
}

void Scena::render(double time, bool flagWireFrame, bool flagAnchorPoints) {
	// this->camera->position = vec3(10 * sin(time * 0.2), 0., 5+10*sin(time * 0.2));
	
	// pulizia del buffer
	glClearColor(0.305f, 0.329f, 0.651f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	// Elaborazione matrici di Proiezione e Vista
	Projection = perspective(radians(this->camera->fovY), this->camera->aspect, this->camera->near_plane, this->camera->far_plane);
	View = lookAt(vec3(this->camera->position), vec3(this->camera->target), vec3(this->camera->upVector));

	// stampa della skybox
	glUseProgram(skyboxProgramId);
	glUniform1i(glGetUniformLocation(skyboxProgramId, "skybox"), 0);
	glUniformMatrix4fv(skybox_uni_proj, 1, GL_FALSE, value_ptr(Projection));
	glUniformMatrix4fv(skybox_uni_view, 1, GL_FALSE, value_ptr(View));
	sky.render();

	/* preparazione program shader per i modelli
	* - tempo
	* - matrici di proiezione e vista
	* - modalità wireframe
	* - luci della scena
	* - telecamera
	*/
	glUseProgram(modelsProgramId);
	glUniform1i(glGetUniformLocation(modelsProgramId, "skybox"), 0);

	glUniform1f(uni_trans.time, (float)time);
	glUniformMatrix4fv(uni_trans.View, 1, GL_FALSE, value_ptr(View));
	glUniformMatrix4fv(uni_trans.Projection, 1, GL_FALSE, value_ptr(Projection));
	if (flagWireFrame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glUniform3f(uni_trans.ViewPos, this->camera->position.x, this->camera->position.y, this->camera->position.z);
	glUniform3f(uni_light.position, this->light1->position.x, this->light1->position.y, this->light1->position.z);
	glUniform3f(uni_light.color, this->light1->color.x, this->light1->color.y, this->light1->color.z);
	glUniform1f(uni_light.power, this->light1->power);
	glUniform3f(uni_light2.position, this->light2->position.x, this->light2->position.y, this->light2->position.z);
	glUniform3f(uni_light2.color, this->light2->color.x, this->light2->color.y, this->light2->color.z);
	glUniform1f(uni_light2.power, this->light2->power);

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

	uni_light.position = glGetUniformLocation(modelsProgramId, "light[0].position");
	uni_light.color = glGetUniformLocation(modelsProgramId, "light[0].color");
	uni_light.power = glGetUniformLocation(modelsProgramId, "light[0].power");

	uni_light2.position = glGetUniformLocation(modelsProgramId, "light[1].position");
	uni_light2.color = glGetUniformLocation(modelsProgramId, "light[1].color");
	uni_light2.power = glGetUniformLocation(modelsProgramId, "light[1].power");

	uni_material.diffuse = glGetUniformLocation(modelsProgramId, "material.diffuse");
	uni_material.ambient = glGetUniformLocation(modelsProgramId, "material.ambient");
	uni_material.specular = glGetUniformLocation(modelsProgramId, "material.specular");
	uni_material.shininess = glGetUniformLocation(modelsProgramId, "material.shininess");
	uni_material.ambientReflectance = glGetUniformLocation(modelsProgramId, "reflectance");

	uni_wave.amp = glGetUniformLocation(modelsProgramId, "wave.Amp");
	uni_wave.off = glGetUniformLocation(modelsProgramId, "wave.Off");
	uni_wave.speed = glGetUniformLocation(modelsProgramId, "wave.Speed");
}


void Scena::cleanStructure() {
	delete(this->camera);
	for (int i = 0; i < this->models.size(); i++) {
		delete(this->models[i]);
	}
}

bool checkCollision(vec3 p, vector<Model *> models) {
	bool collided = false;

	for (int i = 0; !collided && i < models.size(); i++) {
		collided = models[i]->checkCollision(p);
	}

	return collided;
}
