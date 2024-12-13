#include "lib.h"
#include "Scena.h"
#include "inizializzazioniGL.h"
#include "Gui.h"
#include "Model.h"
#include "Light.h"
#include "Camera.h"
#include "eventManager.h"

// Variabili Globali
const string shaderPath = "src/shaders/";
const string texturePath = "resources/textures/";
const string cubeMapPath = "resources/cubeMaps/";
const string objPath = "resources/models/";

int height;
int width;
GLFWwindow* window;

Light* light1;
Light* light2;
Camera* camera;
vector<Model*> models;
bool flagWF = false;
bool flagAncora = false;

// Main
int main(void) {
	Scena scena;
	height = 900;
	width = 1600;

	INIT_finestraOpenGL(window, height, width);

	scena.initScene();
	light1 = scena.getLight1();
	light2 = scena.getLight2();
	camera = scena.getCamera();
	models = scena.getModels();

	setupCallbacks(window);
	Initialize_IMGUI(window);

	double prevFrame = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		double currentFrame = glfwGetTime();
		double deltaTime = currentFrame - prevFrame;
		scena.update(deltaTime);
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
