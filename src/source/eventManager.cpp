#include "eventManager.h"
#include "Camera.h"
#include "Gui.h"
#include "Model.h"

/* extern variables */
extern Camera* camera;
extern vector<Model*> models;
extern int height;
extern int width;
extern mat4 Projection;
extern mat4 View;

/* selezione */
int selected_obj = -1;
float raggio_sfera = 1.;

/* navigazione */
bool navigating = false;
int mov_x = 0;
int mov_y = 0;
int mov_z = 0;
double off_xpos;
double off_ypos;

GLFWwindow* this_window;

vec3 get_ray_from_mouse(float mouse_x, float mouse_y);
bool ray_sphere(vec3 O, vec3 d, vec3 sphere_centre_wor, float sphere_radius, float* intersection_distance);
void exitFromNavigation();

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int center_x;
int center_y;

void setupCallbacks(GLFWwindow* window) {
    this_window = window;
    center_x = floor((float)width * 0.5);
    center_y = floor((float)height * 0.5);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        if (!ImGui::IsAnyItemHovered()) {
            double xpos, ypos;
		    glfwGetCursorPos(window, &xpos, &ypos);
            vec3 ray_wor = get_ray_from_mouse(xpos, ypos);

            selected_obj = -1;
            float closest_intersection = 0.0f;
            for (int i = 0; i < models.size(); i++) {
                float t_dist = 0.0f;
                if (ray_sphere(camera->position, ray_wor, models[i]->ancora_world, raggio_sfera, &t_dist)) {
                    if (selected_obj == -1 || t_dist < closest_intersection) {
                        selected_obj = i;
                        closest_intersection = t_dist;
                    }
                }
            }
            if (selected_obj > -1) {
                exitFromNavigation();
                // cout << "Oggetto selezionato: " << models[selected_obj]->name.c_str() << endl;
            }
        }
	}
}


float Theta = -89.0;
float Phi = 0.0;
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    
    xpos = static_cast<float>(xpos);
    ypos = static_cast<float>(ypos);
    float xoffset, yoffset;
    float alfa = 0.05; //serve ridimensionare l'offset tra due posizioni successive del mosue
    ypos = height - ypos;

    float center_x = width / 2.0f;
    float center_y = height / 2.0f;

    xoffset = xpos - center_x;
    yoffset = ypos - center_y;

    if (navigating)
    {
        xoffset *= alfa;
        yoffset *= alfa;
        //Aggiorna gli angoli di rotazione orizzontale(Theta) e verticale(Phi) in base agli offset calcolati.
        // L'angolo Theta controlla la rotazione attorno all'asse y, mentre Phi controlla la rotazione attorno all'asse x.
        Theta += xoffset;   //Aggiorno l'angolo Theta sommandogli l'offset della posizione x del mouse
        Phi += yoffset;  //Aggiorno l'angolo Phi sommandogli l'offset della posizione y del mouse 

        // Facciamo si' che l'angolo di Phi vari tra -90 e 90, evitando così di capovolgere la telecamera.
        if (Phi > 89.0f)
            Phi = 89.0f;
        if (Phi < -89.0f)
            Phi = -89.0f;

        //Calcola le coordinate x, y e z di un punto sulla sfera unitaria, 
        // utilizzando gli angoli Theta e Phi convertiti in radianti.Questo punto rappresenta la direzione in cui punta la telecamera.
        vec3 front;
        front.x = cos(radians(Theta)) * cos(radians(Phi));
        front.y = sin(radians(Phi));
        front.z = sin(radians(Theta)) * cos(radians(Phi));
        //Normalizza il vettore front per ottenere un vettore unitario che rappresenta la nuova direzione della telecamera.

        camera->direction = normalize(front); //Aggiorno la direzione della telecamera
        camera->target = camera->position + camera->direction; //aggiorno il punto in cui guarda la telecamera

        //Disabilita il cursore del mouse per evitare che si muova fuori dalla finestra durante la navigazione.
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        //Riposiziona il cursore al centro della finestra per mantenere una navigazione fluida.
        glfwSetCursorPos(window, (int)center_x, (int)center_y);
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->fovY -= yoffset;
	if (camera->fovY < 10) {
		camera->fovY = 10;
	}
	else if (camera->fovY > 150) {
		camera->fovY = 150;
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_N && action == GLFW_PRESS) {
        navigating = !navigating;
        if (navigating) {
            mov_x = 0;
            mov_y = 0;
            mov_z = 0;
            selected_obj = -1;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPos(window, center_x, center_y);
        }
        else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        if (navigating) {
            exitFromNavigation();
        }
        if (selected_obj != -1) {
            selected_obj = -1;
        }
    }

    if (navigating) {
        if (key == GLFW_KEY_W && action == GLFW_PRESS) {
            mov_z--;
        }
        if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
            mov_z++;
        }

        if (key == GLFW_KEY_S && action == GLFW_PRESS) {
            mov_z++;
        }
        if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
            mov_z--;
        }

        if (key == GLFW_KEY_D && action == GLFW_PRESS) {
            mov_x++;
        }
        if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
            mov_x--;
        }

        if (key == GLFW_KEY_A && action == GLFW_PRESS) {
            mov_x--;
        }
        if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
            mov_x++;
        }

        if (key == GLFW_KEY_D && action == GLFW_PRESS) {
            mov_x++;
        }
        if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
            mov_x--;
        }

        if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) {
            mov_y--;
        }
        if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE) {
            mov_y++;
        }

        if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
            mov_y++;
        }
        if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
            mov_y--;
        }
    }
}







