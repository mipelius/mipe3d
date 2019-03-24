#pragma once

#include "apidef.h"

#include <string>

namespace mipe3d
{

class MIPE3D_API Resource
{
public:
	Resource(const std::string& filePath);
	virtual ~Resource() {}
	virtual void load() = 0;
	virtual void unload() = 0;

private:
	std::string m_filePath;
};

} // namespace mipe3d