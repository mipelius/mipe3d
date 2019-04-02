#include "Mipe3DTexture.h"

#include <GL/glew.h>

#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

namespace mipe3d
{

Texture::Texture(const std::string& filePath) : Resource(filePath) { }

Texture::~Texture() { }

bool Texture::loadInternal(const nlohmann::json& metaDefinition)
{
    return true;
}

void Texture::unloadInternal()
{
}

} // namespace mipe3d