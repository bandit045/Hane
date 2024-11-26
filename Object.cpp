#include "Object.h"

Object::Object(Shader& shader, Transform& transform) 
{
	m_transform = &transform;
	m_shader = &shader;
}

Object::Object(Shader& shader)
{
	m_transform = new Transform();
	m_shader = &shader;
}