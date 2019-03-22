#pragma once

#include <string>

namespace mipe3d
{

class Resource
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