#include "Face.h"

Face::Face(Vertex& _vertexOne, Vertex& _vertexTwo, Vertex& _vertexThree)
{
    m_vertices[0] = _vertexOne;
    m_vertices[1] = _vertexTwo;
    m_vertices[2] = _vertexThree;

    m_faceNormal = glm::vec3(0.0f, 0.0f, 0.0f); // No normal
    m_triangleData = {0}; // No data which means we need manuely to calculate it with calculateFaceData() but before that if we dont have normals invoke calculateAutomaticNormal(bool _flipInPositiveDirection)
}

Face::~Face()
{

}

void Face::calculateAutomaticNormal(bool _flipInPositiveDirection)
{
    m_faceNormal = Face::calculateFaceNormal(_flipInPositiveDirection);
}

Vertex& Face::getVertex(int _indexOfVertex) // Trying to implement
{
    return m_vertices[_indexOfVertex];
}

std::array<float, 36> Face::calculateFaceData()
{
    // Getting all trhee vertex elements in std::array and push them to vector
    for (uint16_t i = 0; i < 3; i++)
    {
        uint16_t offset = i * 12; // Each vertex has 12 attributess

        // Position
        m_triangleData[offset + 0] = m_vertices[i].getCordinate().x;
        m_triangleData[offset + 1] = m_vertices[i].getCordinate().y;
        m_triangleData[offset + 2] = m_vertices[i].getCordinate().z;

        // Normal 
        m_triangleData[offset + 3] = m_faceNormal.x; // Calculating automaticly with calculateAutomaticNormal(bool _flipInPositiveDirection)
        m_triangleData[offset + 4] = m_faceNormal.y;
        m_triangleData[offset + 5] = m_faceNormal.z;

        // UV Coordinates
        m_triangleData[offset + 6] = m_vertices[i].getUVCord().x;
        m_triangleData[offset + 7] = m_vertices[i].getUVCord().y;

        // Color
        m_triangleData[offset + 8] = m_vertices[i].getColor().r;
        m_triangleData[offset + 9] = m_vertices[i].getColor().g;
        m_triangleData[offset + 10] = m_vertices[i].getColor().b;
        m_triangleData[offset + 11] = m_vertices[i].getColor().a;
    }
    return m_triangleData;
}

glm::vec3 Face::calculateFaceNormal(bool _flipPositive)
{
    glm::vec3 edge1 = glm::vec3((m_vertices[1].getCordinate().x - m_vertices[0].getCordinate().x),
        (m_vertices[1].getCordinate().y - m_vertices[0].getCordinate().y),
        (m_vertices[1].getCordinate().z - m_vertices[0].getCordinate().z));
    glm::vec3 edge2 = glm::vec3((m_vertices[2].getCordinate().x - m_vertices[0].getCordinate().x),
        (m_vertices[2].getCordinate().y - m_vertices[0].getCordinate().y),
        (m_vertices[2].getCordinate().z - m_vertices[0].getCordinate().z));
    if (_flipPositive)
    {
        return glm::normalize(glm::cross(edge2, edge1));
    }
    else
    {
        return glm::normalize(glm::cross(edge1, edge2));
    }
}

std::array<float, 36> Face::getFaceData()
{
    return m_triangleData;
}