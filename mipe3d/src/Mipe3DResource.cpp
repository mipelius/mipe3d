#include "Mipe3DResource.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
using json = nlohmann::json;

namespace mipe3d
{

Resource::Resource(const std::string& filePath)
{
	m_filePath = filePath;
}

bool Resource::load()
{
	unload();

	json metaDefinition;
	std::ifstream filestream(m_filePath, std::ifstream::in);

	try
	{
		filestream >> metaDefinition;
	}
	catch(...)
	{
		std::cout << "Failed to parse .meta: " << m_filePath << std::endl;
		return false;
	}
	
	if (!loadInternal(metaDefinition))
	{
		return false;
	}

	m_isLoaded = true;
	return true;
}

void Resource::unload()
{
	if (m_isLoaded)
	{
		unloadInternal();
	}
}


} // namespace mipe3d