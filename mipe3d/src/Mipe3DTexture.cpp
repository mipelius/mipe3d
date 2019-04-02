#include "Mipe3DTexture.h"

#include <nlohmann/json.hpp>

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