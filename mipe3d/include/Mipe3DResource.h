#pragma once

#include "apidef.h"
#include <string>
#include <nlohmann/json_fwd.hpp>

namespace mipe3d
{

class Resource
{
public:
	MIPE3D_API Resource(const std::string& filePath);
	MIPE3D_API virtual ~Resource() {}
	MIPE3D_API bool load();
	MIPE3D_API void unload();

	const std::string& getFilePath();

protected:
	MIPE3D_API virtual bool loadInternal(const nlohmann::json& metaDefinition) = 0;
	MIPE3D_API virtual void unloadInternal() = 0;

private:
	std::string m_filePath;
	bool m_isLoaded = false;
};

} // namespace mipe3d