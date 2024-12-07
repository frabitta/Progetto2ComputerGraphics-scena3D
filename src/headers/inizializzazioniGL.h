#pragma once
#include "lib.h"

extern const string shaderPath;
extern const string texturePath;
extern const string cubeMapPath;

/* crea una nuova finestra OpenGL*/
int INIT_finestraOpenGL(GLFWwindow*& window, const int height, const int width);
/* Crea una cubemap*/
int INIT_Cubemap(string fileName);
/* Crea una texture*/
int INIT_Texture(string fileName, int flip);
/* Crea un program shader*/
GLuint INIT_shaderProg(const char* vertexFilename, const char* fragmentFilename);