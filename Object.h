#ifndef OBJECT_H
#define OBJECT_H

#include "Transform.h"
#include "Shader.h"

class Object{
public:
	Object(std::string nameOfObject, Transform& transform);
	Object(std::string nameOfObject);
	Object();

	// Setters
	void setObjectName(std::string newName);

	// Getters
	std::string getObjectName(bool newLineChar);

	// Components
	Transform* m_transform;
	Shader* m_shader;
private:
	// Member variables
	std::string m_objectName;

	static int name_counter;

	// Private member function
	static std::string setDefaultObjectName();
};
#endif // !OBJECT_H