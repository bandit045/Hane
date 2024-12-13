#include "Importer.h"

#define WHILE_HAS_TO_READ 1
#define NO_NEXT_LINE EOF

bool Importer::loadOBJ(const char* path, std::vector<glm::vec3>& _vertices, std::vector<glm::vec2>& _textureCordinates, std::vector<glm::vec3>& _normals, std::vector<unsigned int>& _indices, std::vector<glm::vec3>& _importCubeIndexNormal){
	std::vector<unsigned int> vertexIndices;
	std::vector<int> uvIndices;
	std::vector<int> normalIndices;

	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_textureCordinates;
	std::vector<glm::vec3> temp_normals;

	std::vector<glm::vec3> temp_normalsIndex;

	errno_t res;
	FILE* file;;

	res = fopen_s(&file, path, "r");
	if (file == NULL) {
		std::cout << "Imposible to open a OBJ file: " << path << ", check file name, and make sure it has the same!!" << "\n";
		std::cout << "Press key to continiue without it or close window" << "\n";
		std::cin.get();
#ifdef _DEBUG
		throw std::runtime_error("Imposible to open a OBJ file, check file name!");
#endif //_DEBUG
		return false;
	}

	while (WHILE_HAS_TO_READ) {

		char lineHeader[512] = {};
		// read the first word of the line
		int firstWordOfLine = fscanf_s(file, "%s", lineHeader);
		if (firstWordOfLine == NO_NEXT_LINE)
			break; // EOF = End Of File. Quit the loop.

		if (strcmp(lineHeader, "v") == 0) { // Cordinates
			glm::vec3 vertex;
			int check;
			check = fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			if (check != 3)
			{
				std::cout << "Error while reading Vertex Cordinates v(X Y Z)inside OBJ file!" << "\n";
				std::cout << "Numbers of sucesfull in reading cordinates: " << check << "/3" << "\n";
				std::cout << "X: " << vertex.x << " Y: " << vertex.y << " Z: " << vertex.z << "\n";
				
				std::cin.get();
#ifdef _DEBUG
				throw std::runtime_error("Error while reading Vertex Cordinates v(X Y Z)inside OBJ file!");
#endif //_DEBUG
			}
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) { // Texture cordinates
			glm::vec2 uv;
			int check;

			check = fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			if (check != 2)
			{
				std::cout << "Error while reading Texture Cordinates vt(UV) inside OBJ file!" << "\n";
				std::cout << "Numbers of sucesfull in reading texture cordinates: " << check << "/2" << "\n";
				std::cout << "U: " << uv.y << " V: " << uv.x << "\n";

				std::cin.get();
#ifdef _DEBUG
				throw std::runtime_error("Error while reading Texture Cordinates vt(UV) inside OBJ file!");
#endif //_DEBUG
			}
			temp_textureCordinates.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) { // Normals
			glm::vec3 normal;
			int check;
			check = fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			if (check != 3)
			{
				std::cout << "Error while reading Normal Vector VN(X Y Z) inside OBJ file!" << "\n";
				std::cout << "Numbers of sucesfull in reading normal vector: " << check << "/3" << "\n";
				std::cout << "X: " << normal.x << " Y: " << normal.y << " Z: " << normal.z << "\n";

				std::cin.get();
#ifdef _DEBUG
				throw std::runtime_error("Error while reading Normal Vector VN(X Y Z) inside OBJ file!");
#endif //_DEBUG
			}
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				std::cout << ("Error while reading vertexIndex/uvIndex/normalIndex \n");
				std::cout << "Numbers of sucesfull in reading: " << matches << "/9" << "\n";
				std::cout << "Vertex Index: %d/%d/%d" << vertexIndex[0], vertexIndex[1], vertexIndex[2];

				std::cin.get();
#ifdef _DEBUG
				throw std::runtime_error("Error while reading Normal Vector VN(X Y Z) inside OBJ file!");
#endif //_DEBUG
				return false;
			}
			vertexIndices.push_back(vertexIndex[0] - 1);
			vertexIndices.push_back(vertexIndex[1] - 1);
			vertexIndices.push_back(vertexIndex[2] - 1);
			uvIndices.push_back(uvIndex[0] - 1);
			uvIndices.push_back(uvIndex[1] - 1);
			uvIndices.push_back(uvIndex[2] - 1);
			normalIndices.push_back(normalIndex[0] - 1);
			normalIndices.push_back(normalIndex[1] - 1);
			normalIndices.push_back(normalIndex[2] - 1);

			// Map normals using the normal indices
			for (int i = 0; i < 3; i++) {
				unsigned int normalIdx = normalIndex[i] - 1; // OBJ statt at 1 not 0
				_normals.push_back(temp_normals[normalIdx]);
			}
		}
	}  

	_vertices = temp_vertices;
	_normals = temp_normals;
	_textureCordinates = temp_textureCordinates;
	_indices = vertexIndices;
	//_importCubeIndexNormal
	//_uvIndices = uvIndices;

	fclose(file);
}

