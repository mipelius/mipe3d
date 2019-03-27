#pragma once

#include "apidef.h"

#include <string>

#include <nlohmann/json_fwd.hpp>

namespace mipe3d
{

class MIPE3D_API Resource
{
public:
	Resource(const std::string& filePath);
	virtual ~Resource() {}
	bool load();
	void unload();

protected:
	virtual bool loadInternal(const nlohmann::json& metaDefinition) = 0;
	virtual void unloadInternal() = 0;

private:
	std::string m_filePath;
	bool m_isLoaded = false;
};

} // namespace mipe3d