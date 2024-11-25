#ifndef OBJECT_H
#define OBJECT_H

#include "Transform.h"
#include "Shader.h"

class Object{
public:
	Object(Shader& shader, Transform& transform);

	Transform* m_transform;
	Shader* m_shader;
};
#endif // !OBJECT_H