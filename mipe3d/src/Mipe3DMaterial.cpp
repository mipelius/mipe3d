// Copyright (c) Miika Pelkonen. All rights reserved.
// Licensed under the MIT License.

#include "Mipe3DMaterial.h"
#include "Mipe3DResourceManager.h"
#include "Mipe3DShaderProgram.h"
#include "Mipe3DTexture.h"
#include "Mipe3DJsonUtil.h"
#include "Mipe3DLog.h"

#include <nlohmann/json.hpp>

namespace mipe3d
{

Material::Material(const std::string& filePath) : Resource(filePath) { }

Material::~Material() { }

bool Material::loadInternal(const nlohmann::json& metaDefinition)
{
    return parseShaderProgram(metaDefinition) && parseTexture(metaDefinition);
}

void Material::unloadInternal()
{
    m_shaderProgram = nullptr;
    m_texture = nullptr;
}

bool Material::parseShaderProgram(const nlohmann::json& metaDefinition)
{
    using json = nlohmann::json;

    // parse shader program name
    JsonValueParserStatus status;

    auto shaderProgramName =
        parseStringFromJson(metaDefinition, "shader_program", status);

    if (status.error != JsonValueParserError::NONE)
    {
        MIPE3D_LOG_ERROR(getFilePath() + ", " + status.errorMessage);
        return false;
    }

    // find shader program resource
    auto shaderProgram = resourceManager().get<ShaderProgram>(shaderProgramName);

    if (!shaderProgram)
    {
        MIPE3D_LOG_ERROR(
            getFilePath() + ", " +
            "Shader program \"" + shaderProgramName + "\" not found");
        return false;
    }

    m_shaderProgram = shaderProgram;
    return true;
}

bool Material::parseTexture(const nlohmann::json& metaDefinition)
{
    using json = nlohmann::json;

    // parse textureName
    JsonValueParserStatus status;

    auto textureName =
        parseStringFromJson(metaDefinition, "texture", status);
    
    if (status.error == JsonValueParserError::NOT_FOUND)
    {
        return true; // ok, since not required
    }
    if (status.error != JsonValueParserError::NONE)
    {
        MIPE3D_LOG_ERROR(getFilePath() + ", " + status.errorMessage);
        return false;
    }

    // find texture resource
    auto texture = resourceManager().get<Texture>(textureName);

    if (!texture)
    {
        MIPE3D_LOG_ERROR(
            getFilePath() + ", " +
            "Texture \"" + textureName + "\" not found");
        return false;
    }

    m_texture = texture;
    return true;
}

} // namespace mipe3d