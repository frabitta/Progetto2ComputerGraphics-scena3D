#version 330 core
layout (location = 0) in vec3 aPos;   // Attributo Posizione

uniform mat4 Proj;
uniform mat4 View;

out vec3 TexCoords;

void main() {
  TexCoords = aPos;
  
  //Matrice di vista a cui si toglie il contributo della traslazione
  mat4 Static_View=mat4(mat3(View));
  gl_Position = Proj * Static_View * vec4(aPos, 1.0);
}
