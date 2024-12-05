#ifndef RENDER_FLAGS_H
#define RENDER_FLAGS_H

#include <unordered_map>

struct DataToReturn {
	std::vector<std::string> insertOrder;
	std::unordered_map<std::string, bool> flags;
};

class RenderFlags//For different state insade the fragment shader, or other shaders using std::unordered_map and std::vector
{
public:
	//To add a new value, to existing one order in which is added important and tracked by std::vector for order
	void addRenderFlag(std::string nameOfRenderFlage, bool defaultFlagValue);
	//Serve to change the value inside the std::unordered_map structure by name and value
	void setValueToBoolRenderFlag(const std::string& nameInMapToChange, const bool& newValueToBool);
	// Serve to get reference value from the std::unordered_map structure
	bool& getSpecificValueReference(const std::string& nameToValueFromMap);

	//This method serve as to get any value inside this class and edit it use it carefull!!
	DataToReturn& getAllValue();
private:
	DataToReturn renderFlagsWithOrder;
};

#endif // !RENDER_FLAGS_H