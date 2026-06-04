#ifndef LITERAL_VERTEX_H
#define LITERAL_VERTEX_H

#include <iostream>
#include <array>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>

namespace Hane 
{
	// This vertex class is used like single vertex in much bigger structure like mesh
	// It can be in FaceTriangle, Mesh(Defined mesh by specifying all vertex on by one), Mesh(defined by faceTriangle)
	class LiteralVertex
	{
	private:
		mutable glm::vec3 m_cordinate;
		mutable glm::vec3 m_normal;
		mutable glm::vec2 m_uvcord;
		mutable glm::vec4 m_color;

		bool m_isVertexDefaultValue;

		bool m_isVertexDefaultValue_cordinate;
		bool m_isVertexDefaultValue_normal;
		bool m_isVertexDefaultValue_uvcord;
		bool m_isVertexDefaultValue_color;

		// Debug purpose
		static int s_invokedConstructor;
		static int s_invokedCopyConstructor;
		static int s_invokedMoveConstructor;
		static int s_invokedDestructor;
		static int s_invokedCopyAssignmentOperator;
		static int s_invokedMoveAssignmentOperator;
	public:
		LiteralVertex();

		// This value is m_cordinate + m_normal + m_uvcord + m_color which is 3+3+2+4 = 12
		static const int s_offsetOfBufferLayout = 12;

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

		// This method is used to get data and can be send to GPU with array.data() 
		std::array<float, 12> getVertexData();
	};
}
#endif // !LITERAL_VERTEX_H