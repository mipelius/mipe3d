// Copyright (c) Miika Pelkonen. All rights reserved.
// Licensed under the MIT License.

#include "Mipe3DResource.h"
#include "Mipe3DJsonUtil.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace mipe3d
{

Resource::Resource(const std::string& filePath)
{
    m_filePath = filePath;
}

bool Resource::load()
{
    unload();

    json metaDefinition;
    
    if (!loadJson(m_filePath, metaDefinition))
    {
        return false;
    }
    
    if (!loadInternal(metaDefinition))
    {
        return false;
    }

    m_isLoaded = true;
    return true;
}

void Resource::unload()
{
    if (m_isLoaded)
    {
        unloadInternal();
    }
}

const std::string& Resource::getFilePath()
{
    return m_filePath;
}


} // namespace mipe3d