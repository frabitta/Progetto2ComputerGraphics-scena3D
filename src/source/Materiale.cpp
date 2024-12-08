#include "Materiale.h"

Materiale::Materiale(string i_nome, vec3 i_ambient, vec3 i_diffuse, vec3 i_specular, GLfloat i_shininess) {
    this->nome = i_nome;
    this->ambient = i_ambient;
    this->diffuse = i_diffuse;
    this->specular = i_specular;
    this->shininess = i_shininess;
}

Materiale::Materiale() {
    this->nome = "def";
    this->ambient = vec3(0.5,0.5,0.5);
    this->diffuse = vec3(0.5, 0.5, 0.5);
    this->specular = vec3(0.5, 0.5, 0.5);
    this->shininess = 0.2;
}

void Materiale::setMat(string i_nome, vec3 i_ambient, vec3 i_diffuse, vec3 i_specular, GLfloat i_shininess) {
    this->nome = i_nome;
    this->ambient = i_ambient;
    this->diffuse = i_diffuse;
    this->specular = i_specular;
    this->shininess = i_shininess;
}
