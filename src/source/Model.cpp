#include "Model.h"
#include "loadMeshes_assimp.h"

void setupMesh(Mesh* mesh, string nome, ShadingType shadingType);

const vec4 COLORE_ANCORA = vec4(0.0, 1.0, 0.0, 1.0);

void Model::assingUniformsToMeshes() {
	for (int i = 0; i < nmeshes; i++) {
		this->meshes[i]->uni_mat_ambient = this->loc_uni_mat_ambient;
		this->meshes[i]->uni_mat_diffuse = this->loc_uni_mat_diffuse;
		this->meshes[i]->uni_mat_specular = this->loc_uni_mat_specular;
		this->meshes[i]->uni_mat_shininess = this->loc_uni_mat_shininess;
		this->meshes[i]->uni_TextureYesNo = this->loc_uni_TextureYesNo;
		this->meshes[i]->uni_TextureLoc = this->loc_uni_TextureLoc;
		this->meshes[i]->uni_Model = this->loc_uni_Model;
		this->meshes[i]->uni_Shading = this->loc_uni_Shading;
		// this->meshes[i].textureID = this->loc_textureID;
	}
}

void Model::loadUniforms(GLint  mat_ambient, GLint  mat_diffuse, GLint  mat_specular, GLint  mat_shininess,
	GLint  uni_TextureYesNo, GLint  uni_TextureLoc, GLint  uni_Model, GLint  uni_Shading) {
	this->loc_uni_mat_ambient = mat_ambient;
	this->loc_uni_mat_diffuse = mat_diffuse;
	this->loc_uni_mat_specular = mat_specular;
	this->loc_uni_mat_shininess = mat_shininess;
	this->loc_uni_TextureYesNo = uni_TextureYesNo;
	this->loc_uni_TextureLoc = uni_TextureLoc;
	this->loc_uni_Model = uni_Model;
	this->loc_uni_Shading = uni_Shading;
	this->assingUniformsToMeshes();
}

/*
void Model::loadTexture() {
texturesino = si
	this->loc_textureID = textureID;
}*/

void Model::loadFromObj(const char* fileName, ShadingType shadingType, string name) {
	auto path = objPath + fileName;
	bool obj = loadAssImp(path.c_str(), this->meshes);
	this->nmeshes = (int)this->meshes.size();

	this->normalizeModel();
	
	this->initModel(shadingType, name);
	this->type = Type::Obj;
}

void printMatrix(mat4 M) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << M[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Model::updateMatrix() {
	mat4 model = mat4(1.0);
	model = glm::translate(model, this->posizione);
	model = glm::rotate(model, glm::radians(this->angolo), this->rotation_axis);
	model = glm::scale(model, this->dimensioni);
	
	for (int i = 0; i < this->nmeshes; i++)
	{
		this->meshes[i]->updateModelMatrix(model);
	}

	this->ancora_world = model * vec4(this->ancora,1.);
}

void setupMesh(Mesh *mesh, string nome, ShadingType shadingType) {
	mesh->nome = nome;
	mesh->shading = shadingType;
	mesh->INIT_vao();
}

/* adds a primitive to the model geometry */
void Model::addGeometry(Geometry type, vec4 colore, vec3 posizione, float angolo, vec3 rotation_axis, vec3 dimensioni) {
	Mesh* mesh = new Mesh();
	switch (type) {
	case PIANO: {
		crea_piano(mesh, colore);
		break;
	}
	case PIANO_SUDDIVISO: {
		crea_piano_suddiviso(mesh, colore);
		break;
	}
	case PIRAMIDE: {
		crea_piramide(mesh, colore);
		break;
	}
	case SFERA: {
		crea_sfera(mesh, colore);
		break;
	}
	case CILINDRO: {
		crea_cilindro(mesh, colore);
		break;
	}
	case TORO: {
		crea_toro(mesh, colore);
		break;
	}
	case CONO: {
		crea_cono(mesh, colore);
		break;
	}
	default:
	case CUBO: {
		crea_cubo(mesh, colore);
		break;
	}
	}
	mat4 model = mat4(1.0);
	model = glm::translate(model, posizione);
	model = glm::rotate(model, glm::radians(angolo), rotation_axis);
	model = glm::scale(model, dimensioni);
	for (int i = 0; i < mesh->vertices.size(); i++) {
		mesh->vertices[i] = vec3(model * vec4(mesh->vertices[i],1.));
	}

	this->meshes.push_back(mesh);
	this->nmeshes++;
}

void Model::addGeometry(Geometry type, vec4 colore) {
	this->addGeometry(type, colore, vec3(0., 0., 0.), 0., vec3(1., 0., 0.), vec3(1., 1., 1.));
}


/* create a model from a geometry */
void Model::compileGeometry(ShadingType shadingType, Materiale materiale, string name)  {
	this->type = Type::Primitives;
	this->normalizeModel();
	this->initModel(shadingType, name);
	this->setGeometryMaterial(materiale);
}

/* sets the geometry material */
void Model::setGeometryMaterial(Materiale materiale)  {
	if (this->type == Type::Primitives) {
		for (int i = 0; i < nmeshes; i++) {
			this->meshes[i]->materiale = materiale;
		}
	}
}

void Model::initModel(ShadingType shadingType, string nome) {
	this->name = nome;
	for (int i = 0; i < nmeshes; i++) {
		setupMesh(this->meshes[i], "Modello", shadingType);
	}

	this->updateMatrix();
	this->assingUniformsToMeshes();

	/* setup ancora vao */
	glGenVertexArrays(1, &this->ancora_VAO);
	glBindVertexArray(this->ancora_VAO);

	//Genero , rendo attivo, riempio il VBO del punto dell'ancora
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	vec3 anc = this->ancora;
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3), &anc, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	//Genero , rendo attivo, riempio il VBO del colore dell'ancora
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	vec4 colore = COLORE_ANCORA;
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec4), &colore, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

}

