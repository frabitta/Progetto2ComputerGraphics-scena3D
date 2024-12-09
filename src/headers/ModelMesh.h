#pragma once
#include "lib.h"
#include "Materiale.h"
#include "Mesh.h"

typedef enum {
    PASS_THROUGH,
    TOON,
    PHONG,
    BLINN_PHONG,
    GOURAUD
} ShadingType;

class ModelMesh : public Mesh {
public:
    void updateModelMatrix(mat4 M);
    void render();
    void putTexture(bool activate, GLuint id);
    
    // dati mondo
    mat4 Model = mat4(1.0);                 // Matrice di modellazione per applicare trasformazioni alla mesh
        
    // aspetto shader
    ShadingType shading;        // Tipo di shading utilizzato
    Materiale materiale;        // Materiale del modello
    float mat_reflectance = 0.;
    bool texture;
    GLuint textureID;

    // shader uniforms
    GLint  uni_Model;
    GLint  uni_Shading;
    GLint  uni_mat_ambient;
    GLint  uni_mat_diffuse;
    GLint  uni_mat_specular;
    GLint  uni_mat_shininess;
    GLint  uni_TextureYesNo;
    GLint  uni_TextureLoc;
    GLint uni_ambientReflectance;
};
