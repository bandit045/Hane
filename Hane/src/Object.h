#ifndef OBJECT_H
#define OBJECT_H

#include "Transform.h" // Ima svoj transform mesto na koje se nalazi, kao ako ima scale, ili rotaciju 
#include "Shader.h" // Shader je nekoliko levela niza stvar od objekta, jel sam objekat moze imati vise materijala na sebi a vise materijala zahtevaju vise shadera??????? ili napraviti "Simple Object" koji na sebi ima samo jedan Material time je i potrebno samo jedan Shader?
//include "Material.h" ??? dali je Material stvar koja se kontrolise pomocu modela ili objekta 
//include "Model.h" ??? model se sastoji od Matriala i Mesha? Materijal se sastoji od vise textura i shadera? 

class Object{
public:
	Object(std::string _nameOfObject, Transform& _transform);
	Object(std::string _nameOfObject); // Dali je potrebno kreirati novi object odmah sa imenom ili ga samo kreirati pa mu dodeliti defaultIme i ako korisnik zeli da ga preimenuje on to i ucini? jedino kroz neki interface ili wizard-interesantan koncept slicno i za transform???
	Object();

	// Setters
	void setObjectName(std::string _newName);

	// Getters
	std::string getObjectName() const;

	// Components
	Transform* m_transform; // TODO smart ptr
	Shader* m_shader; // Mozda uklonit, mozzzzzzzda
private:
	// Member variables
	std::string m_objectName;

	// Static counter increment to giving a name to the object who dosnt have it
	static int name_counter;

	// Private member functions
	static std::string setDefaultObjectName();
};
#endif // !OBJECT_H