void Model::renderModel(bool flagAncora) {
	for (int i = 0; i < this->meshes.size(); i++) {
		this->meshes[i]->renderMesh();
	}

	/* disegna l'ancora se richiesto*/
	if (flagAncora) {
		glDisable(GL_DEPTH_TEST);

		glUniform1i(this->loc_uni_Shading, ShadingType::PASS_THROUGH);
		glBindVertexArray(this->ancora_VAO);
		glPointSize(15.0);
		glDrawArrays(GL_POINTS, 0, 1);
		glBindVertexArray(0);

		glEnable(GL_DEPTH_TEST);
	}
}

void Model::setShading(ShadingType shadingType) {
	for (int i = 0; i < nmeshes; i++) {
		this->meshes[i]->shading = shadingType;
	}
}

void Model::normalizeModel() {
	int i, k;
	unsigned int nmeshes = (unsigned int)this->meshes.size();
	vector<vec3> minimo, massimo;
	vec3 centroid = { 0.0f, 0.0f, 0.0f };

	//Calcolo il centroide della mesh (facendo la media dei suoi vertici)
	int numVertices = 0;
	for (i = 0; i < this->meshes.size(); i++) {
		for (k = 0; k < this->meshes[i]->vertices.size(); k++) {
			centroid += this->meshes[i]->vertices[k];
			numVertices++;
		}
	}
	centroid /= numVertices;

	for (i = 0; i < this->meshes.size(); i++) {
		for (k = 0; k < this->meshes[i]->vertices.size(); k++) {
			this->meshes[i]->vertices[k] -= centroid;
		}
	}

	// Troviamo i valori minimi e massimi per tutte le coordinate del modello
	float minX = numeric_limits<float>::max();
	float maxX = -numeric_limits<float>::max();
	float minY = numeric_limits<float>::max();
	float maxY = -numeric_limits<float>::max();
	float minZ = numeric_limits<float>::max();
	float maxZ = -numeric_limits<float>::max();

	// Iteriamo su tutte le mesh e troviamo i minimi e massimi globali
	for (i = 0; i < this->meshes.size(); i++) {
		for (k = 0; k < this->meshes[i]->vertices.size(); k++)
		{
			minX = std::min(minX, this->meshes[i]->vertices[k].x);
			maxX = std::max(maxX, this->meshes[i]->vertices[k].x);
			minY = std::min(minY, this->meshes[i]->vertices[k].y);
			maxY = std::max(maxY, this->meshes[i]->vertices[k].y);
			minZ = std::min(minZ, this->meshes[i]->vertices[k].z);
			maxZ = std::max(maxZ, this->meshes[i]->vertices[k].z);
		}
	}

	// Calcoliamo if fattore di scala per ogni dimensione (per mantenere le proporzioni
	float rangeX = maxX - minX;
	float rangeY = maxY - minY;
	float rangeZ = maxZ - minZ;

	float maxRange = std::max({ rangeX, rangeY, rangeZ });
	for (i = 0; i < this->meshes.size(); i++) {
		for (k = 0; k < this->meshes[i]->vertices.size(); k++) {
			this->meshes[i]->vertices[k].x = 2.0f * (this->meshes[i]->vertices[k].x - minX) / maxRange - 1.0f;
			this->meshes[i]->vertices[k].y = 2.0f * (this->meshes[i]->vertices[k].y - minY) / maxRange - 1.0f;
			this->meshes[i]->vertices[k].z = 2.0f * (this->meshes[i]->vertices[k].z - minZ) / maxRange - 1.0f;
		}
	}

	numVertices = 0;
	for (i = 0; i < this->meshes.size(); i++) {
		for (k = 0; k < this->meshes[i]->vertices.size(); k++) {
			centroid += this->meshes[i]->vertices[k];
			numVertices++;
		}
	}
	centroid /= numVertices;

	this->ancora = centroid;
}

void Model::goToPos(vec3 pos) {
	this->posizione = pos;
	this->updateMatrix();
}

void Model::rotate(float angle, vec3 axis) {
	this->angolo = angle;
	this->rotation_axis = axis;
	this->updateMatrix();
}

void Model::scale(vec3 scale) {
	this->dimensioni = scale;
	this->updateMatrix();
}