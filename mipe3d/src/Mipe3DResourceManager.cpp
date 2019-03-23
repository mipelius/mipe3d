#include "Mipe3DResourceManager.h"
#include "Mipe3DResource.h"

namespace mipe3d
{

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

bool ResourceManager::startUp()
{
	// create resource objects based on some resource configuration file.
	// ---> to be implemented later...

	// then load all the resources
	for (auto pathToResourcePair : m_pathToResourceMap)
	{
		auto resource = pathToResourcePair.second;
		resource->load();
	}

	return true;
}

bool ResourceManager::shutDown()
{
	for (auto pathToResourcePair : m_pathToResourceMap)
	{
		auto resource = pathToResourcePair.second;
		delete resource;
	}

	return true;
}

} // namespace mipe3d
