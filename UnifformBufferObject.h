#ifndef UNIFFORM_BUFFER_OBJECT_H
#define UNIFFORM_BUFFER_OBJECT_H

#include <glad/glad.h>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <vector>

class UnifformBufferObject
{
public:
	void static sendBoolsUniformToShader(const char* nameOfUniformStructInShader, const std::vector<int>& vectorBoolData, const GLuint& shaderProgramID);
	std::vector<int> static prepareVectorToSendFromUnordered_Map(const std::unordered_map<std::string, bool>& vectorToChange, const std::vector<std::string>& _insertOrder);
private:
};
#endif // !UNIFFORM_BUFFER_OBJECT_H