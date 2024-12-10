#pragma once
#include "lib.h"
#include "Model.h"
#include "Camera.h"
#include "Light.h"

class Scena {
public:
	/* inizializza la scena */
	void initScene();
	/* ripristina la scena alla situazione iniziale*/
	void resetScene();
	/* restituisce puntatori a tutti i modelli della scena*/
	vector<Model*> getModels();
	/* restituisce un puntatore alla telecamera*/
	Camera* getCamera();
	/* restituisce un puntatore alla luce*/
	Light* getLight1();
	/* restituisce un puntatore alla luce*/
	Light* getLight2();
	/* renderizza la scena */
	void render(double time, bool flagWireFrame, bool flagAnchorPoints);
	/* distrugge la scena */
	void cleanStructure();
	/* aggiorna la scena */
	void update(double deltaTime);
private:
	// void loadShaders();
	Camera* camera;
	Light* light1;
	Light* light2;
	vector<Model*> models;
};