#include "Gui.h"
#include "Model.h"
#include "Light.h"
#include "Camera.h"

extern Light* light1;
extern Camera* camera;
extern vector<Model*> models;
extern bool flagWF;
extern bool flagAncora;

float posL1[3];
float coloreL1[3];

void Initialize_IMGUI(GLFWwindow* window) {
    IMGUI_CHECKVERSION(); // Verifica la compatibilità della versione di ImGui

    // Create ImGui context
    ImGui::CreateContext(); // Crea un nuovo contesto ImGui

    // Get ImGui IO object to configure options
    ImGuiIO& io = ImGui::GetIO(); // Ottieni l'oggetto IO per configurare opzioni come input, font e stili
    io.FontGlobalScale = 2.0f;  //Dimensione del font

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
    // Render ImGui
    ImGui::Render(); // Renderizza gli elementi dell'interfaccia ImGui
}

void close_GUI() {
    ImGui_ImplOpenGL3_Shutdown(); // Chiude l'integrazione con OpenGL
    ImGui_ImplGlfw_Shutdown(); // Chiude l'integrazione con GLFW
    ImGui::DestroyContext(); // Distrugge il contesto ImGui
}
