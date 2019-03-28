#pragma once

#include "apidef.h"
#include "Mipe3DResource.h"

namespace mipe3d
{

class Texture : public Resource
{
friend class Renderable;

public:
	MIPE3D_API Texture(const std::string& filePath);
	MIPE3D_API ~Texture() override;
	
protected:
	bool loadInternal(const nlohmann::json& metaDefinition) override;
	void unloadInternal() override;

private:
	// ...
};

} // namespace mipe3d