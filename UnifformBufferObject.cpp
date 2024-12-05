#include "UnifformBufferObject.h"

void UnifformBufferObject::sendBoolsUniformToShader(const char* nameOfUniformStructInShader, const std::vector<int>& vectorToSendToGPU, const GLuint& shaderProgramID)
{
    unsigned int uniformBlockIndexRed = glGetUniformBlockIndex(shaderProgramID, nameOfUniformStructInShader);
    glUniformBlockBinding(shaderProgramID, uniformBlockIndexRed, 0);

    // Generate buffer
    GLuint renderFlagsUniformObject;
    glGenBuffers(1, &renderFlagsUniformObject);
    glBindBuffer(GL_UNIFORM_BUFFER, renderFlagsUniformObject);

    // Allocate memory for the uniform buffer
    glBufferData(GL_UNIFORM_BUFFER, vectorToSendToGPU.size() * sizeof(int), nullptr, GL_DYNAMIC_DRAW);

    // Bind buffer range (to match the shader uniform block)
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, renderFlagsUniformObject, 0, vectorToSendToGPU.size() * sizeof(int));

    // Upload the data to the buffer
    glBufferSubData(GL_UNIFORM_BUFFER, 0, vectorToSendToGPU.size() * sizeof(int), vectorToSendToGPU.data());

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

std::vector<int> UnifformBufferObject::prepareVectorToSendFromUnordered_Map(const std::unordered_map<std::string, bool>& _mapToChange, const std::vector<std::string>& _insertOrder)
{
    std::vector<int> vecToSend;
    vecToSend.reserve(_insertOrder.size());

    for (int i = 0; i < _insertOrder.size(); ++i)
    {
        const std::string& s = _insertOrder[i];
        vecToSend.push_back(_mapToChange.at(s));
    }
    return vecToSend;
}

std::vector<int> UnifformBufferObject::prepareFlags(RenderFlags _renderFlags)
{
    std::vector<int> vecToSend;
    vecToSend.reserve(_renderFlags.getAllValue().insertOrder.size());

    for (int i = 0; i < _renderFlags.getAllValue().insertOrder.size(); ++i)
    {
        const std::string& s = _renderFlags.getAllValue().insertOrder[i];
        vecToSend.push_back(_renderFlags.getAllValue().flags.at(s));
    }
    return vecToSend;
}