bool Importer::parseOBJ(
	const std::string& filepath,
	std::vector<glm::vec3>& vertices,
	std::vector<glm::vec2>& uvs,
	std::vector<glm::vec3>& normals,
	std::vector<unsigned int>& indices,
	std::vector<unsigned int>& normalIndices) {

	std::ifstream file(filepath);

	if (!file.is_open()) {
#ifdef _DEBUG
		throw std::runtime_error("Failed to open file: " + filepath);
#else
		std::cerr << "Failed to open file: " << filepath << std::endl;
		return false;
#endif
	}

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream lineStream(line);
		std::string lineHeader;
		lineStream >> lineHeader;

		if (lineHeader == "v") {
			// Vertex position data
			glm::vec3 vertex;
			lineStream >> vertex.x >> vertex.y >> vertex.z;
			vertices.push_back(vertex);
		}
		else if (lineHeader == "vt") {
			// Texture coordinates
			glm::vec2 uv;
			lineStream >> uv.x >> uv.y;
			uvs.push_back(uv);
		}
		else if (lineHeader == "vn") {
			// Normal vectors
			glm::vec3 normal;
			lineStream >> normal.x >> normal.y >> normal.z;
			normals.push_back(normal);
		}
		else if (lineHeader == "f") {
			// Face indices
			std::string vertex1, vertex2, vertex3;
			lineStream >> vertex1 >> vertex2 >> vertex3;

			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

			auto parseFaceElement = [](const std::string& element, unsigned int& v, unsigned int& t, unsigned int& n) {
				std::istringstream elementStream(element);
				std::string vertexStr, uvStr, normalStr;

				std::getline(elementStream, vertexStr, '/');
				v = std::stoi(vertexStr);

				if (std::getline(elementStream, uvStr, '/')) {
					t = uvStr.empty() ? 0 : std::stoi(uvStr);
				}

				if (std::getline(elementStream, normalStr, '/')) {
					n = normalStr.empty() ? 0 : std::stoi(normalStr);
				}
			};

			try {
				parseFaceElement(vertex1, vertexIndex[0], uvIndex[0], normalIndex[0]);
				parseFaceElement(vertex2, vertexIndex[1], uvIndex[1], normalIndex[1]);
				parseFaceElement(vertex3, vertexIndex[2], uvIndex[2], normalIndex[2]);

				indices.push_back(vertexIndex[0] - 1);
				indices.push_back(vertexIndex[1] - 1);
				indices.push_back(vertexIndex[2] - 1);

				//uvIndices.push_back(uvIndex[0] - 1);
				//uvIndices.push_back(uvIndex[1] - 1);
				//uvIndices.push_back(uvIndex[2] - 1);

				normalIndices.push_back(normalIndex[0] - 1);
				normalIndices.push_back(normalIndex[1] - 1);
				normalIndices.push_back(normalIndex[2] - 1);
			}
			catch (const std::exception& e) {
#ifdef _DEBUG
				throw std::runtime_error("Error parsing face data: " + std::string(e.what()));
#else
				std::cerr << "Error parsing face data: " << e.what() << std::endl;
				return false;
#endif
			}
		}
	}

	file.close();
	return true;
}