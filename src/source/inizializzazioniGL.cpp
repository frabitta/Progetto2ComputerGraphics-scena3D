#include "lib.h"
#include "inizializzazioniGL.h"
#include <GL/gl.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
// Dichiarazioni funzioni di supporto

/* lettura dei file di shader */
char* readShaderSource(const char* shaderFile);
/* compila la shader caricata */
int compileShader(GLuint shaderId, const GLchar* shader, string fileName);
/* caricamento di un file di texture */
unsigned int loadTexture(char const* path, int flip);
/* caricamento di un file cubemap */
unsigned int loadCubemap(vector<std::string> faces, int flip);

// Implementazioni funzioni di libreria

int INIT_finestraOpenGL(GLFWwindow*& window, const int height, const int width) {
	/* Initialize the library */
	if (!glfwInit())   //se glfwInit() dà valore falso, return -1
		return -1;

	//Imposta le proprietà del contesto e del profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	//Abilita il double buffering
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Scena", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create the window !" << std::endl;
		glfwTerminate(); //Libera le risorse allcoata da glfwInit
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window); //crea il context corrente e lo associa a window. In opengl un rendering context è una macchina astati che memorizza tutte le informazioni necessarie e le risorse per il rendering grafico

	//verifica se la libreria GLAD è riuscita a caricare correttamente tutti i puntatori 
	// alle funzioni OpenGL necessarie.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failde to load opengl function pointers !" << std::endl;
		glfwTerminate();
		return -1;
	}

	/* trasparenza */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return 0;
}

int INIT_Cubemap(string fileName) {
	string imagePath = cubeMapPath + fileName;
	int cubemapTexture;
	vector<std::string> faces {
		imagePath + "/posx.jpg",		// right
		imagePath + "/negx.jpg",		// left
		imagePath + "/posy.jpg",		// top
		imagePath + "/negy.jpg",		// bottom
		imagePath + "/posz.jpg",		// front
		imagePath + "/negz.jpg"};	// back
	return cubemapTexture = loadCubemap(faces, 0);
}

int INIT_Texture(string fileName, int flip) {
	int texture;
	string imagePath = texturePath + fileName;
	texture = loadTexture(imagePath.c_str(), flip);
	return texture;
}

GLuint INIT_shaderProg(const char* vertexFilename, const char* fragmentFilename) {
	GLenum ErrorCheckValue = glGetError();

	const string vertexPath = shaderPath + vertexFilename;
	const  GLchar* VertexShader = readShaderSource(vertexPath.c_str());
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	compileShader(vertexShaderId, VertexShader, vertexFilename);

	const string fragmentPath = shaderPath + fragmentFilename;
	const GLchar* FragmentShader = readShaderSource(fragmentPath.c_str());
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	compileShader(fragmentShaderId, FragmentShader, fragmentFilename);

	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programId, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	return programId;
}


// Definizioni funzioni di supporto

#pragma warning(disable:4996)
char* readShaderSource(const char* shaderFile) {
	FILE* fp = fopen(shaderFile, "rb");

	if (fp == NULL) { return NULL; }

	fseek(fp, 0L, SEEK_END);
	long size = ftell(fp);

	fseek(fp, 0L, SEEK_SET);
	char* buf = new char[size + 1];
	fread(buf, 1, size, fp); // ho aggiunto un -1 per evitare buffer overrun, non so se serve

	buf[size] = '\0';
	fclose(fp);

	return buf;
}

int compileShader(GLuint shaderId, const GLchar* shader, string fileName) {
	int success;
	char infoLog[512];

	glShaderSource(shaderId, 1, (const char**)&shader, NULL);
	glCompileShader(shaderId);
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
		std::cout << "ERROR: Compilation failed of shader '" << fileName << "'\nDetails:" << infoLog << std::endl;
	}
	return success;
}

unsigned int loadTexture(char const* path, int flip) {
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	stbi_set_flip_vertically_on_load(flip);
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format = GL_RGBA;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

unsigned int loadCubemap(vector<std::string> faces, int flip) {
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++) {
		stbi_set_flip_vertically_on_load(flip);
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data) {
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				width,
				height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				data);
			stbi_image_free(data);
		} else {
			std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}