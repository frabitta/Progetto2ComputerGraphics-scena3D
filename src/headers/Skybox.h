#pragma once
#include "lib.h"
#include "Mesh.h"

class Skybox: public Mesh {
public:
    void createSkybox(string cubeMapName);
    void render();

    int cubemap;
};