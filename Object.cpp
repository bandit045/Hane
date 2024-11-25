#include "Object.h"

Object::Object(Shader& shader, Transform& transform) 
{
	m_transform = &transform;
	m_shaderID = &shader;
}