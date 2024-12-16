#ifndef FACE_TRIANGLE_H
#define FACE_TRIANGLE_H

#include <glm\glm.hpp>
#include <array>
#include "Vertex.h"

class Face
{
public:
	Face(Vertex& _vertexOne, Vertex& _vertexTwo, Vertex& _vertexThree);
	~Face();

	const static int s_numberOfVerticesInFace = 3;
	// This method serve to flip normal of Face, if its true it flips the normal direction in positive way
	void calculateAutomaticNormal(bool _flipInPositiveDirection);
	// This method is used to get data and can be send to GPU with vector.data() 
	std::array<float, 36> getFaceData();
	// Used to get index of vertex inside triangle can be 1 2 3
	Vertex& getVertex(int _indexOfVertex);
	std::array<float, 36> calculateFaceData();
private:
	std::array<Vertex, 3> m_vertices;

	glm::vec3 m_faceNormal;

	std::array<float, 36> m_triangleData;
	void setNormalDirectionPositive(bool _flipPositive);

	// Check if works
	glm::vec3 calculateFaceNormal(bool _automaticCalculateNormal);
};

#endif // !FACE_TRIANGLE_H