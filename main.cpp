#include "lib.h"
#include "inizializzazioniGL.h"

// Dichiarazione funzioni locali
/* main loop of the window */
void gameLoop();

// Variabili Globali
const int height = 900;
const int width = 1600;
GLFWwindow* window;

// Main
int main(void) {
	INIT_finestraOpenGL(window, height, width);

	gameLoop();

	glfwTerminate();
	return 0;
}

// Definizione funzioni locali
void gameLoop() {
	while (!glfwWindowShouldClose(window)) {
		double currentFrame = glfwGetTime();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}
}