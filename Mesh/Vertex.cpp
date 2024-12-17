#include "Vertex.h"

Vertex::Vertex()
{
	m_cordinate = glm::vec3(1.0f, 1.0f, 1.0f);
	m_normal =    glm::vec3(0.0f, 0.0f, 0.0f);
	m_uvcord =    glm::vec2(1.0f, 1.0f);
	m_color =     glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	m_isVertexDefaultValue = true;

	m_isVertexDefaultValue_cordinate = true;
	m_isVertexDefaultValue_normal = true;
	m_isVertexDefaultValue_uvcord = true;
	m_isVertexDefaultValue_color = true;
}

Vertex::~Vertex()
{
	
}

// This method return true if the vertex has all default value, which is bad :(
bool Vertex::getIfVertHasAllDefaultValue()
{
	if (m_isVertexDefaultValue_cordinate || m_isVertexDefaultValue_normal || m_isVertexDefaultValue_uvcord || m_isVertexDefaultValue_color)
	{
		std::cout << "Vertex have default values for not all components" << "\n";
		return true;
	}
	else
	{
		std::cout << "Vertex doe`s have all changed values" << "\n";
		return false;
	}
}

const glm::vec3& Vertex::getCordinate() const
{
	return m_cordinate;
}

glm::vec3& Vertex::setCordinate()
{
	m_isVertexDefaultValue_cordinate = false;
	return m_cordinate;
}

const glm::vec3& Vertex::getNormal() const
{
	return m_normal;
}

glm::vec3& Vertex::setNormal()
{
	m_isVertexDefaultValue_normal = false;
	return m_normal;
}

const glm::vec2& Vertex::getUVCord() const
{
	return m_uvcord;
}

glm::vec2& Vertex::setUVCord()
{
	m_isVertexDefaultValue_uvcord = false;
	return m_uvcord;
}

const glm::vec4& Vertex::getColor() const
{
	return m_color;
}

glm::vec4& Vertex::setColor()
{
	m_isVertexDefaultValue_color = false;
	return m_color;
}

// This method is used to get data and can be send to GPU with vector.data() 
std::array<float, 12> Vertex::getVertexData()
{
	std::array<float, 12> toReturn;
	toReturn[0] = m_cordinate.x;
    toReturn[1] = m_cordinate.y;
    toReturn[2] = m_cordinate.z;
    toReturn[3] = m_normal.x;
    toReturn[4] = m_normal.y;
    toReturn[5] = m_normal.z;
    toReturn[6] = m_uvcord.x;
    toReturn[7] = m_uvcord.y;
    toReturn[8] = m_color.r;
    toReturn[9] = m_color.g;
    toReturn[10] = m_color.b;
    toReturn[11] = m_color.w;
	return toReturn;
}