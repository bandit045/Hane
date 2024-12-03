#include "UnifformBufferObject.h"

void UnifformBufferObject::sendBoolsUniformToShader(const char* nameOfUniformStructInShader, const std::vector<int>& vectorBoolData, const GLuint& shaderProgramID)
{
    unsigned int uniformBlockIndexRed = glGetUniformBlockIndex(shaderProgramID, nameOfUniformStructInShader);
    glUniformBlockBinding(shaderProgramID, uniformBlockIndexRed, 0);

    // Generate buffer
    GLuint renderFlagsUniformObject;
    glGenBuffers(1, &renderFlagsUniformObject);
    glBindBuffer(GL_UNIFORM_BUFFER, renderFlagsUniformObject);

    // Allocate memory for the uniform buffer
    glBufferData(GL_UNIFORM_BUFFER, vectorBoolData.size() * sizeof(int), nullptr, GL_DYNAMIC_DRAW);

    // Bind buffer range (to match the shader uniform block)
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, renderFlagsUniformObject, 0, vectorBoolData.size() * sizeof(int));

    // Upload the data to the buffer
    glBufferSubData(GL_UNIFORM_BUFFER, 0, vectorBoolData.size() * sizeof(int), vectorBoolData.data());

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

std::vector<int> UnifformBufferObject::prepareVectorToSendFromUnordered_Map(const std::unordered_map<std::string, bool>& _mapToChange, const std::vector<std::string>& _insertOrder)
{
    std::vector<int> vecToSend;
    vecToSend.reserve(_insertOrder.size());

    /*vecToSend[0] = _mapToChange.at("isPointLightReducingOnDistance");
    vecToSend[1] = _mapToChange.at("isPhong");
    vecToSend[2] = _mapToChange.at("isBlinnPhong");
    vecToSend[3] = _mapToChange.at("isSpecularMap");
    vecToSend[4] = _mapToChange.at("isDirectionalLight");
    vecToSend[5] = _mapToChange.at("isPointLight");
    vecToSend[6] = _mapToChange.at("isAutomaticLuminosity");
    vecToSend[7] = _mapToChange.at("isManuelLuminosity");*/

    for (int i = 0; i < _insertOrder.size(); ++i)
    {
        const std::string& s = _insertOrder[i];
        vecToSend.push_back(_mapToChange.at(s));
    }
    return vecToSend;
}
