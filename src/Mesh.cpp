#include "Mesh/Mesh.h"

namespace Hane
{
	Mesh::Mesh()
	{
		Mesh::m_numberOfTriangle = 0;
		std::cout << "Mesh constructor invoked! \n";
	}

	Mesh::~Mesh()
	{
		std::cout << "Mesh destructor invoked! \n";
	}

	void Mesh::setEBOindices(const std::vector<EBO::OrderOfRendering>& _orderOfRenderingTriangles)
	{

	}

	void Mesh::addTriangleToMesh(Hane::Face& _faceTriangleToAdd)
	{
		Mesh::m_triangles.push_back(_faceTriangleToAdd);
		Mesh::m_numberOfTriangle++;
	}

	int Mesh::getNumberOfTriangle()
	{
		return m_numberOfTriangle;
	}

	Hane::Face& Mesh::getTriangle(int _indexOfTriangleInsideMesh)
	{
		return Mesh::m_triangles[_indexOfTriangleInsideMesh];
	}

	int Mesh::getNumberOfVertices()
	{
		return Mesh::m_numberOfTriangle * Hane::Face::s_numberOfVerticesInFace;
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
}