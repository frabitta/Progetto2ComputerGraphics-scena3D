#pragma once
#include "lib.h"

class Materiale {
public:
    Materiale(string i_nome, vec3 i_ambient, vec3 i_diffuse, vec3 i_specular, GLfloat i_shininess);
    Materiale();
    void setMat(string i_nome, vec3 i_ambient, vec3 i_diffuse, vec3 i_specular, GLfloat i_shininess);

    string nome;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    GLfloat shininess;
};
