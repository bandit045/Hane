#include "Mesh.h"

Mesh::Mesh(int _numberOfVerticesToAllocate) : m_numberOfVerticesAllocated(_numberOfVerticesToAllocate)
{
	m_vertices.reserve(_numberOfVerticesToAllocate);
	m_numberOfVerticesAdded = 0;
}

void Mesh::addVertexToMesh(Vertex _vertex)
{
	m_vertices.emplace_back(_vertex);
	m_numberOfVerticesAdded++;
}

int Mesh::getNumberOfVerticesAllocated()
{
	return m_numberOfVerticesAllocated;
}

int Mesh::getNumberOfAddedVertices()
{
	return m_numberOfVerticesAdded;
}

std::vector<float> Mesh::getMeshDataInVector()
{
	std::vector<float> meshDataToReturn;
	size_t meshDataSize = static_cast<size_t>(m_numberOfVerticesAdded) * Vertex::m_numberOfAllSingleValueInVertex;
	meshDataToReturn.reserve(meshDataSize);

	for (int i = 0; i < m_numberOfVerticesAdded; i++)
	{
		meshDataToReturn.push_back(m_vertices[i].getCordinate().x);
		meshDataToReturn.push_back(m_vertices[i].getCordinate().y);
		meshDataToReturn.push_back(m_vertices[i].getCordinate().z);

		meshDataToReturn.push_back(m_vertices[i].getNormal().x);
		meshDataToReturn.push_back(m_vertices[i].getNormal().y);
		meshDataToReturn.push_back(m_vertices[i].getNormal().z);

		meshDataToReturn.push_back(m_vertices[i].getUVCord().x);
		meshDataToReturn.push_back(m_vertices[i].getUVCord().y);

		meshDataToReturn.push_back(m_vertices[i].getColor().r);
		meshDataToReturn.push_back(m_vertices[i].getColor().g);
		meshDataToReturn.push_back(m_vertices[i].getColor().b);
		meshDataToReturn.push_back(m_vertices[i].getColor().a);
	}
	return meshDataToReturn;
}