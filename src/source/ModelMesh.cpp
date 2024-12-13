#include "ModelMesh.h"
#include "lib.h"
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

// Dichiarazioni funzioni di supporto

// Implementazioni funzioni ogetto

void ModelMesh::updateModelMatrix(mat4 M) {
	this->Model = M;
}

void ModelMesh::render() {

    // shading
    glUniform1i(this->uni_Shading, this->shading);
    
    // materiale
    glUniform3fv(this->uni_mat_ambient, 1, value_ptr(this->materiale.ambient));
    glUniform3fv(this->uni_mat_diffuse, 1, value_ptr(this->materiale.diffuse));
    glUniform3fv(this->uni_mat_specular, 1, value_ptr(this->materiale.specular));
    glUniform1f(this->uni_mat_shininess, this->materiale.shininess);
    glUniform1f(this->uni_ambientReflectance, this->mat_reflectance);
    
    // modello e vertici
    glUniformMatrix4fv(this->uni_Model, 1, GL_FALSE, value_ptr(this->Model));
    glBindVertexArray(this->VAO);
    
    // texture
    glUniform1i(this->uni_TextureYesNo, this->texture);     // dice se c'è o no
    // cout << this->texture << endl;
    if (this->texture) {
        // dice dove trovarla e la carica
        glUniform1i(this->uni_TextureLoc, 0);
        glBindTexture(GL_TEXTURE_2D, this->textureID);
    }

    // disegna
    glDrawElements(GL_TRIANGLES, (this->indices.size()) * sizeof(GLuint), GL_UNSIGNED_INT, 0);

    // disassocia questo VAO
    glBindVertexArray(0);
}

void ModelMesh::putTexture(bool activate, GLuint id) {
    this->texture = activate;
    this->textureID = id;
}