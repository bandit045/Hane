#ifndef MESH_H
#define MESH_H

#include "EBO.h"
#include "Face.h"
#include <glm/glm.hpp>
#include <vector>

class Mesh// Cucurently mesh accept only triangles 
{
public:
	Mesh();

	// Used for debuging purpose
	void printMeshData();

	// Returns number of triangles in mesh
	int getNumberOfTriangle();
	// Returns number of vertices in mesh
	int getNumberOfVertices();
	// Add triangle to mesh
	void addTriangleToMesh(Face& _faceTriangleToAdd);
	// Calculate data in continious memory
	void calculateMeshData();
	void setEBOindices(const std::vector<EBO::OrderOfRendering>& _orderOfRenderingTriangles); // Not used cucurently
	// Used to send mesh data to GPU with vector.data()
	std::vector<float> getMeshData();
	Face& getTriangle(int _indexOfTriangleInsideMesh); // Trying to implement this function
private:
	// This member variable store all triangles inside Mesh
	std::vector<Face> m_triangles;
	// Used to store mesh data in continious memory
	std::vector<float> m_meshData;

	// How much triangles we have in mesh
	int m_numberOfTriangle;
	std::vector<EBO::OrderOfRendering> m_orderOfRenderingTriangles; // Trying to implement
};
#endif // !MESH_H