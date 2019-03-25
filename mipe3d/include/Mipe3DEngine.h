#pragma once

#include "apidef.h"

#include <memory>

namespace mipe3d
{

class RenderSystem;
class ResourceManager;
class IScene;

class MIPE3D_API Engine
{
	friend MIPE3D_API Engine& engine();
	friend MIPE3D_API ResourceManager& resourceManager();
	friend MIPE3D_API RenderSystem& renderSystem();

public:
	void run(IScene& scene);

private:
	Engine();
	virtual ~Engine();

	bool startUp();
	bool shutDown();
	void startGameLoop();

	bool m_isRunning = false;
	RenderSystem* m_renderSystem = nullptr;
	ResourceManager* m_resourceManager = nullptr;

	IScene* m_scene = nullptr;
};

MIPE3D_API Engine& engine();
MIPE3D_API ResourceManager& resourceManager();
MIPE3D_API RenderSystem& renderSystem();

} // namespace mipe3d