#pragma once
#include "lib.h"
#include "Materiale.h"


typedef enum {
    PASS_THROUGH,
    TOON,
    PHONG,
    BLINN_PHONG,
    GOURAUD
} ShadingType;

class Mesh {
public:
    Mesh();

    void updateModelMatrix(mat4 M);
    void renderMesh();
    void INIT_vao();

    string nome;                // Nome della mesh (utile per l'identificazione)
    
    // dati locali
    vector<vec3> vertices;      // Vettore contenente le coordinate dei vertici della mesh
    vector<vec4> colors;        // Vettore contenente i colori associati a ciascun vertice
    vector<GLuint> indices;     // Vettore contenente gli indici dei vertici che definiscono i triangoli (o altre primitive)
    vector<vec3> normals;       // Vettore contenente i vettori normali ai vertici (utili per il calcolo dell'illuminazione)
    vector<vec2> texCoords;     // Vettore contenente le coordinate delle texture per ciascun vertice
    
    // dati mondo
    mat4 Model = mat4(1.0);                 // Matrice di modellazione per applicare trasformazioni alla mesh
    
    // buffers
    GLuint VAO;                 // Vertex Array Object: identificatore dell'oggetto che contiene tutte le informazioni sulla mesh
    GLuint VBO_vertices;        // Vertex Buffer Object per le coordinate dei vertici
    GLuint VBO_colors;          // Vertex Buffer Object per i colori dei vertici
    GLuint VBO_normals;         // Vertex Buffer Object per le normali dei vertici
    GLuint EBO_indices;         // Element Buffer Object per gli indici dei vertici
    GLuint VBO_coord_texture;   // Vertex Buffer Object per le coordinate delle texture
    
    // aspetto shader
    ShadingType shading;        // Tipo di shading utilizzato
    Materiale materiale;        // Materiale del modello
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
};