#include "Camera.h"

void Camera::initCamera() {
    this->position = vec3(0.,0.,10.);
    this->target = vec3(0.,0.,0.);
    this->direction = this->target - this->position;
    this->upVector = vec3(0.,1.,0.);
    this->fovY = 50.f;
    this->aspect = 16.f/9.f;
    this->near_plane = 0.1f;
    this->far_plane = 2000.f;
}