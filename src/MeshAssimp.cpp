#include "MeshAssimp.h"

Hane::MeshAssimp::MeshAssimp(std::vector<Hane::VertexAssimp> _verticesAssimp, std::vector<unsigned int> _indicesAssimp, std::vector<Hane::TextureAssimp> _texturesAssimp)
{
    this->m_verticesAssimp = _verticesAssimp;
    this->m_indicesAssimp = _indicesAssimp;
    this->m_texturesAssimp = _texturesAssimp;

    Hane::MeshAssimp::setupAssimpMesh();
}

void Hane::MeshAssimp::setupAssimpMesh()
{
    glGenVertexArrays(1, &m_vertexArrayObjectAssimp);
    glGenBuffers(1, &m_vertexBufferObjectAssimp);
    glGenBuffers(1, &m_elementBufferObjectAssimp);

    glBindVertexArray(m_vertexArrayObjectAssimp);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjectAssimp);

    glBufferData(GL_ARRAY_BUFFER, m_verticesAssimp.size() * sizeof(VertexAssimp), &m_verticesAssimp[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferObjectAssimp);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesAssimp.size() * sizeof(unsigned int), &m_indicesAssimp[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAssimp), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAssimp), (void*)offsetof(VertexAssimp, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexAssimp), (void*)offsetof(VertexAssimp, TexCoords));

    glBindVertexArray(0);
}