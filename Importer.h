#ifndef IMPORTER_H
#define IMPORTER_H

#include <iostream>
#include <vector>
#include <string>
#include <glm/glm.hpp>

class Importer
{
public:
	static bool loadOBJ(const char* path, std::vector<glm::vec3>& vertices, std::vector<glm::vec2>& textureCordinates, std::vector<glm::vec3>& normals, std::vector<unsigned int>& _indices);
};

#endif // !IMPORTER_H
