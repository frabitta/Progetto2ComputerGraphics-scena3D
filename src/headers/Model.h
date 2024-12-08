#pragma once
#include "lib.h"
#include "Mesh.h"
#include "Geometry.h"

class Model {
public:
	/* load uniform indices */
	void loadUniforms(GLint  mat_ambient, GLint  mat_diffuse, GLint  mat_specular, GLint  mat_shininess,
		GLint  uni_TextureYesNo, GLint  uni_TextureLoc, GLint  uni_Model, GLint  uni_Shading);
	/* create a model from a .obj file*/
	void loadFromObj(const char* fileName, ShadingType shadingType);
	/* create a model from a geometry */
	void createFromGeometry(Geometry type, vec4 colore, ShadingType shadingType);
	/* renders the model */
	void renderModel(bool flagAncora);
	/* moves the model */
	void goToPos(vec3 pos);

private:
	void normalizeModel();
	void updateMatrix();
	void assingUniformsToMeshes();

	vector<Mesh *> meshes;
	int nmeshes = 0;
	vec3 posizione = vec3(0.,0.,0.);
	float angolo = 0.f;
	vec3 rotation_axis = vec3(0.,1.,0.);
	vec3 dimensioni = vec3(1.,1.,1.);

	GLint  loc_uni_mat_ambient, loc_uni_mat_diffuse, loc_uni_mat_specular, loc_uni_mat_shininess;
	GLint  loc_uni_TextureYesNo, loc_uni_TextureLoc;
	GLint  loc_uni_Model, loc_uni_Shading;
};