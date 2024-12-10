#pragma once
#include "lib.h"

class BoundingBox {
public:
	bool checkCollision(vec3 p);
	void generateFromVertices(vector<vec3> vertices);

	vec3 p1 = vec3(0.,0.,0.);
	vec3 p2 = vec3(0.,0.,0.);
};
