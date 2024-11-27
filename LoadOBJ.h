#ifndef LOAD_OBJ_H
#define LOAD_OBJ_H

#include <iostream>
#include <vector>
#include <string>
#include <glm/glm.hpp>

class LoadOBJ
{
public:
	static bool loadOBJ(const char* path, std::vector<glm::vec3>& vertices, std::vector<glm::vec2>& textureCordinates, std::vector<glm::vec3>& normals, std::vector<int>& _indices);
};

#endif // !LOAD_OBJ_H
