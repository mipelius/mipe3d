#include "Mipe3DResourceManager.h"
#include "Mipe3DResource.h"
#include "Mipe3DMesh.h"
#include "Mipe3DShaderProgram.h"

#include <dirent.h>
#include <nlohmann/json.hpp>

#include <iostream>
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
		std::cout << "Directory '" << ASSETS_ROOT_DIRECTORY << "' is missing!";
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
	// parse json
	std::ifstream filestream(fullFilePath, std::ifstream::in);
	json resourceMetaJson;

	try
	{
		filestream >> resourceMetaJson;
	}
	catch (json::parse_error)
	{
		std::cout <<
			"Corrupted .meta, should be in json format: " <<
			fullFilePath <<
			std::endl;

		return false;
	}
	catch (...)
	{
		std::cout <<
			"Error occured during parsing the file, " <<
			"fullFilePath" <<
			std::endl;

		return false;
	}

	// check type
	const char* TYPE_FIELD = "type";

	if (resourceMetaJson.find(TYPE_FIELD) == resourceMetaJson.end())
	{
		std::cout <<
			"Resource must specify \"" << TYPE_FIELD << "\": " <<
			fullFilePath <<
			std::endl;

		return false;
	}

	// check if type is supported
	auto typeString = resourceMetaJson[TYPE_FIELD].get<std::string>();

	if (m_typeToResourceFactoryMap.find(typeString) == m_typeToResourceFactoryMap.end())
	{
		std::cout <<
			"Unsupported resource type: \"" <<
			typeString <<
			"\", "
			<< fullFilePath
			<< std::endl;

		return false;
	}

	// create and store resource
	auto factory = m_typeToResourceFactoryMap[typeString];
	auto resource = factory->create(fullFilePath);
	m_pathToResourceMap[key] = resource;
	return true;
}

} // namespace mipe3d
