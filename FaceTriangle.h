#ifndef FACE_TRIANGLE_H
#define FACE_TRIANGLE_H

#include <glm\glm.hpp>
#include "Vertex.h"

class Face
{
public:
	Face(const Vertex& _vertexOne, const Vertex& _vertexTwo, const Vertex& _vertexThree);
	// This method serve to flip normal of Face, if its true it flips the normal direction in positive way
	void setNormalDirectionPositive(bool _flipPositive);
	// This method is used to get data and can be send to GPU with vector.data() 
	std::vector<float> getVertexData();
private:
	Vertex m_vertexOne, m_vertexTwo, m_vertexThree;
	glm::vec3 m_faceNormal;

	size_t m_sizeToAllocateToVectorData;
	std::vector<float> vertexData;

	std::vector<float> calculateVectorData();

	// Check if works
	glm::vec3 calculateFaceNormal(bool _flipPositive);
};

#endif // !FACE_TRIANGLE_H