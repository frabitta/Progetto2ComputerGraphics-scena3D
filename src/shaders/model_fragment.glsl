#version 330 core
in vec4 ourColor;
in vec2 frag_coord;
flat in int isGouraud;

// identificativo della texture unit che gestisce questa texture
uniform int textureSi;
uniform sampler2D textureLoc;

out vec4 FragColor;  

void main()
{
    if (isGouraud != 0) {
        /* Elabora modello di illuminazione */
        // modifica 'ourColor'
    }

    if (textureSi != 0) {
    /* il colore in uscita è un mix tra il colore del vertice e il colore derivante dalla texture
    * la funzione texture prende la texture specificata nell'unità 'textureLoc' alle coordinate 'frag_coord' */
        FragColor = mix(ourColor, texture(textureLoc, frag_coord), 0.5);
    } else {
        FragColor = ourColor;
    }
}