vec3 get_ray_from_mouse(float mouse_x, float mouse_y) {
    //La funzione get_ray_from_mouse calcola il raggio che parte dalla posizione della telecamera
    //  e passa attraverso il punto sullo schermo corrispondente alla posizione del mouse.
    mouse_y = height - mouse_y;

    // mappiamo le coordinate di viewport del mouse [0,width], [0,height] in coordinate normalizzate [-1,1]  
    float ndc_x = (2.0f * mouse_x) / width - 1.0;
    float ndc_y = (2.0f * mouse_y) / height - 1.0;

    //Nello spazio di clippling z più piccola, oggetto più vicino all'osservatore, quindi si pone la z a - 1, 
    // posizionando il punto sul piano vicino del frustum.
    // Questo significa che il raggio che stiamo calcolando partirà dalla telecamera e si dirigerà 
    // verso il punto più vicino visibile sullo schermo.
    float ndc_z = -1.0f;

    // Coordinate nel clip space 
    vec4 P_clip = vec4(ndc_x, ndc_y, ndc_z, 1.0);

    // Le coordinate nell' eye space si ottengono premoltiplicando per l'inversa della matrice Projection.
    vec4 ViewModelp = inverse(Projection) * P_clip;

    // le coordinate nel world space: si ottengono premoltiplicando per l'inversa della matrice di Vista 
    ViewModelp.w = 1;
    vec4 Pw = inverse(View) * ViewModelp;

    //Il vettore del raggio viene calcolato sottraendo la posizione della telecamera SetupTelecamera.position dal punto Pw nel world space.
    vec3 ray_wor = normalize(vec3(Pw) - vec3(camera->position));

    return ray_wor;
}

/* controlla se un raggio interseca una sfera. In caso negativo, restituisce false. Rigetta
 le intersezioni dietro l'origine del raggio, e pone  intersection_distance all'intersezione p iù vicina.
*/
bool ray_sphere(vec3 O, vec3 d, vec3 sphere_centre_wor, float sphere_radius, float* intersection_distance) {

    //Calcoliamo O-C
    vec3 dist_sfera = O - sphere_centre_wor;
    float b = dot(dist_sfera, d);
    float cc = dot(dist_sfera, dist_sfera) - sphere_radius * sphere_radius;

    float delta = b * b - cc;

    if (delta < 0)  //Il raggio non interseca la sfera
        return false;
    //Calcolo i valori di t per cui il raggio interseca la sfera e restituisco il valore dell'intersezione 
    //più vicina all'osservatore (la t più piccola)
    if (delta > 0.0f) {
        //calcola le due intersezioni
        float t_a = -b + sqrt(delta);
        float t_b = -b - sqrt(delta);
        *intersection_distance = t_b;

        //Caso di intersezioni dietro l'osservatore
        if (t_a < 0.0) {
            if (t_b < 0)
                return false;
        }

        return true;
    }
    //Caso in cui il raggio è tangente alla sfera: un interesezione con molteplicità doppia.
    if (delta == 0) {
        float t = -b + sqrt(delta);
        if (t < 0)
            return false;
        *intersection_distance = t;
        return true;
    }

    return false;
}

void exitFromNavigation() {
    navigating = false;
    glfwSetInputMode(this_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}