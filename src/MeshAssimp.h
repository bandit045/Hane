#ifndef MESH_ASSIMP_H 
#define MESH_ASSIMP_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include "Shader.h"

namespace Hane
{
	struct VertexAssimp {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};
	struct TextureAssimp {
		unsigned int id;
		const char* type;
	};
	class MeshAssimp
	{
	public:
		// mesh data
		std::vector<Hane::VertexAssimp>       m_verticesAssimp;
		std::vector<unsigned int>			  m_indicesAssimp;
		std::vector<Hane::TextureAssimp>      m_texturesAssimp;

		void Draw(Shader& _shaderAssimp);

		MeshAssimp(std::vector<Hane::VertexAssimp> _verticesAssimp, std::vector<unsigned int> _indicesAssimp, std::vector<Hane::TextureAssimp> _texturesAssimp);

	private:
		//  render data
		unsigned int m_vertexArrayObjectAssimp, m_vertexBufferObjectAssimp, m_elementBufferObjectAssimp;
		void setupAssimpMesh();
	};
}
#endif // !MESH_ASSIMP_H 