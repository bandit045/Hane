#include "RenderFlags.h"


void RenderFlags::addRenderFlag(std::string nameOfRenderFlage, bool defaultFlagValue)
{
	renderFlagsWithOrder.flags.insert(std::pair<std::string, bool>(nameOfRenderFlage, defaultFlagValue));
	renderFlagsWithOrder.insertOrder.push_back(nameOfRenderFlage);
}

void RenderFlags::setValueToBoolRenderFlag(const std::string& nameInMapToChange, const bool& newValueToBool)
{
	renderFlagsWithOrder.flags.at(nameInMapToChange) = newValueToBool;
}

bool& RenderFlags::getSpecificValueReference(const std::string& nameToValueFromMap)
{
	return renderFlagsWithOrder.flags[nameToValueFromMap];
}

DataToReturn& RenderFlags::getAllValue()
{
	return renderFlagsWithOrder;
}