#include "Gui.h"
#include "Model.h"
#include "Light.h"
#include "Camera.h"
#include "Materiale.h"

extern Light* light1;
extern Camera* camera;
extern vector<Model*> models;
extern bool flagWF;
extern bool flagAncora;

extern int selected_obj;

extern Materiale mat_plasticaRossa;
extern Materiale mat_ottone;
extern Materiale mat_smeraldo;
extern Materiale mat_neve;
extern Materiale mat_giallo;
extern Materiale mat_rosa;
extern Materiale mat_marrone;

float posL1[3];
float coloreL1[3];

void Initialize_IMGUI(GLFWwindow* window) {
    IMGUI_CHECKVERSION(); // Verifica la compatibilità della versione di ImGui

    // Create ImGui context
    ImGui::CreateContext(); // Crea un nuovo contesto ImGui

    // Get ImGui IO object to configure options
    ImGuiIO& io = ImGui::GetIO(); // Ottieni l'oggetto IO per configurare opzioni come input, font e stili
    io.FontGlobalScale = 1.4f;  //Dimensione del font

    // Set dark theme
    ImGui::StyleColorsDark(); // Imposta il tema scuro per l'interfaccia

    // Initialize ImGui for GLFW and OpenGL 3.3
    ImGui_ImplGlfw_InitForOpenGL(window, true); // Inizializza ImGui per GLFW
    ImGui_ImplOpenGL3_Init("#version 330 core"); // Inizializza ImGui per OpenGL 3.3

    posL1[0] = light1->position.x;
    posL1[1] = light1->position.y;
    posL1[2] = light1->position.z;

    coloreL1[0] = light1->color.r;
    coloreL1[1] = light1->color.g;
    coloreL1[2] = light1->color.b;
}

