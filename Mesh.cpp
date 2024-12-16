#include "Mesh.h"

Mesh::Mesh()
{
	Mesh::m_numberOfTriangle = 0;
}

void Mesh::setEBOindices(const std::vector<EBO::OrderOfRendering>& _orderOfRenderingTriangles)
{
	
}

void Mesh::addTriangleToMesh(Face& _faceTriangleToAdd)
{
	Mesh::m_triangles.push_back(_faceTriangleToAdd);
	Mesh::m_numberOfTriangle++;
}

int Mesh::getNumberOfTriangle()
{
	return m_numberOfTriangle;
}

Face& Mesh::getTriangle(int _indexOfTriangleInsideMesh)
{
	return Mesh::m_triangles[_indexOfTriangleInsideMesh];
}

int Mesh::getNumberOfVertices()
{
	return Mesh::m_numberOfTriangle * Face::s_numberOfVerticesInFace;
}

std::vector<float> Mesh::getMeshData()
{
	return Mesh::m_meshData;
}

void Mesh::calculateMeshData()
{
	for (auto i : Mesh::m_triangles)
	{
		for (auto j : i.getFaceData())
		{
			m_meshData.push_back(j);
		}
	}
}

// For debug
void Mesh::printMeshData()
{
	for (float value : Mesh::m_meshData) {
		std::cout << value << " \n";
	}
}