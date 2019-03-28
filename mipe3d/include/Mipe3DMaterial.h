#pragma once

#include "apidef.h"
#include "Mipe3DResource.h"

namespace mipe3d
{

class MIPE3D_API Material : public Resource
{
friend class Renderable;

public:
	Material(const std::string& filePath);
	~Material() override;
	
protected:
	bool loadInternal(const nlohmann::json& metaDefinition) override;
	void unloadInternal() override;

private:
	// ...
};

} // namespace mipe3d