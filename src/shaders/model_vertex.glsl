#version 330 core
layout (location = 0) in vec3 aPos;         // position of the vertex
layout (location = 1) in vec4 aColor;       // color of the vertex
layout (location = 2) in vec3 vertexNormal; // normal to the vertex
layout (location = 3) in vec2 coord_st;     // Attributo texture -------- TODO

struct PointLight {
	vec3 position;
	vec3 color;
	float power;
};
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

int PASS_THROUGH=0;
int TOON = 1;
int PHONG = 2;
int BLINN_PHONG = 3;
int GOURAUD = 4;

uniform float time;
uniform mat4 Projection;
uniform mat4 Model;
uniform mat4 View;
uniform vec3 ViewPos;
uniform int shadingType;
uniform PointLight light;
uniform Material material;
uniform int textureSi;

out vec4 ourColor;      // output color to the fragment shader
out vec2 frag_coord;    // fragment coordinate
out int isGouraud;     // flag per il fragment di elaborare il modello d'illuminazione
out int mixTexture;

// dati da passare per campionare il riflesso dell'ambiente
out vec3 pos;
out vec3 cameraPos;
out vec3 normal;

float strenght = 0.1;

void main()
{
    float offset = time;
    isGouraud = 0;
    ourColor = aColor;
    frag_coord = vec2(0,0);
    mixTexture = textureSi;

    pos = vec3(Model*vec4(aPos, 1.0));
    cameraPos = ViewPos;

    //trasformare le normali nel vertice in esame nel sistema di coordinate di vista
    vec3 N = normalize(transpose(inverse(mat3(View * Model))) * vertexNormal);
    normal = N;

    if (shadingType == TOON) {
        float luminosity = dot(vertexNormal, light.position-aPos);
        float damping = 0.5;
        ourColor = aColor * luminosity * light.power * damping * (1/length(light.position-aPos));
    }

    if (shadingType == PHONG || shadingType == BLINN_PHONG) {
        //Trasformare le coordinate del vertice da elaborare (aPos) in coordinate di vista
        vec4 eyePosition = View * Model * vec4(aPos, 1.0);

        //Trasformiamo la posizione della luce nelle coordinate di vista
        vec4 eyeLightPos = View * vec4(light.position, 1.0);

        //Calcoliamo la direzione della luce L, la direzione riflessione R e di vista
        vec3 V = normalize(ViewPos - eyePosition.xyz);
        vec3 L = normalize((eyeLightPos - eyePosition).xyz);

        vec3 R; vec3 H;
        if (shadingType == PHONG) {
            R = reflect(-L, N);  //Costruisce la direzione riflessa di L rispesso alla normale
        } else {
            H = normalize(L+V);  //Costruisce la direzione riflessa di L rispesso alla normale
        }

        //ambientale
        vec3 ambient = strenght * light.power * material.ambient;
        
        //diffuse
        float coseno_angolo_theta = max(dot(L, N), 0);
        vec3 diffuse = light.power * light.color * coseno_angolo_theta * material.diffuse;
        
        //speculare
        float coseno_angolo;
        if (shadingType == PHONG) {
            float coseno_alfa = pow(max(dot(V, R), 0), material.shininess);
            coseno_angolo = coseno_alfa;
        } else {
            float coseno_beta = pow(max(dot(H, N), 0), material.shininess);
            coseno_angolo = coseno_beta;
        }
        vec3 specular = light.power * light.color * coseno_angolo * material.specular;
        ourColor = vec4(ambient + diffuse + specular, 1.0);
    } else if (shadingType == GOURAUD) {
        // TODO ---------------------
        isGouraud = 1;
    }
    
    if (textureSi != 0) {
        frag_coord = coord_st;
    }
    
    gl_Position = Projection*View*Model*vec4(aPos, 1.0);
}  