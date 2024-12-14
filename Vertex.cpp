#include "Vertex.h"

Vertex::Vertex()
{
	m_cordinate = glm::vec3(1.0f, 1.0f, 1.0f);
	m_normal =    glm::vec3(1.0f, 1.0f, 1.0f);
	m_uvcord =    glm::vec2(1.0f, 1.0f);
	m_color =     glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	m_isVertexDefaultValue = true;

	m_isVertexDefaultValue_cordinate = true;
	m_isVertexDefaultValue_normal = true;
	m_isVertexDefaultValue_uvcord = true;
	m_isVertexDefaultValue_color = true;
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
std::vector<float> Vertex::getVertexData()
{
	std::vector<float> toReturn;
	toReturn.reserve(12);
	toReturn.push_back(m_cordinate.x);
    toReturn.push_back(m_cordinate.y);
    toReturn.push_back(m_cordinate.z);
    toReturn.push_back(m_normal.x);
    toReturn.push_back(m_normal.y);
    toReturn.push_back(m_normal.z);
    toReturn.push_back(m_uvcord.x);
    toReturn.push_back(m_uvcord.y);
    toReturn.push_back(m_color.r);
    toReturn.push_back(m_color.g);
    toReturn.push_back(m_color.b);
    toReturn.push_back(m_color.w);
	return toReturn;
	/*	std::vector<float> ddad;
	ddad = top_left.getVertexData();
	for (int i = 0; i < 12; i++)
	{
		std::cout << ddad[i] << "\n";
	}*/
}