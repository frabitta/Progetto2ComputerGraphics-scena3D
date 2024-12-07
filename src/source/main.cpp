#include "lib.h"
#include "Scena.h"
#include "inizializzazioniGL.h"

// Dichiarazione funzioni locali


// Variabili Globali
const string shaderPath = "src/shaders/";
const string texturePath = "resources/textures/";
const string cubeMapPath = "resources/cubeMaps";
const string objPath = "resources/models/";

const int height = 900;
const int width = 1600;
GLFWwindow* window;

// Main
int main(void) {
	Scena scena;
	INIT_finestraOpenGL(window, height, width);

	scena.initScene();
	
	while (!glfwWindowShouldClose(window)) {
		double currentFrame = glfwGetTime();

		scena.render(currentFrame, false, false);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	scena.cleanStructure();
	glfwTerminate();
	return 0;
}
