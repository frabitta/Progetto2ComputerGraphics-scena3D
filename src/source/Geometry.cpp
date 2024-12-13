#include "Geometry.h"

void crea_cubo(Mesh* mesh, vec4 colore)
{
	std::vector<glm::vec2> texCoords = {
	   {0.0f, 0.0f}, // Bottom-left
	   {1.0f, 0.0f}, // Bottom-right
	   {1.0f, 1.0f}, // Top-right
	   {0.0f, 1.0f}  // Top-left
	};

	mesh->vertices.push_back(vec3(-1.0, -1.0, 1.0));
	mesh->texCoords.push_back(texCoords[0]);
	mesh->colors.push_back(colore);
	mesh->vertices.push_back(vec3(1.0, -1.0, 1.0));
	mesh->texCoords.push_back(texCoords[1]);
	mesh->colors.push_back(colore);
	mesh->vertices.push_back(vec3(1.0, 1.0, 1.0));
	mesh->texCoords.push_back(texCoords[2]);
	mesh->colors.push_back(colore);
	mesh->vertices.push_back(vec3(-1.0, 1.0, 1.0));
	mesh->texCoords.push_back(texCoords[3]);
	mesh->colors.push_back(colore);

	// back
	mesh->vertices.push_back(vec3(-1.0, -1.0, -1.0));
	mesh->texCoords.push_back(texCoords[0]);
	mesh->colors.push_back(colore);
	mesh->vertices.push_back(vec3(1.0, -1.0, -1.0));
	mesh->texCoords.push_back(texCoords[1]);
	mesh->colors.push_back(colore);
	mesh->vertices.push_back(vec3(1.0, 1.0, -1.0));
	mesh->texCoords.push_back(texCoords[2]);
	mesh->colors.push_back(colore);
	mesh->vertices.push_back(vec3(-1.0, 1.0, -1.0));
	mesh->texCoords.push_back(texCoords[3]);
	mesh->colors.push_back(colore);

	// indici
	mesh->indices.push_back(0); mesh->indices.push_back(1); mesh->indices.push_back(2);
	mesh->indices.push_back(2); mesh->indices.push_back(3); mesh->indices.push_back(0);
	mesh->indices.push_back(1); mesh->indices.push_back(5); mesh->indices.push_back(6);
	mesh->indices.push_back(6); mesh->indices.push_back(2); mesh->indices.push_back(1);
	mesh->indices.push_back(7); mesh->indices.push_back(6); mesh->indices.push_back(5);
	mesh->indices.push_back(5); mesh->indices.push_back(4); mesh->indices.push_back(7);
	mesh->indices.push_back(4); mesh->indices.push_back(0); mesh->indices.push_back(3);
	mesh->indices.push_back(3); mesh->indices.push_back(7); mesh->indices.push_back(4);
	mesh->indices.push_back(4); mesh->indices.push_back(5); mesh->indices.push_back(1);
	mesh->indices.push_back(1); mesh->indices.push_back(0); mesh->indices.push_back(4);
	mesh->indices.push_back(3); mesh->indices.push_back(2); mesh->indices.push_back(6);
	mesh->indices.push_back(6); mesh->indices.push_back(7); mesh->indices.push_back(3);

	// normali
	mesh->normals.push_back(normalize(vec3(-1, -1, 1)));
	mesh->normals.push_back(normalize(vec3(1, -1, 1)));
	mesh->normals.push_back(normalize(vec3(1, 1, 1)));
	mesh->normals.push_back(normalize(vec3(-1, 1, 1)));
	mesh->normals.push_back(normalize(vec3(-1, -1, -1)));
	mesh->normals.push_back(normalize(vec3(1, -1, -1)));
	mesh->normals.push_back(normalize(vec3(1, 1, -1)));
	mesh->normals.push_back(normalize(vec3(-1, 1, -1)));

	unsigned int nv = (unsigned int)mesh->vertices.size();
	mesh->indices.push_back(nv - 1);
}

