#include "Mesh.h"

Mesh::Mesh() {
    this->nome = "nuova mesh";
}

void Mesh::INIT_VAO()
{
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    //Genero , rendo attivo, riempio il VBO della geometria dei vertici
    glGenBuffers(1, &this->VBO_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO_vertices);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(vec3), this->vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    //Genero , rendo attivo, riempio il VBO dei colori
    glGenBuffers(1, &this->VBO_colors);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO_colors);
    glBufferData(GL_ARRAY_BUFFER, this->colors.size() * sizeof(vec4), this->colors.data(), GL_STATIC_DRAW);
    //Adesso carico il VBO dei colori nel layer 2
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    //Genero , rendo attivo, riempio il VBO delle normali
    glGenBuffers(1, &this->VBO_normals);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO_normals);
    glBufferData(GL_ARRAY_BUFFER, this->normals.size() * sizeof(vec3), this->normals.data(), GL_STATIC_DRAW);
    //Adesso carico il VBO delle NORMALI nel layer 2
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(2);

    //Genero , rendo attivo, riempio il VBO delle texture
    glGenBuffers(1, &this->VBO_coord_texture);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO_coord_texture);
    glBufferData(GL_ARRAY_BUFFER, this->texCoords.size() * sizeof(vec2), this->texCoords.data(), GL_STATIC_DRAW);
    //Adesso carico il VBO delle texture nel layer 3
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(3);

    //EBO di tipo indici
    glGenBuffers(1, &this->EBO_indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO_indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), this->indices.data(), GL_STATIC_DRAW);
}
