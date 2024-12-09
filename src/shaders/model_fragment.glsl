#version 330 core
in vec4 ourColor;
in vec2 frag_coord;
flat in int isGouraud;

// identificativo della texture unit che gestisce questa texture
flat in int mixTexture;
uniform sampler2D textureLoc;

uniform float reflectance;
uniform samplerCube skybox;
in vec3 pos;
in vec3 cameraPos;
in vec3 normal;

out vec4 FragColor;  

void main()
{
    if (mixTexture != 0) {
    /* il colore in uscita è un mix tra il colore del vertice e il colore derivante dalla texture
    * la funzione texture prende la texture specificata nell'unità 'textureLoc' alle coordinate 'frag_coord' */
        FragColor = mix(ourColor, texture(textureLoc, frag_coord), 0.5);
    } else {
        FragColor = ourColor;
    }

    vec3 I = normalize(pos - cameraPos);
    vec3 R = reflect(I, normalize(normal));
    vec4 currentCol = FragColor;
    if (reflectance > 0) {
        FragColor = mix(currentCol, texture(skybox, R), reflectance);
    }
}