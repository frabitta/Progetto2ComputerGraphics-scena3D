#pragma once
#include "lib.h"
#include "Mesh.h"
#include "Geometry.h"
#include "Materiale.h"

extern const string objPath;

enum Type {
	Obj,
	Primitives
};

class Model {
public:
	/* load uniform indices */
	void loadUniforms(GLint  mat_ambient, GLint  mat_diffuse, GLint  mat_specular, GLint  mat_shininess,
		GLint  uni_TextureYesNo, GLint  uni_TextureLoc, GLint  uni_Model, GLint  uni_Shading);
	/* create a model from a .obj file*/
	void loadFromObj(const char* fileName, ShadingType shadingType, string name);
	/* adds a primitive to the model geometry */
	void addGeometry(Geometry type, vec4 colore);
	void addGeometry(Geometry type, vec4 colore, vec3 posizione, float angolo, vec3 rotation_axis, vec3 dimensioni);
	/* create a model from a geometry */
	void compileGeometry(ShadingType shadingType, Materiale materiale, string name);
	/* sets the geometry material */
	void setGeometryMaterial(Materiale materiale);
	/* renders the model */
	void renderModel(bool flagAncora);
	/* moves the model */
	void goToPos(vec3 pos);
	/* rotates model */
	void rotate(float angle, vec3 axis);
	/* scales the model */
	void scale(vec3 scale);
	/* set the shading of the model */
	void setShading(ShadingType shadingType);

private:
	void normalizeModel();
	void updateMatrix();
	void assingUniformsToMeshes();
	void initModel(ShadingType shadingType, string nome);

	Type type;
	string name;

	vector<Mesh *> meshes;
	int nmeshes = 0;
	vec3 posizione = vec3(0.,0.,0.);
	float angolo = 0.f;
	vec3 rotation_axis = vec3(0.,1.,0.);
	vec3 dimensioni = vec3(1.,1.,1.);

	vec3 ancora = vec3(0., 0., 0.); // Punto di ancoraggio del modello locale
	vec4 ancora_world;
	GLuint ancora_VAO;
	GLuint ancora_VBO;

	GLint  loc_uni_mat_ambient, loc_uni_mat_diffuse, loc_uni_mat_specular, loc_uni_mat_shininess;
	GLint  loc_uni_TextureYesNo, loc_uni_TextureLoc;
	GLint  loc_uni_Model, loc_uni_Shading;
};