#pragma once

#include "apidef.h"

#include <string>
#include <map>

#include "Mipe3DMesh.h"

namespace mipe3d
{

class Resource;
class IResourceFactory;

class MIPE3D_API ResourceManager
{
	friend class Engine;

public:
	template <class T>
	T* get(const std::string& resourcePath);

private:
	ResourceManager();
	~ResourceManager();
	ResourceManager(const ResourceManager& other) = delete;
	ResourceManager& operator=(const ResourceManager& other) = delete;

	bool startUp();
	bool shutDown();

	bool createResource(const std::string& key, const std::string& fullFilePath);

	std::map<std::string, Resource*> m_pathToResourceMap;
	std::map<std::string, IResourceFactory*> m_typeToResourceFactoryMap;
};

// ---- template method definitions ----

template <class T>
T* ResourceManager::get(const std::string& resourcePath)
{
	auto it = m_pathToResourceMap.find(resourcePath);
	if (it == m_pathToResourceMap.end())
	{
		return nullptr;
	}
	return dynamic_cast<T*>(it->second);
}

// ---- singleton accessor ----

MIPE3D_API ResourceManager& resourceManager();

} // namespace mipe3d