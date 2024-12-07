#pragma once
#include "lib.h"

class Light {
public:
	/* resetta i parametri */
	void initLight();

	vec3 position;
	vec3 color;
	float power;
};