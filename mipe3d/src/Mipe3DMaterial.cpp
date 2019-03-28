#include "Mipe3DMaterial.h"

#include <GL/glew.h>

#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

namespace mipe3d
{

Material::Material(const std::string& filePath) : Resource(filePath) { }

Material::~Material() { }

bool Material::loadInternal(const nlohmann::json& metaDefinition)
{
	return true;
}

void Material::unloadInternal()
{
}

} // namespace mipe3d