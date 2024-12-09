#pragma once
#include "lib.h"

class Mesh {
public:
    Mesh();

    void INIT_VAO();
    // virtual void render() = 0;

    string nome;                // Nome della mesh (utile per l'identificazione)

    // dati locali
    vector<vec3> vertices;      // Vettore contenente le coordinate dei vertici della mesh
    vector<vec4> colors;        // Vettore contenente i colori associati a ciascun vertice
    vector<GLuint> indices;     // Vettore contenente gli indici dei vertici che definiscono i triangoli (o altre primitive)
    vector<vec3> normals;       // Vettore contenente i vettori normali ai vertici (utili per il calcolo dell'illuminazione)
    vector<vec2> texCoords;     // Vettore contenente le coordinate delle texture per ciascun vertice

    // buffers
    GLuint VAO;                 // Vertex Array Object: identificatore dell'oggetto che contiene tutte le informazioni sulla mesh
    GLuint VBO_vertices;        // Vertex Buffer Object per le coordinate dei vertici
    GLuint VBO_colors;          // Vertex Buffer Object per i colori dei vertici
    GLuint VBO_normals;         // Vertex Buffer Object per le normali dei vertici
    GLuint EBO_indices;         // Element Buffer Object per gli indici dei vertici
    GLuint VBO_coord_texture;   // Vertex Buffer Object per le coordinate delle texture
};