void crea_piramide(Mesh* mesh, vec4 colore)
{
	mesh->vertices.push_back(vec3(-1.0, 0.0, 1.0));
	mesh->colors.push_back(colore);
	mesh->vertices.push_back(vec3(1.0, 0.0, 1.0));
	mesh->colors.push_back(colore);
	mesh->vertices.push_back(vec3(1.0, 0.0, -1.0));
	mesh->colors.push_back(colore);
	mesh->vertices.push_back(vec3(-1.0, 0.0, -1.0));
	mesh->colors.push_back(colore);
	// Apice piramide
	mesh->vertices.push_back(vec3(0.0, 1.0, 0.0));
	mesh->colors.push_back(colore);

	mesh->indices.push_back(0); mesh->indices.push_back(1); mesh->indices.push_back(2);
	mesh->indices.push_back(0); mesh->indices.push_back(2); mesh->indices.push_back(3);

	mesh->indices.push_back(0); mesh->indices.push_back(4); mesh->indices.push_back(3);
	mesh->indices.push_back(0); mesh->indices.push_back(1); mesh->indices.push_back(4);

	mesh->indices.push_back(3); mesh->indices.push_back(2); mesh->indices.push_back(4);
	mesh->indices.push_back(1); mesh->indices.push_back(2); mesh->indices.push_back(4);

	for (int i = 0; i < mesh->vertices.size(); i++)
		mesh->normals.push_back(vec3(0.0));

	unsigned int nv = (unsigned int)mesh->vertices.size();
	mesh->indices.push_back(nv - 1);

}
void crea_piano(Mesh* mesh, vec4 colore)
{
	mesh->vertices.push_back(vec3(-0.5, 0.0, 0.5));
	mesh->colors.push_back(colore);
	mesh->vertices.push_back(vec3(0.5, 0.0, 0.5));
	mesh->colors.push_back(colore);
	mesh->vertices.push_back(vec3(0.5, 0.0, -0.5));
	mesh->colors.push_back(colore);
	mesh->vertices.push_back(vec3(-0.5, 0.0, -0.5));
	mesh->colors.push_back(colore);

	mesh->indices.push_back(0); mesh->indices.push_back(1); mesh->indices.push_back(2);
	mesh->indices.push_back(0); mesh->indices.push_back(2); mesh->indices.push_back(3);

	mesh->texCoords.push_back(vec2(0.0, 1.0));
	mesh->texCoords.push_back(vec2(1.0, 1.0));
	mesh->texCoords.push_back(vec2(1.0, 0.0));
	mesh->texCoords.push_back(vec2(0.0, 0.0));

	mesh->normals.push_back(vec3(0.0, 1.0, 0.0));
	mesh->normals.push_back(vec3(0.0, 1.0, 0.0));
	mesh->normals.push_back(vec3(0.0, 1.0, 0.0));
	mesh->normals.push_back(vec3(0.0, 1.0, 0.0));

	unsigned int nv = (unsigned int)mesh->vertices.size();
	mesh->indices.push_back(nv - 1);
}

void crea_piano_suddiviso(Mesh* mesh, vec4 colore)
{

	int N = 1024;

	int i, j;
	float x, y, s, t;
	for (i = 0; i < N; i++)
	{
		x = (float)i / N;
		for (j = 0; j < N; j++)

		{
			y = (float)j / N;
			mesh->vertices.push_back(vec3(x, 0.0, y));
			mesh->colors.push_back(colore);
			mesh->normals.push_back(vec3(0.0, 1.0, 0.0));
			//Coordinate di texture
			/*
			s = x;
			t = y;
			*/
			s = j;
			t = i;
			mesh->texCoords.push_back(vec2(s, t));

		}
	}
	int cont = -1;

	for (i = 0; i <= pow(N, 2) - (N + 1); i++) {

		j = i % (N);

		if (j != N - 1)
		{
			mesh->indices.push_back(i);
			mesh->indices.push_back(i + 1);
			mesh->indices.push_back(i + N);

			mesh->indices.push_back(i + N + 1);
			mesh->indices.push_back(i + 1);
			mesh->indices.push_back(i + N);
		}
	}
	
	unsigned int nv = (unsigned int)mesh->vertices.size();
	mesh->indices.push_back(nv - 1);
}

void crea_sfera(Mesh* mesh, vec4 colore)
{
	float s, t;
	vec3 centro = vec3(0.0, 0.0, 0.0);
	vec3 raggio = vec3(1.0, 1.0, 1.0);

	int Stacks = 30;  //numero di suddivisioni sull'asse y
	int Slices = 30;  // numero di suddivisioni sull'asse x

	//Calc The Vertices

	//Stacks= suddivisioni lungo l'asse y
	for (int i = 0; i <= Stacks; ++i) {

		float V = i / (float)Stacks;
		float phi = V * pi <float>();

		// Loop Through Slices suddivisioni lungo l'asse x
		for (int j = 0; j <= Slices; ++j) {

			float U = j / (float)Slices;
			float theta = U * (pi <float>() * 2);

			// Calc The Vertex Positions
			float x = centro.x + raggio.x * (cosf(theta) * sinf(phi));
			float y = centro.y + raggio.y * cosf(phi);
			float z = centro.z + raggio.z * sinf(theta) * sinf(phi);

			mesh->vertices.push_back(vec3(x, y, z)),
				mesh->colors.push_back(colore);

			//Normale nel vertice
			mesh->normals.push_back(vec3(x, y, z));
			//coordinata di Texture
			s = U;
			t = V;
			mesh->texCoords.push_back(vec2(s, t));
		}
	}

	// Calc The Index Positions
	for (int i = 0; i < Slices * Stacks + Slices; ++i) {
		mesh->indices.push_back(i);
		mesh->indices.push_back(i + Slices + 1);
		mesh->indices.push_back(i + Slices);

		mesh->indices.push_back(i + Slices + 1);
		mesh->indices.push_back(i);
		mesh->indices.push_back(i + 1);
	}

	unsigned int nv = (unsigned int)mesh->vertices.size();
	mesh->indices.push_back(nv - 1);
}

