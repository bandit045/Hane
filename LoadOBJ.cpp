#include "LoadOBJ.h"

#define WHILE_HAS_TO_READ 1
#define NO_NEXT_LINE EOF

bool LoadOBJ::loadOBJ(const char* path, std::vector<glm::vec3>& _vertices, std::vector<glm::vec2>& _textureCordinates, std::vector<glm::vec3>& _normals, std::vector<int>& _indices)
{
	std::vector<int> vertexIndices;
	std::vector<int> uvIndices;
	std::vector<int> normalIndices;

	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_textureCordinates;
	std::vector<glm::vec3> temp_normals;

	FILE* file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}

	while (WHILE_HAS_TO_READ) {

		char lineHeader[128] = {0};
		// read the first word of the line
		int firstWordOfLine = fscanf(file, "%s", lineHeader);
		if (firstWordOfLine == NO_NEXT_LINE)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		if (strcmp(lineHeader, "v") == 0) { // Cordinates
			glm::vec3 vertex;
			int check;
			check = fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			if (check != 3)
			{
				std::cout << "Error while reading Vertex Cordinates inside OBJ file!" << "\n";
			}
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) { // Texture cordinates
			glm::vec2 uv;
			int check;
			check = fscanf(file, "%f %f\n", &uv.x, &uv.y);
			if (check != 2)
			{
				std::cout << "Error while reading Texture Cordinates inside OBJ file!" << "\n";
			}
			temp_textureCordinates.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) { // Normals
			glm::vec3 normal;
			int check;
			check = fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			if (check != 3)
			{
				std::cout << "Error while reading Normals inside OBJ file!" << "\n";
			}
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0] - 1);
			vertexIndices.push_back(vertexIndex[1] - 1);
			vertexIndices.push_back(vertexIndex[2] - 1);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	_vertices = temp_vertices;
	_normals = temp_normals;
	_textureCordinates = temp_textureCordinates;
	_indices = vertexIndices;

	/*// For each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++) 
	{
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		_vertices.push_back(vertex);
	}

	// For each Texture Cordinates of each triangle !!!!!!!!!!!!
	for (unsigned int i = 0; i < uvIndices.size(); i++)
	{
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 textureCordinates = temp_textureCordinates[uvIndex - 1];
		_textureCordinates.push_back(textureCordinates);
	}

	// For each Normal of each face
	for (unsigned int i = 0; i < normalIndices.size(); i++)
	{
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normals = temp_normals[normalIndex - 1];
		_normals.push_back(normals);
	}*/

	fclose(file);
}