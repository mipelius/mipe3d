// Copyright (c) Miika Pelkonen. All rights reserved.
// Licensed under the MIT License.

#include "Mipe3DTexture.h"
#include "Mipe3DJsonUtil.h"
#include "Mipe3DLog.h"

#include <gl/glew.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <nlohmann/json.hpp>

namespace mipe3d
{

Texture::Texture(const std::string& filePath) : Resource(filePath) { }

Texture::~Texture() { }

bool Texture::loadInternal(const nlohmann::json& metaDefinition)
{
    // parse source path
    JsonValueParserStatus status;

    auto sourcePath = parseStringFromJson(metaDefinition, "source", status);

    if (status.error != JsonValueParserError::NONE)
    {
        MIPE3D_LOG_ERROR(getFilePath() + ", " + status.errorMessage);
        return false;
    }

    // read image
    SDL_Surface* surface = IMG_Load(sourcePath.c_str());
    if (surface == NULL)
    {
        MIPE3D_LOG_ERROR(
            getFilePath() +
            ", Could not read source \"" +
            sourcePath +
            "\", SDL_image error:" +
            IMG_GetError());

        return false;
    }

    // get the number of channels in the SDL surface
    GLenum textureFormat = GL_NONE;
    GLint numColorChannels;

    numColorChannels = surface->format->BytesPerPixel;
    if (numColorChannels == 4)
    {
        if (surface->format->Rmask == 0x000000ff)
            textureFormat = GL_RGBA;
        else
            textureFormat = GL_BGRA;
    }
    else if (numColorChannels == 3)
    {
        if (surface->format->Rmask == 0x000000ff)
            textureFormat = GL_RGB;
        else
            textureFormat = GL_BGR;
    }
    else {
        MIPE3D_LOG_ERROR(
            sourcePath +
            ", Only true color images are supported");
        return false;
    }

    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        numColorChannels,
        surface->w,
        surface->h,
        0,
        textureFormat,
        GL_UNSIGNED_BYTE,
        surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    SDL_FreeSurface(surface);
    return true;
}

void Texture::unloadInternal()
{
    glDeleteTextures(1, &m_textureId);
}

} // namespace mipe3d