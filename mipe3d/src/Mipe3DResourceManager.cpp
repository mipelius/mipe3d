#include "Mipe3DResourceManager.h"

#include "Mipe3DEngine.h"
#include "Mipe3DResource.h"
#include "Mipe3DMesh.h"
#include "Mipe3DShaderProgram.h"
#include "Mipe3DMaterial.h"
#include "Mipe3DTexture.h"
#include "Mipe3DJsonUtil.h"
#include "Mipe3DLog.h"

#include <dirent.h>
#include <nlohmann/json.hpp>

#include <algorithm>
#include <fstream>
#include <exception>

using json = nlohmann::json;

namespace mipe3d
{

class IResourceFactory
{
public:
	virtual Resource* create(const std::string& filePath) = 0;
};

template <class T>
class ResourceFactory : public IResourceFactory
{
public:
	ResourceFactory()
	{
		static_assert(
			std::is_base_of<Resource, T> (),
			"Resource factory's type T must be inherited from Resource."
		);
	}
	Resource* create(const std::string& filePath)
	{
		return new T(filePath);
	}
};

static const std::string ASSETS_ROOT_DIRECTORY = ".\\assets\\";

ResourceManager::ResourceManager()
{
	m_typeToResourceFactoryMap["mesh"] = new ResourceFactory<Mesh>();
 	m_typeToResourceFactoryMap["shader_program"] = new ResourceFactory<ShaderProgram>();
	m_typeToResourceFactoryMap["texture"] = new ResourceFactory<Texture>();
	m_typeToResourceFactoryMap["material"] = new ResourceFactory<Material>();
}

ResourceManager::~ResourceManager()
{
for (auto pair : m_typeToResourceFactoryMap)
{
	delete pair.second;
}
}

bool ResourceManager::startUp()
{
	// create resources defined in .meta files in ASSETS_ROOT_DIRECTORY
	DIR *dir;
	struct dirent *entry;
	if (!(dir = opendir(ASSETS_ROOT_DIRECTORY.c_str())))
	{
		MIPE3D_LOG_ERROR(
			std::string("Directory \"") + ASSETS_ROOT_DIRECTORY + "\" is missing!");
		return false;
	}
	while (entry = readdir(dir))
	{
		std::string fileName(entry->d_name);

		size_t fileExtensionPosition = fileName.size() >= 5 ? fileName.size() - 5 : 0;

		if (fileName.substr(fileExtensionPosition) == ".meta")
		{
			auto key = fileName.substr(0, fileExtensionPosition);
			std::string fullPath = ASSETS_ROOT_DIRECTORY + fileName;

			if (!createResource(key, fullPath))
			{
				return false;
			}
		}
	}
	closedir(dir);

	// load all the created resources
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
		resource->unload();
		delete resource;
	}

	return true;
}

bool ResourceManager::createResource(const std::string& key, const std::string& fullFilePath)
{
	// load json
	json resourceMetaJson;

	if (!loadJson(fullFilePath, resourceMetaJson))
	{
		return false;
	}
	
	JsonValueParserStatus status;

	// parse typename
	auto typeName = parseStringFromJson(resourceMetaJson, "type", status);

	if (status.error != JsonValueParserError::NONE)
	{
		MIPE3D_LOG_ERROR(status.errorMessage);
		return false;
	}
	
	// check if type is supported
	if (m_typeToResourceFactoryMap.find(typeName) == m_typeToResourceFactoryMap.end())
	{
		MIPE3D_LOG_ERROR(
			fullFilePath +
			", Resource type: \"" +
			typeName +
			"\" is not supported");

		return false;
	}

	// create and store resource
	auto factory = m_typeToResourceFactoryMap[typeName];
	auto resource = factory->create(fullFilePath);
	m_pathToResourceMap[key] = resource;
	return true;
}

ResourceManager& resourceManager()
{
	return *(engine().m_resourceManager);
}

} // namespace mipe3d
