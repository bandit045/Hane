#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>

class Vertex
{
private:
	glm::vec3 m_cordinate;
	glm::vec3 m_normal;
	glm::vec2 m_uvcord;
	glm::vec4 m_color;

	bool m_isVertexDefaultValue;

	bool m_isVertexDefaultValue_cordinate;
	bool m_isVertexDefaultValue_normal;
	bool m_isVertexDefaultValue_uvcord;
	bool m_isVertexDefaultValue_color;
public:
	Vertex();

	// This value is m_cordinate + m_normal + m_uvcord + m_color which is 3+3+2+4 = 12
	static const int m_numberOfAllSingleValueInVertex = 12;

	// This method return true if the vertex has all default value, which is bad :(
	bool getIfVertHasAllDefaultValue();

	const glm::vec3& getCordinate() const;
	glm::vec3& setCordinate();

    const glm::vec3& getNormal() const;
	glm::vec3& setNormal();

    const glm::vec2& getUVCord() const;
	glm::vec2& setUVCord();

    const glm::vec4& getColor() const;
	glm::vec4& setColor();

	// This method is used to get data and can be send to GPU with vector.data() 
	std::vector<float> getVertexData();
};
#endif // !VERTEX_H