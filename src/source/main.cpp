#include "lib.h"
#include "Scena.h"
#include "inizializzazioniGL.h"
#include "Gui.h"
#include "Model.h"
#include "Light.h"
#include "Camera.h"
// #include "eventManager.h"

// Dichiarazione funzioni locali


// Variabili Globali
const string shaderPath = "src/shaders/";
const string texturePath = "resources/textures/";
const string cubeMapPath = "resources/cubeMaps/";
const string objPath = "resources/models/";

const int height = 900;
const int width = 1600;
GLFWwindow* window;

Light* light1;
Camera* camera;
vector<Model*> models;
bool flagWF = false;
bool flagAncora = false;

// Main
int main(void) {
	Scena scena;
	INIT_finestraOpenGL(window, height, width);

	scena.initScene();
	light1 = scena.getLight1();
	camera = scena.getCamera();
	models = scena.getModels();

	// setupCallbacks(window);

	Initialize_IMGUI(window);

	double prevFrame = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		double currentFrame = glfwGetTime();
		double deltaTime = currentFrame - prevFrame;
		// scena.update(deltaTime);
		double prevFrame = currentFrame;
		
		my_interface(window);

		scena.render(currentFrame, flagWF, flagAncora);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // Renderizza i dati di disegno di ImGui
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}
	close_GUI();
	scena.cleanStructure();
	glfwTerminate();
	return 0;
}
