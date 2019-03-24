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
public:
	Engine();
	void run(IScene& scene);
	virtual ~Engine();

private:
	bool startUp();
	bool shutDown();
	void startGameLoop();

	bool m_isRunning = false;
	RenderSystem* m_renderSystem = nullptr;
	ResourceManager* m_resourceManager = nullptr;

	IScene* m_scene = nullptr;
};

} // namespace mipe3d