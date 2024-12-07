#pragma once
#include "lib.h"
#include "Mesh.h"

enum Geometry {
	CUBO,
	PIANO,
	PIANO_SUDDIVISO,
	PIRAMIDE,
	SFERA,
	CILINDRO,
	TORO,
	CONO
};

void crea_cubo(Mesh* mesh, vec4 colore);
void crea_piano(Mesh* mesh, vec4 colore);
void crea_piano_suddiviso(Mesh* mesh, vec4 colore);
void crea_piramide(Mesh* mesh, vec4 colore);
void crea_sfera(Mesh* mesh, vec4 colore);
void crea_cilindro(Mesh* mesh, vec4 colore);
void crea_toro(Mesh* mesh, vec4 colore);
void crea_cono(Mesh* mesh, vec4 colore);