void my_interface(GLFWwindow* window) {
    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame(); // Inizia un nuovo frame per ImGui
    ImGui::NewFrame();

    // Create a window for color settings
    ImGui::Begin("Impostazioni", NULL, //il secondo parametro viene utilizzato per controllare se la finestra dovrebbe essere aperta o chiusa. 
        // NULL significa che la finestra sarà sempre aperta.
        ImGuiWindowFlags_NoResize | //   Impedisce all'utente di ridimensionare la finestra.
        ImGuiWindowFlags_AlwaysAutoResize |  //La finestra si ridimensionerà automaticamente per adattarsi al contenuto. 
        ImGuiWindowFlags_NoBackground |  //Disabilita lo sfondo della finestra, rendendola trasparente.
        ImGuiWindowFlags_NoTitleBar |    //Nasconde la barra del titolo della finestra.
        ImGuiWindowFlags_NoMove          //Impedisce all'utente di spostare la finestra
    );

    ImGui::LabelText("Light 1","");
    ImGui::SliderFloat3("pos", posL1, -50, +50);
    light1->position = vec3(posL1[0], posL1[1], posL1[2]);
    ImGui::ColorEdit3("color", coloreL1, 0);
    light1->color = vec3(coloreL1[0], coloreL1[1], coloreL1[2]);
    ImGui::SliderFloat("power", &light1->power, 0, 10);
    ImGui::NewLine();
    /*
    ImGui::LabelText("Light 2", "");
    ImGui::SliderFloat3("pos", posL2, -50, +50);
    light2->position = vec3(posL2[0], posL2[1], posL2[2]);
    ImGui::ColorEdit3("color", coloreL2, 0);
    light2->color = vec3(coloreL2[0], coloreL2[1], coloreL2[2]);
    ImGui::SliderFloat("power", &light2->power, 0, 10);
    */
    ImGui::NewLine();
    ImGui::Checkbox("Wireframe", &flagWF);
    ImGui::Checkbox("VisualizzaAncora ", &flagAncora);

    ImGui::End(); // Termina la finestra


    if (selected_obj >= 0 && selected_obj < models.size()) {
        ImVec2 windowSize = ImGui::GetIO().DisplaySize;
        ImVec2 windowPos = ImVec2(windowSize.x * 0.75f, windowSize.y * 0.5f);
        ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);

        Model* selectedModel = models[selected_obj];
        ImGui::Begin(selectedModel->name.c_str(), NULL, //il secondo parametro viene utilizzato per controllare se la finestra dovrebbe essere aperta o chiusa.
            ImGuiWindowFlags_NoResize | //   Impedisce all'utente di ridimensionare la finestra.
            ImGuiWindowFlags_AlwaysAutoResize |  //La finestra si ridimensionerà automaticamente per adattarsi al contenuto. 
            ImGuiWindowFlags_NoMove          //Impedisce all'utente di spostare la finestra
        );

        // posizione
        float pos[3] = {selectedModel->posizione.x, selectedModel->posizione.y, selectedModel->posizione.z };
        ImGui::SliderFloat3("pos", pos, -20, +20);
        selectedModel->goToPos(vec3(pos[0], pos[1], pos[2]));
        // rotazione
        float angle = selectedModel->angolo;
        float rot_vector[3] = { selectedModel->rotation_axis.x, selectedModel->rotation_axis.y, selectedModel->rotation_axis.z };
        ImGui::SliderFloat("rot angle", &angle, 0, 360);
        // ImGui::SameLine();
        ImGui::SliderFloat3("rot axis", rot_vector, 0, 1);
        selectedModel->rotate(angle, vec3(rot_vector[0], rot_vector[1], rot_vector[2]));
        // scaling
        float scale[3] = {selectedModel->dimensioni.x, selectedModel->dimensioni.y, selectedModel->dimensioni.z };
        ImGui::SliderFloat3("scale", scale, 0, 50);
        selectedModel->scale(vec3(scale[0], scale[1], scale[2]));
        // reflectance
        /*
        float refl = 0;
        ImGui::SliderFloat("reflectance", &refl, 0, 1);
        selectedModel->setReflectance(refl);
        */
        // shading
        if (ImGui::BeginMenu("Shader")) {
            if (ImGui::MenuItem("Pass through")) {
                selectedModel->setShading(ShadingType::PASS_THROUGH);
            }
            if (ImGui::MenuItem("Phong")) {
                selectedModel->setShading(ShadingType::PHONG);
            }
            if (ImGui::MenuItem("Blinn-Phong")) {
                selectedModel->setShading(ShadingType::BLINN_PHONG);
            }
            ImGui::EndMenu();
        }
        // materiale se geometria
        if (selectedModel->type == Type::Primitives) {
            if (ImGui::BeginMenu("Materiale")) {
                if (ImGui::MenuItem("Plastica rossa")) {
                    selectedModel->setGeometryMaterial(mat_plasticaRossa);
                }
                if (ImGui::MenuItem("Ottone")) {
                    selectedModel->setGeometryMaterial(mat_ottone);
                }
                if (ImGui::MenuItem("Smeraldo")) {
                    selectedModel->setGeometryMaterial(mat_smeraldo);
                }
                if (ImGui::MenuItem("Neve")) {
                    selectedModel->setGeometryMaterial(mat_neve);
                }
                if (ImGui::MenuItem("Giallo")) {
                    selectedModel->setGeometryMaterial(mat_giallo);
                }
                if (ImGui::MenuItem("Rosa")) {
                    selectedModel->setGeometryMaterial(mat_rosa);
                }
                if (ImGui::MenuItem("Marrone")) {
                    selectedModel->setGeometryMaterial(mat_marrone);
                }
                ImGui::EndMenu();
            }
        }

        ImGui::End();
    }

    // Render ImGui
    ImGui::Render(); // Renderizza gli elementi dell'interfaccia ImGui
}

void close_GUI() {
    ImGui_ImplOpenGL3_Shutdown(); // Chiude l'integrazione con OpenGL
    ImGui_ImplGlfw_Shutdown(); // Chiude l'integrazione con GLFW
    ImGui::DestroyContext(); // Distrugge il contesto ImGui
}
