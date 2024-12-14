#include "FaceTriangle.h"

Face::Face(const Vertex& _vertexOne, const Vertex& _vertexTwo, const Vertex& _vertexThree)
{
    m_vertexOne = _vertexOne;
    m_vertexTwo = _vertexTwo;
    m_vertexThree = _vertexThree;

    m_sizeToAllocateToVectorData = Vertex::m_numberOfAllSingleValueInVertex * 3;

    m_faceNormal = calculateFaceNormal(true);
    vertexData = calculateVectorData();
}

std::vector<float> Face::calculateVectorData()
{
    std::vector<float> returnData;
    returnData.reserve(m_sizeToAllocateToVectorData);
//--------------Vertex One-----------------------------------
    returnData.push_back(m_vertexOne.getCordinate().x);
    returnData.push_back(m_vertexOne.getCordinate().y);
    returnData.push_back(m_vertexOne.getCordinate().z);

    returnData.push_back(m_faceNormal.x); // This normals are automatic calculated
    returnData.push_back(m_faceNormal.y);
    returnData.push_back(m_faceNormal.z);

    returnData.push_back(m_vertexOne.getUVCord().x);
    returnData.push_back(m_vertexOne.getUVCord().y);

    returnData.push_back(m_vertexOne.getColor().r);
    returnData.push_back(m_vertexOne.getColor().g);
    returnData.push_back(m_vertexOne.getColor().b);
    returnData.push_back(m_vertexOne.getColor().a);
//--------------Vertex Two-----------------------------------
    returnData.push_back(m_vertexTwo.getCordinate().x);
    returnData.push_back(m_vertexTwo.getCordinate().y);
    returnData.push_back(m_vertexTwo.getCordinate().z);

    returnData.push_back(m_faceNormal.x); // This normals are automatic calculated
    returnData.push_back(m_faceNormal.y);
    returnData.push_back(m_faceNormal.z);

    returnData.push_back(m_vertexTwo.getUVCord().x);
    returnData.push_back(m_vertexTwo.getUVCord().y);

    returnData.push_back(m_vertexTwo.getColor().r);
    returnData.push_back(m_vertexTwo.getColor().g);
    returnData.push_back(m_vertexTwo.getColor().b);
    returnData.push_back(m_vertexTwo.getColor().a);
//--------------Vertex Three-----------------------------------
    returnData.push_back(m_vertexThree.getCordinate().x);
    returnData.push_back(m_vertexThree.getCordinate().y);
    returnData.push_back(m_vertexThree.getCordinate().z);

    returnData.push_back(m_faceNormal.x); // This normals are automatic calculated
    returnData.push_back(m_faceNormal.y);
    returnData.push_back(m_faceNormal.z);

    returnData.push_back(m_vertexThree.getUVCord().x);
    returnData.push_back(m_vertexThree.getUVCord().y);

    returnData.push_back(m_vertexThree.getColor().r);
    returnData.push_back(m_vertexThree.getColor().g);
    returnData.push_back(m_vertexThree.getColor().b);
    returnData.push_back(m_vertexThree.getColor().a);
    return returnData;
}

//Check if Works!!!!!!!!!!
glm::vec3 Face::calculateFaceNormal(bool _flipPositive)
{
    glm::vec3 edge1 = glm::vec3((m_vertexTwo.getCordinate().x - m_vertexOne.getCordinate().x),
                                (m_vertexTwo.getCordinate().y - m_vertexOne.getCordinate().y),
                                (m_vertexTwo.getCordinate().z - m_vertexOne.getCordinate().z));
    glm::vec3 edge2 = glm::vec3((m_vertexThree.getCordinate().x - m_vertexOne.getCordinate().x),
                                (m_vertexThree.getCordinate().y - m_vertexOne.getCordinate().y),
                                (m_vertexThree.getCordinate().z - m_vertexOne.getCordinate().z));
    if (_flipPositive)
    {
        return glm::normalize(glm::cross(edge2, edge1));
    }
    else
    {
        return glm::normalize(glm::cross(edge1, edge2));
    }
}

// If its true it flips the normal direction in positive way
void Face::setNormalDirectionPositive(bool _flipPositive)
{
    m_faceNormal = calculateFaceNormal(_flipPositive);
    vertexData = calculateVectorData();
}

std::vector<float> Face::getVertexData()
{
    return vertexData;
}
