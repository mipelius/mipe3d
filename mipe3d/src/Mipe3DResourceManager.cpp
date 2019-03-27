#include "Mipe3DResourceManager.h"
#include "Mipe3DResource.h"
#include "Mipe3DMesh.h"

#include <dirent.h>
#include <nlohmann/json.hpp>

#include <iostream>
#include <algorithm>
#include <fstream>
#include <exception>

static const std::string ASSETS_ROOT_DIRECTORY = ".\\assets\\";

using json = nlohmann::json;

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
		
	if (resourceMetaJson.find("type") == resourceMetaJson.end())
	{
		std::cout << 
			"Resource must specify \"type\": " << 
			fullFilePath << 
			std::endl;
		
		return false;
	}

	if (resourceMetaJson["type"] == "mesh")
	{
		Mesh* mesh = new Mesh(fullFilePath);
		m_pathToResourceMap[key] = mesh;
		return true;
	}
	// else if (resourceMetaJson["type"] == "texture") { /* ... */ }
	// else if ...
	else
	{
		std::cout <<
			"Unsupported resource type: \"" <<
			resourceMetaJson["type"] <<
			"\", "
			<< fullFilePath
			<< std::endl;

		return false;
	}
}

} // namespace mipe3d
