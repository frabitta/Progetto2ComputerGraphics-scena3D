#pragma once
#include "lib.h"

class Camera {
public:
    /* resetta i parametri */
	void initCamera();
    
    // Proprietà telecamera
    vec3 position;  // Posizione della camera nello spazio 3D
    vec3 target;    // Punto verso cui la camera è puntata
    vec3 upVector;  // Vettore che indica la direzione "up" della camera
    vec3 direction; // Vettore che indica la direzione di visione della camera
    // Proprietà proiezione
    float fovY;         // Campo visivo verticale in gradi
    float aspect;       // Rapporto tra larghezza e altezza del viewport
    float near_plane;   // Distanza del piano di clipping vicino
    float far_plane;    // Distanza del piano di clipping lontano
};