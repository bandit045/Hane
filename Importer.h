#ifndef IMPORTER_H
#define IMPORTER_H

#include <iostream>
#include <vector>
#include <string>
//#include <glm/glm.hpp>

#include <fstream>
#include <sstream>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class Importer
{
public:
	static bool loadOBJ(const char* path, std::vector<glm::vec3>& vertices, std::vector<glm::vec2>& textureCordinates, std::vector<glm::vec3>& normals, std::vector<unsigned int>& _indices, std::vector<unsigned int>& _importCubeIndexNormal);
};

#endif // !IMPORTER_H
