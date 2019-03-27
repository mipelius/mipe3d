#pragma once

#include "apidef.h"
#include "Mipe3DResource.h"

namespace mipe3d
{

class MIPE3D_API Mesh : public Resource
{
public:
	Mesh(const std::string& filePath);
	~Mesh() override;
	
protected:
	bool loadInternal(const nlohmann::json& metaDefinition) override;
	void unloadInternal() override;
};

} // namespace mipe3d