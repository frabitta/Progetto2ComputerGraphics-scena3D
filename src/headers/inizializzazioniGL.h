#pragma once

const string shaderPath = "src/shaders/";
const string texturePath = "resources/textures/";
const string cubeMapPath = "resources/cubeMaps";

/* crea una nuova finestra OpenGL*/
int INIT_finestraOpenGL(GLFWwindow*& window, const int height, const int width);
/* Crea una cubemap*/
int INIT_Cubemap(string fileName);
/* Crea una texture*/
int INIT_Texture(string fileName, int flip);
/* Crea un program shader*/
GLuint INIT_shaderProg(const char* vertexFilename, const char* fragmentFilename);