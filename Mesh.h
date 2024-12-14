#ifndef MESH_H
#define MESH_H

#include "Vertex.h"
#include <vector>

class Mesh
{
public:
	Mesh(int _numberOfVertices);

	void addVertexToMesh(Vertex _vertex);
	int getNumberOfVerticesAllocated();
	int getNumberOfAddedVertices();
	std::vector<float> getMeshDataInVector();
private:
	int m_numberOfVerticesAllocated;
	int m_numberOfVerticesAdded;
	std::vector<Vertex> m_vertices;
};
#endif // !MESH_H