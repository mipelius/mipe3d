#pragma once

#include "apidef.h"

#include <string>
#include <map>

namespace mipe3d
{

class Resource;

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

	std::map<std::string, Resource*> m_pathToResourceMap;
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

} // namespace mipe3d