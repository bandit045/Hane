#ifndef UNIFFORM_BUFFER_OBJECT_H
#define UNIFFORM_BUFFER_OBJECT_H

#include <glad/glad.h>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <vector>
#include "RenderFlags.h"

class UnifformBufferObject
{
public:
	// This method send continous data std::vector<int> to shader 
	void static sendBoolsUniformToShader(const char* nameOfUniformStructInShader, const std::vector<int>& vectorToSendToGPU, const GLuint& shaderProgramID);
	// This method prepare to sent data from std::unordered_map (bool) to shader but transform it in vector(int) in order to send to "sendBoolsUniformToShader()" method
	std::vector<int> static prepareVectorToSendFromUnordered_Map(const std::unordered_map<std::string, bool>& vectorToChange, const std::vector<std::string>& _insertOrder);
	// This method serve as method to organize data in which order need to be to send to GPU from std::unordered_map, in help of vector that monitor order in which we add them same as "prepareVectorToSendFromUnordered_Map()"
	std::vector<int> static prepareFlags(RenderFlags _renderFlags);
private:
};
#endif // !UNIFFORM_BUFFER_OBJECT_H