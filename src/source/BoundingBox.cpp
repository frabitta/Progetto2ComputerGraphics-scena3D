#include "BoundingBox.h"

bool BoundingBox::checkCollision(vec3 p) {
	return this->p1.x < p.x && p.x < this->p2.x
		&& this->p1.y < p.y && p.y < this->p2.y
		&& this->p1.z < p.z && p.z < this->p2.z;
}

void BoundingBox::generateFromVertices(vector<vec3> vertices) {
	float min_x = 999999., min_y = 999999., min_z = 999999.;
	float max_x = -999999., max_y = -999999., max_z = -999999.;

	for (int i = 0; i < vertices.size(); i++) {
		vec3 v = vertices[i];
		if (v.x > max_x) {
			max_x = v.x;
		}
		if (v.x < min_x) {
			min_x = v.x;
		}
		if (v.y > max_y) {
			max_y = v.y;
		}
		if (v.y < min_y) {
			min_y = v.y;
		}
		if (v.z > max_z) {
			max_z = v.z;
		}
		if (v.z < min_z) {
			min_z = v.z;
		}
	}

	this->p1 = vec3(min_x, min_y, min_z);
	this->p2 = vec3(max_x, max_y, max_z);
}
