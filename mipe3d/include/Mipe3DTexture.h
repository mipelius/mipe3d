// Copyright (c) Miika Pelkonen. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "apidef.h"
#include "Mipe3DResource.h"

typedef unsigned int GLuint;

namespace mipe3d
{

class Texture : public Resource
{
friend class ShaderProgram;

public:
    MIPE3D_API Texture(const std::string& filePath);
    MIPE3D_API ~Texture() override;
    
protected:
    bool loadInternal(const nlohmann::json& metaDefinition) override;
    void unloadInternal() override;

private:
    GLuint m_textureId;
};

} // namespace mipe3d