void crea_toro(Mesh* mesh, vec4 colore)
{
	int Stacks = 30;  //numero di suddivisioni sull'asse x
	int Slices = 30;  // numero di suddivisioni sull'asse y
	float R = 1, r = 0.5;
	float s, t;

	//Calc The Vertices
	for (int i = 0; i <= Stacks; ++i) {

		float V = i / (float)Stacks;
		float phi = V * glm::pi <float>() * 2;

		// Loop Through Slices
		for (int j = 0; j <= Slices; ++j) {

			float U = j / (float)Slices;
			float theta = U * (glm::pi <float>() * 2);

			// Calc The Vertex Positions
			float x = (R + r * cosf(phi)) * cosf(theta);
			float y = r * sinf(phi);
			float z = (R + r * cosf(phi)) * sinf(theta);

			// Push Back Vertex Data
			mesh->vertices.push_back(vec3(x, y, z));
			mesh->colors.push_back(colore);
			//Normale nel vertice
			mesh->normals.push_back(vec3(normalize(vec3(sin(phi) * cos(theta), cos(phi), sin(theta) * sin(phi)))));
			s = U;
			t = V;
			mesh->texCoords.push_back(vec2(s, t));
		}
	}

	// Calc The Index Positions
	for (int i = 0; i < Slices * Stacks + Slices; ++i) {
		mesh->indices.push_back(i);
		mesh->indices.push_back(i + Slices + 1);
		mesh->indices.push_back(i + Slices);

		mesh->indices.push_back(i + Slices + 1);
		mesh->indices.push_back(i);
		mesh->indices.push_back(i + 1);
	}

	unsigned int nv = (unsigned int)mesh->vertices.size();
	mesh->indices.push_back(nv - 1);

}

void crea_cono(Mesh* mesh, vec4 colore)
{
	int Stacks = 30;  //numero di suddivisioni sull'asse x
	int Slices = 30;  // numero di suddivisioni sull'asse y
	float s, t;

	//Calc The Vertices
	for (int i = 0; i <= Stacks; ++i) {

		float V = i / (float)Stacks;
		float h = V;

		// Loop Through Slices
		for (int j = 0; j <= Slices; ++j) {

			float U = j / (float)Slices;
			float theta = U * (glm::pi <float>() * 2);

			// Calc The Vertex Positions
			float x = h * cosf(theta);
			float y = h;
			float z = h * sinf(theta);

			// Push Back Vertex Data
			mesh->vertices.push_back(vec3(x, y, z));
			mesh->colors.push_back(colore);
			//Normale nel vertice
			mesh->normals.push_back(normalize(vec3(cos(theta) / sqrt(2.0f), -1 / sqrt(2.0f), sin(theta) / sqrt(2.0f))));
			//coordinata di texture
			s = U;
			t = V;
			mesh->texCoords.push_back(vec2(s, t));
		}
	}

	// Calc The Index Positions
	for (int i = 0; i < Slices * Stacks + Slices; ++i) {
		mesh->indices.push_back(i);
		mesh->indices.push_back(i + Slices + 1);
		mesh->indices.push_back(i + Slices);

		mesh->indices.push_back(i + Slices + 1);
		mesh->indices.push_back(i);
		mesh->indices.push_back(i + 1);
	}
}

void crea_cilindro(Mesh* mesh, vec4 colore)
{
	int Stacks = 30;  //numero di suddivisioni sull'asse x
	int Slices = 30;  // numero di suddivisioni sull'asse y

	float s, t;
	//Calc The Vertices
	for (int i = 0; i <= Stacks; ++i) {

		float V = i / (float)Stacks;
		float h = V;

		// Loop Through Slices
		for (int j = 0; j <= Slices; ++j) {

			float U = j / (float)Slices;
			float theta = U * (glm::pi <float>() * 2);

			// Calc The Vertex Positions
			float x = cosf(theta);
			float y = h;
			float z = sinf(theta);


			// Push Back Vertex Data
			mesh->vertices.push_back(vec3(x, y, z));
			mesh->colors.push_back(colore);
			mesh->normals.push_back(vec3(normalize(vec3(cos(theta), 0, sin(theta)))));
			//Coordinata di texture
			s = U;
			t = V;
			mesh->texCoords.push_back(vec2(s, t));

		}
	}

	// Calc The Index Positions
	for (int i = 0; i < Slices * Stacks + Slices; ++i) {
		mesh->indices.push_back(i);
		mesh->indices.push_back(i + Slices + 1);
		mesh->indices.push_back(i + Slices);

		mesh->indices.push_back(i + Slices + 1);
		mesh->indices.push_back(i);
		mesh->indices.push_back(i + 1);
	}
}
