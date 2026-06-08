#include "Object.h"

int Object::name_counter = 0;

Object::Object(std::string _nameOfObject, Transform& _transform)
{
	m_objectName = _nameOfObject;

	m_transform = &_transform;
}
Object::Object(std::string _nameOfObject)
{
	m_objectName = _nameOfObject;

	m_transform = new Transform();
}
Object::Object()
{
	m_objectName = setDefaultObjectName();

	m_transform = new Transform();
}
void Object::setObjectName(std::string _newName)
{
	m_objectName = _newName;
}
std::string Object::setDefaultObjectName() // This method serve as gurd if we dons specify name of object in constructor
{
	name_counter++;
	return "Object_" + std::to_string(name_counter) + ")";
}
std::string Object::getObjectName() const
{
	return m_objectName;
}