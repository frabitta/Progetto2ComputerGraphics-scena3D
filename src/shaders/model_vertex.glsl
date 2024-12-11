#version 330 core
layout (location = 0) in vec3 aPos;         // position of the vertex
layout (location = 1) in vec4 aColor;       // color of the vertex
layout (location = 2) in vec3 vertexNormal; // normal to the vertex
layout (location = 3) in vec2 coord_st;     // Attributo texture -------- TODO

#define NUM_LIGHTS 2

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
struct Wave {
    float Amp;
    float Off;
    float Speed;
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
uniform PointLight light[NUM_LIGHTS];
uniform Material material;
uniform int textureSi;
uniform Wave wave;


out vec4 ourColor;      // output color to the fragment shader
out vec2 frag_coord;    // fragment coordinate
out int isGouraud;     // flag per il fragment di elaborare il modello d'illuminazione
out int mixTexture;

// dati da passare per campionare il riflesso dell'ambiente
out vec3 pos;
out vec3 cameraPos;
out vec3 normal;

float strenght = 0.1;

float func(float amp, float x, float off, float speed) {
    off += time;
    off *= speed;
    // float res = pow(sin(x+off),2)*(-0.8) + pow(sin(x+0.3+off),4)*0.9 + pow(sin(x+0.6+off),3) * 0.2;
    float res = sin(x+off) + sin(2*x+off);
    res *= amp;
    return res;
}

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
        float luminosity = 0;
        for (int i = 0; i<NUM_LIGHTS; i++) {
            luminosity = dot(vertexNormal, light[i].position-aPos) * light[i].power * strenght * (1/length(light[i].position-aPos));
        }
        luminosity /= NUM_LIGHTS;
        ourColor = aColor * luminosity;
    }

    if (shadingType == PHONG || shadingType == BLINN_PHONG) {
        //Trasformare le coordinate del vertice da elaborare (aPos) in coordinate di vista
        vec4 eyePosition = View * Model * vec4(aPos, 1.0);

        vec3 ambient = vec3(0.,0.,0.);
        vec3 diffuse = vec3(0.,0.,0.);
        vec3 specular = vec3(0.,0.,0.);
        for (int i = 0; i<NUM_LIGHTS; i++) {
            float distanceDamping = 1/length(light[i].position-aPos);

            //Trasformiamo la posizione della luce nelle coordinate di vista
            vec4 eyeLightPos = View * vec4(light[i].position, 1.0);

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
            ambient += strenght * light[i].power * material.ambient * distanceDamping;
        
            //diffuse
            float coseno_angolo_theta = max(dot(L, N), 0);
            diffuse += light[i].power * light[i].color * coseno_angolo_theta * material.diffuse * distanceDamping;
        
            //speculare
            float coseno_angolo;
            if (shadingType == PHONG) {
                float coseno_alfa = pow(max(dot(V, R), 0), material.shininess);
                coseno_angolo = coseno_alfa;
            } else {
                float coseno_beta = pow(max(dot(H, N), 0), material.shininess);
                coseno_angolo = coseno_beta;
            }
            specular += light[i].power * light[i].color * coseno_angolo * material.specular * distanceDamping;   
        }
        ambient /= NUM_LIGHTS;
        diffuse /= NUM_LIGHTS;
        specular /= NUM_LIGHTS;
        ourColor = vec4(ambient + diffuse + specular, 1.0);
    }
    
    if (textureSi != 0) {
        frag_coord = coord_st;
    }
    
    vec4 v = vec4(aPos, 1.0);

    if (wave.Amp != 0) {
        v.z += func(wave.Amp, v.x*0.7+v.y*0.3, wave.Off, wave.Speed);
        v.y += func(wave.Amp / 3, v.x, wave.Off, wave.Speed);
    }

    gl_Position = Projection*View*Model*v;
}